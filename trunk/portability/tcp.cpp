////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////

#include "tcp.hpp"
#include "dprintf.hpp"
#include <string.h>

#ifdef MSWINDOWS
// Windoze-specific includes
#include <winsock2.h>
#define ERRNO WSAGetLastError()
#define HERRNO WSAGetLastError()
#define IOCTL ioctlsocket
#define CLOSE closesocket
#define SHUT_RDWR SD_BOTH
#define EINPROGRESS WSAEINPROGRESS
#define EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKLEN_T int
#else
// Generic Unix includes
// fix for older versions of Darwin?
#define _BSD_SOCKLEN_T_ int
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define ERRNO errno
#define HERRNO h_errno
#define SOCKET int
#define SOCKET_ERROR -1
#define IOCTL ::ioctl
#define CLOSE ::close
#define SOCKLEN_T socklen_t
#ifdef SOLARIS
// Sun put some definitions in a different place
#include <sys/filio.h>
#endif
#endif

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

////////////////////////////////////////////////////////////////////////////////
// Utilities

  static std::string error_string(int error)
  {
    std::string result = "error " + dformat("%d",error);
#ifdef MSWINDOWS
    char* message = 0;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                  0,
                  error,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // "User default language"
                  (LPTSTR)&message,
                  0,0);
    if (message) 
    {
      result = message;
      LocalFree(message);
    }
    // the error message is for some perverse reason newline terminated - remove this
    if (result[result.size()-1] == '\n')
      result.erase(result.end()-1);
    if (result[result.size()-1] == '\r')
      result.erase(result.end()-1);
#else
    result = strerror(error);
#endif
    return result;
  }

  // convert address:port into a sockaddr
  static void convert_address(unsigned long address, unsigned short port, sockaddr& sa)
  {
    unsigned short network_port = htons(port);
    unsigned long network_address = htonl(address);
    sa.sa_family = AF_INET;
    memcpy(&sa.sa_data[0], &network_port, sizeof(network_port));
    memcpy(&sa.sa_data[2], &network_address, sizeof(network_address));
  }

  // convert host:port into a sockaddr
  static void convert_host(hostent& host, unsigned short port, sockaddr& sa)
  {
    sa.sa_family = host.h_addrtype;
    unsigned short network_port = htons(port);
    memcpy(&sa.sa_data[0], &network_port, sizeof(network_port));
    memcpy(&sa.sa_data[2], host.h_addr, host.h_length);
  }

  // convert sockaddr to address:port
  static void convert_sockaddr(const sockaddr& sa, unsigned long& address, unsigned short& port)
  {
    unsigned short network_port = 0;
    memcpy(&network_port, &sa.sa_data[0], sizeof(network_port));
    unsigned long network_address = 0;
    memcpy(&network_address, &sa.sa_data[2], sizeof(network_address));
    address = ntohl(network_address);
    port = ntohs(network_port);
  }

////////////////////////////////////////////////////////////////////////////////
// Initialisation
// Windows requires that Winsock is initialised before use and closed after
// These routines initialise once on first use and close on the destruction of the last object using it
// on non-windows platforms, I still increment/decrement the sockets count variable for diagnostic purposes

  static int sockets_count = 0;

  static int sockets_init(void)
  {
    int error = 0;
    if (sockets_count++ == 0)
    {
#ifdef MSWINDOWS
      WSAData winsock_info;
      // request Winsock 2.0 or higher
      error = WSAStartup(MAKEWORD(2,0),&winsock_info);
#endif
    }
    return error;
  }

  static int sockets_close(void)
  {
    int error = 0;
    if (--sockets_count == 0)
    {
#ifdef MSWINDOWS
      if (WSACleanup() == SOCKET_ERROR)
        error = ERRNO;
#endif
    }
    return error;
  }

////////////////////////////////////////////////////////////////////////////////
// Socket - common code to manipulate a TCP socket

  class TCP_socket
  {
  private:
    SOCKET m_socket;
    mutable int m_error;
    mutable std::string m_message;

    TCP_socket(const TCP_socket&);

  public:

    ////////////////////////////////////////////////////////////////////////////
    // constructors/destructors

    TCP_socket(void) : m_socket(INVALID_SOCKET), m_error(0)
      {
        set_error(sockets_init());
      }

    ~TCP_socket(void)
      {
        close();
        set_error(sockets_close());
      }

    ////////////////////////////////////////////////////////////////////////////
    // error handling

    void set_error (int error) const
      {
        if (m_error == 0 && error != 0)
        {
          m_error = error;
          m_message = error_string(error);
        }
      }

    int error(void) const
      {
        return m_error;
      }

    void clear_error (void)
      {
        m_error = 0;
        m_message.erase();
      }

    std::string message(void) const
      {
        return error_string(m_error);
      }

    ////////////////////////////////////////////////////////////////////////////
    // initialisation, connection

    bool initialised(void) const
      {
        return m_socket != INVALID_SOCKET;
      }

    // attach this object to a pre-opened socket
    bool set(SOCKET socket)
      {
        if (!close()) return false;
        clear_error();
        m_socket = socket;
        return true;
      }

    // create a raw socket attached to this object
    bool initialise(void)
      {
        if (!close()) return false;
        clear_error();
        // create an anonymous socket
        m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket == INVALID_SOCKET)
        {
          set_error(ERRNO);
          close();
          return false;
        }
        // set the socket into non-blocking mode
        unsigned long nonblocking = 1;
        if (IOCTL(m_socket, FIONBIO, &nonblocking) == SOCKET_ERROR)
        {
          set_error(ERRNO);
          return false;
        }
        return true;
      }

    // initialise a socket and set this socket up to be a listening port
    // - port: port to listen on
    // - length of backlog queue to manage - may be zero
    // - returns success status
    bool listen(unsigned short port, unsigned short queue = 0)
      {
        if (!initialise())
          return false;
        // name the socket and bind it to a port - this is a requirement for a server
        sockaddr server;
        convert_address(INADDR_ANY, port, server);
        if (bind(m_socket, &server, sizeof(server)) == SOCKET_ERROR)
        {
          set_error(ERRNO);
          close();
          return false;
        }
        // now set the port to listen for incoming connections
        if (::listen(m_socket, (int)queue) == SOCKET_ERROR)
        {
          set_error(ERRNO);
          close();
          return false;
        }
        return true;
      }

    // accept a connection on the object's socket - only applicable if it has been set up as a listening port
    // - socket - filled in with the accepted connection's socket
    // - remote_address - filled in with accepted connection's IP address
    // - remote_port - filled in with accepted connection's port
    bool accept(SOCKET& socket, unsigned long& remote_address, unsigned short& remote_port)
      {
        // accept the connection, at the same time getting the address of the connecting client
        sockaddr saddress;
        SOCKLEN_T saddress_length = sizeof(saddress);
        SOCKET connection_socket = ::accept(m_socket, &saddress, &saddress_length);
        if (connection_socket == INVALID_SOCKET)
        {
          set_error(ERRNO);
          return false;
        }
        // extract the contents of the address
        convert_sockaddr(saddress, remote_address, remote_port);
        return true;
      }

    // client connect to a server
    // - address: IP name or number
    // - port: port to connect to
    bool connect(const std::string& address, unsigned short port,
                 unsigned long& remote_address, unsigned short& remote_port)
      {
        if (!initialise())
          return false;
        bool result = true;
        // Lookup the IP address to convert it into a host record
        // this DOES lookup IP address names as well (not according to MS help !!)
        hostent* host_info = ::gethostbyname(address.c_str());
        if (!host_info)
        {
          set_error(HERRNO);
          result = false;
        }
        else
        {
          /// fill in the connection data structure
          sockaddr connect_data;
          convert_host(*host_info, port, connect_data);
          // try connecting
          if (::connect(m_socket, &connect_data, sizeof(connect_data)) == SOCKET_ERROR)
          {
            // extract the remote connection details for local storage
            convert_sockaddr(connect_data, remote_address, remote_port);
            // the socket is non-blocking, so connect will almost certainly fail with EINPROGRESS which is not an error
            int error = ERRNO;
            if (error != EINPROGRESS && error != EWOULDBLOCK)
            {
              set_error(error);
              result = false;
            }
          }
        }
        return result;
      }

    // test whether a socket is connected and ready to communicate
    bool connected(unsigned timeout = 0)
      {
        // Linux and Windows docs say test with select for whether socket is
        // writable - this is already done by send_ready. However, a problem
        // has been reported with Linux whereby the OS will report a socket as
        // writable when it isn't
#ifdef MSWINDOWS
        return send_ready(timeout);
#else
        if (!send_ready(timeout)) return false;
        // DJDM: socket has returned EINPROGRESS on the first attempt at connection
        // it has also returned that it can be written to
        // we must now ask it if it has actually connected - using getsockopt
        int error;
        socklen_t serror = sizeof(int);
        if (getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &error, &serror)==0)
          // handle the error value - one of them means that the socket has connected
          if (!error || error == EISCONN)
            return true;
        return false;
#endif
      }

    bool close(void)
      {
        bool result = true;
        if (initialised())
        {
          if (shutdown(m_socket,SHUT_RDWR) == SOCKET_ERROR)
          {
            set_error(ERRNO);
            result = false;
          }
          if (CLOSE(m_socket) == SOCKET_ERROR)
          {
            set_error(ERRNO);
            result = false;
          }
        }
        m_socket = INVALID_SOCKET;
        return result;
      }

    ////////////////////////////////////////////////////////////////////////////
    // sending/receiving

    bool send_ready(unsigned wait = 0)
      {
        if (!initialised()) return false;
        // determines whether the socket is ready to send
        fd_set write_set; 
        FD_ZERO(&write_set);
        FD_SET(m_socket,&write_set);
        timeval timeout;
        timeout.tv_sec = wait/1000000;
        timeout.tv_usec = wait%1000000;
        int select_result = select(m_socket+1, 0, &write_set, 0, &timeout);
        switch(select_result)
        {
        case SOCKET_ERROR:
          // select failed with an error - trap the error
          set_error(ERRNO);
          return false;
        case 0:
          // timeout exceeded without a connection appearing
          return false;
        default:
          // at least one connection is pending
          return true;
        }
      }

    bool send (std::string& data)
      {
        if (!initialised()) return false;
        if (!send_ready(0)) return true;
        // send the data - this will never block but may not send all the data
        int bytes = ::send(m_socket, data.c_str(), data.size(), 0);
        if (bytes == SOCKET_ERROR)
        {
          set_error(ERRNO);
          return false;
        }
        // remove the sent bytes from the data buffer so that the buffer represents the data still to be sent
        data.erase(0,bytes);
        return true;
      }

    bool receive_ready(unsigned wait = 0)
      {
        if (!initialised()) return false;
        // determines whether the socket is ready to receive
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(m_socket,&read_set);
        timeval timeout;
        timeout.tv_sec = wait/1000000;
        timeout.tv_usec = wait%1000000;
        int select_result = select(m_socket+1, &read_set, 0, 0, &timeout);
        switch(select_result)
        {
        case SOCKET_ERROR:
          // select failed with an error - trap the error
          set_error(ERRNO);
          return false;
        case 0:
          // timeout exceeded without a connection appearing
          return false;
        default:
          // at least one connection is pending
          return true;
        }
      }

    bool receive (std::string& data)
      {
        if (!initialised()) return false;
        if (!receive_ready(0)) return true;
        bool result = true;
        // determine how much data is available to read
        unsigned long bytes = 0;
        if (IOCTL(m_socket, FIONREAD, &bytes) == SOCKET_ERROR)
        {
          set_error(ERRNO);
          result = false;
        }
        else
        {
          // get the data up to the amount claimed to be present - this is non-blocking
          char* buffer = new char[bytes+1];
          int read = recv(m_socket, buffer, bytes, 0);
          if (read == SOCKET_ERROR)
          {
            set_error(ERRNO);
            close();
            result = false;
          }
          else if (read == 0)
          {
            // TODO - check whether this is an appropriate conditon to close the socket
            close();
          }
          else
          {
            // this is binary data so copy the bytes including nulls
            data.append(buffer,read);
          }
          delete[] buffer;
        }
        return result;
      }

    ////////////////////////////////////////////////////////////////////////////
    // informational

    SOCKET socket(void) const
      {
        return m_socket;
      }

    unsigned short local_port() const
      {
        sockaddr sa;
        SOCKLEN_T address_length = sizeof(sa);
        if (getsockname(m_socket, &sa, &address_length) != 0)
        {
          set_error(ERRNO);
          return 0;
        }
        unsigned long address = 0;
        unsigned short port = 0;
        convert_sockaddr(sa, address, port);
        return port;
      }

  };

  ////////////////////////////////////////////////////////////////////////////////
  // Connection

  class TCP_connection_data
  {
  private:
    friend class TCP_server_data;
    TCP_socket m_socket;
    unsigned long m_address;
    unsigned short m_port;
    unsigned m_count;

    TCP_connection_data(const TCP_connection_data&);

  public:

    TCP_connection_data(void) : m_address(0), m_port(0), m_count(1)
      {
      }

    ~TCP_connection_data(void)
      {
        close();
      }

    void increment(void)
      {
        ++m_count;
      }

    bool decrement(void)
      {
        --m_count;
        return m_count == 0;
      }

    void set_error (int error)
      {
        m_socket.set_error(error);
      }

    int error(void) const
      {
        return m_socket.error();
      }

    std::string message(void) const
      {
        return m_socket.message();
      }

    bool initialise(const SOCKET& socket, unsigned long address, unsigned short port)
      {
        close();
        m_socket.set(socket);
        m_address = address;
        m_port = port;
        return true;
      }

    bool initialised(void) const
      {
        return m_socket.initialised();
      }

    unsigned long remote_address(void) const
      {
        return m_address;
      }

    unsigned short remote_port(void) const
      {
        return m_port;
      }

    unsigned short local_port(void) const
      {
        return m_socket.local_port();
      }

    bool send_ready(unsigned wait)
      {
        return m_socket.send_ready(wait);
      }

    bool send (std::string& data)
      {
        return m_socket.send(data);
      }

    bool receive_ready(unsigned wait)
      {
        return m_socket.receive_ready(wait);
      }

    bool receive (std::string& data)
      {
        return m_socket.receive(data);
      }

    bool close(void)
      {
        m_address = 0;
        m_port = 0;
        return m_socket.close();
      }
  };

  ////////////////////////////////////////
  // exported functions

  TCP_connection::TCP_connection(void) : m_data(new TCP_connection_data)
  {
  }

  TCP_connection::~TCP_connection(void)
  {
    if (m_data->decrement())
      delete m_data;
  }

  TCP_connection::TCP_connection(const TCP_connection& connection) : m_data(0)
  {
    m_data = connection.m_data;
    m_data->increment();
  }

  TCP_connection& TCP_connection::operator=(const TCP_connection& connection)
  {
    if (m_data == connection.m_data) return *this;
    if (m_data->decrement())
      delete m_data;
    m_data = connection.m_data;
    m_data->increment();
    return *this;
  }

  int TCP_connection::error(void) const
  {
    return m_data->error();
  }

  std::string TCP_connection::message(void) const
  {
    return m_data->message();
  }

  bool TCP_connection::initialised(void) const
  {
    return m_data->initialised();
  }

  unsigned long TCP_connection::address(void) const
  {
    return m_data->remote_address();
  }

  unsigned short TCP_connection::port(void) const
  {
    return remote_port();
  }

  unsigned short TCP_connection::remote_port(void) const
  {
    return m_data->remote_port();
  }

  unsigned short TCP_connection::local_port(void) const
  {
    return m_data->remote_port();
  }

  bool TCP_connection::send_ready(unsigned wait)
  {
    return m_data->send_ready(wait);
  }

  bool TCP_connection::send (std::string& data)
  {
    return m_data->send(data);
  }

  bool TCP_connection::receive_ready(unsigned wait)
  {
    return m_data->receive_ready(wait);
  }

  bool TCP_connection::receive (std::string& data)
  {
    return m_data->receive(data);
  }

  bool TCP_connection::close(void)
  {
    return m_data->close();
  }

////////////////////////////////////////////////////////////////////////////////
// Server

  class TCP_server_data
  {
  private:
    TCP_socket m_socket;
    unsigned m_count;

    TCP_server_data(const TCP_server_data&);

  public:

    TCP_server_data(void) : m_count(1)
      {
      }

    ~TCP_server_data(void)
      {
        close();
      }

    void increment(void)
      {
        ++m_count;
      }

    bool decrement(void)
      {
        --m_count;
        return m_count == 0;
      }

    void set_error (int error)
      {
        m_socket.set_error(error);
      }

    int error(void) const
      {
        return m_socket.error();
      }

    std::string message(void) const
      {
        return m_socket.message();
      }

    bool initialise(unsigned short port, unsigned short queue)
      {
        return m_socket.listen(port, queue);
      }

    bool initialised(void) const
      {
        return m_socket.initialised();
      }

    bool close(void)
      {
        return m_socket.close();
      }

    bool connection_ready(unsigned wait)
      {
        return m_socket.receive_ready(wait);
      }

    TCP_connection connection(void)
      {
        TCP_connection connection;
        SOCKET socket = INVALID_SOCKET;
        unsigned long address = 0;
        unsigned short port = 0;
        if (m_socket.accept(socket, address, port))
          connection.m_data->initialise(socket, address, port);
        return connection;
      }
  };

  ////////////////////////////////////////
  // exported functions

  TCP_server::TCP_server(void) : m_data(new TCP_server_data)
  {
  }

  TCP_server::TCP_server(unsigned short port, unsigned short queue) : m_data(new TCP_server_data)
  {
    initialise(port,queue);
  }

  TCP_server::~TCP_server(void)
  {
    if (m_data->decrement())
      delete m_data;
  }

  TCP_server::TCP_server(const TCP_server& server)
  {
    m_data = server.m_data;
    m_data->increment();
  }

  TCP_server& TCP_server::operator=(const TCP_server& server)
  {
    if (m_data == server.m_data) return *this;
    if (m_data->decrement())
      delete m_data;
    m_data = server.m_data;
    m_data->increment();
    return *this;
  }

  bool TCP_server::initialise(unsigned short port, unsigned short queue)
  {
    return m_data->initialise(port,queue);
  }

  bool TCP_server::initialised(void) const
  {
    return m_data->initialised();
  }

  int TCP_server::error(void) const
  {
    return m_data->error();
  }

  std::string TCP_server::message(void) const
  {
    return m_data->message();
  }

  bool TCP_server::close(void)
  {
    return m_data->close();
  }

  bool TCP_server::connection_ready(unsigned wait)
  {
    return m_data->connection_ready(wait);
  }

  TCP_connection TCP_server::connection(void)
  {
    return m_data->connection();
  }

////////////////////////////////////////////////////////////////////////////////
// Client

  class TCP_client_data
  {
  private:
    TCP_socket m_socket;
    unsigned long m_address;
    unsigned short m_port;
    unsigned m_count;

    TCP_client_data(const TCP_client_data&);

  public:

    TCP_client_data(void) : m_address(0), m_port(0), m_count(1)
      {
      }

    ~TCP_client_data(void)
      {
        close();
      }

    void increment(void)
      {
        ++m_count;
      }

    bool decrement(void)
      {
        --m_count;
        return m_count == 0;
      }

    void set_error (int error)
      {
        m_socket.set_error(error);
      }

    int error(void) const
      {
        return m_socket.error();
      }

    std::string message(void) const
      {
        return m_socket.message();
      }

    // initialise - with 0 timeout this does a non-blocking connect, otherwise it blocks with the specified timeout
    bool initialise(const std::string& address, unsigned short port, unsigned timeout=0)
      {
        if (!m_socket.connect(address, port, m_address, m_port))
        {
          close();
          return false;
        }
        if (timeout && !m_socket.connected(timeout))
        {
          close();
          return false;
        }
        return true;
      }

    bool initialised(void) const
      {
        return m_socket.initialised();
      }

    unsigned long address(void) const
      {
        return m_address;
      }

    unsigned short local_port(void) const
      {
        return m_socket.local_port();
      }

    unsigned short remote_port(void) const
      {
        return m_port;
      }

    bool connected(void)
      {
        return m_socket.connected();
      }

    bool send_ready(unsigned wait)
      {
        return m_socket.send_ready(wait);
      }

    bool send (std::string& data)
      {
        return m_socket.send(data);
      }

    bool receive_ready(unsigned wait)
      {
        return m_socket.receive_ready(wait);
      }

    bool receive (std::string& data)
      {
        return m_socket.receive(data);
      }

    bool close(void)
      {
        m_address = 0;
        m_port = 0;      
        return m_socket.close();
      }

  };

  ////////////////////////////////////////
  // exported functions

  TCP_client::TCP_client(void) : m_data(new TCP_client_data)
  {
  }

  TCP_client::TCP_client(const std::string& address, unsigned short port, unsigned int timeout) : 
    m_data(new TCP_client_data)
  {
    initialise(address,port,timeout);
  }

  TCP_client::~TCP_client(void)
  {
    if (m_data->decrement())
      delete m_data;
  }

  TCP_client::TCP_client(const TCP_client& client)
  {
    m_data = client.m_data;
    m_data->increment();
  }

  TCP_client& TCP_client::operator=(const TCP_client& client)
  {
    if (m_data == client.m_data) return *this;
    if (m_data->decrement())
      delete m_data;
    m_data = client.m_data;
    m_data->increment();
    return *this;
  }

  int TCP_client::error(void) const
  {
    return m_data->error();
  }

  std::string TCP_client::message(void) const
  {
    return m_data->message();
  }

  bool TCP_client::initialise(const std::string& address, unsigned short port, unsigned int timeout)
  {
    return m_data->initialise(address, port, timeout);
  }

  bool TCP_client::initialised(void) const
  {
    return m_data->initialised();
  }

  bool TCP_client::connected(void)
  {
    return m_data->connected();
  }

  unsigned long TCP_client::address(void) const
  {
    return m_data->address();
  }

  unsigned short TCP_client::port(void) const
  {
    return remote_port();
  }

  unsigned short TCP_client::remote_port(void) const
  {
    return m_data->remote_port();
  }

  unsigned short TCP_client::local_port(void) const
  {
    return m_data->local_port();
  }

  bool TCP_client::send_ready(unsigned wait)
  {
    return m_data->send_ready(wait);
  }

  bool TCP_client::send (std::string& data)
  {
    return m_data->send(data);
  }

  bool TCP_client::receive_ready(unsigned wait)
  {
    return m_data->receive_ready(wait);
  }

  bool TCP_client::receive (std::string& data)
  {
    return m_data->receive(data);
  }

  bool TCP_client::close(void)
  {
    return m_data->close();
  }

////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
