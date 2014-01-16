#include "build.hpp"
#include "tcp_sockets.hpp"
#include "string_utilities.hpp"
#include "subprocesses.hpp"
#include <vector>
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// TCP test: this program is designed to be run twice - once without an
// argument as the server, which itself runs a second copy with an argument as
// the client. The two instances then swap information using TCP
////////////////////////////////////////////////////////////////////////////////

unsigned timeout = 10000000;

////////////////////////////////////////////////////////////////////////////////
// Server code
// sets up a TCP server then spawns this program again in client mode

int server(std::vector<std::string> values, int port, const std::string& command)
{
  int errors = 0;
  std::cerr << "server: " << stlplus::build() << std::endl;
  // this is the first-run instance and acts as the server
  // setup a server on the shared port
  std::cerr << "server: started" << std::endl;
  stlplus::TCP_server server(port);
  std::cerr << "server: set up TCP server on port " << port << std::endl;
  // now spawn a second copy of this program
  stlplus::async_subprocess client;
  client.spawn(command);
  std::cerr << "server: spawned client with command: " << command << std::endl;
  // now wait for a client connection to come in
  std::cerr << "server: waiting for incoming connection" << std::endl;
  if (!server.accept_ready(timeout))
  {
    std::cerr << "server: ERROR: wait for incoming connection timed out" << std::endl;
    ++errors;
  }
  else
  {
    std::cerr << "server: accepting incoming connection" << std::endl;
    stlplus::TCP_connection connection = server.accept();
    unsigned request = 0;
    while(connection.initialised())
    {
      std::cerr << "server: checking for receive request" << std::endl;
      // check connection for incoming request
      if (!connection.receive_ready(timeout))
      {
        std::cerr << "server: ERROR: wait for receive timed out" << std::endl;
        ++errors;
      }
      else
      {
        // receive the request
        std::string data;
        if (!connection.receive(data))
        {
          std::cerr << "server: ERROR: connection receive failed after receive_ready was true" << std::endl;
          ++errors;
        }
        else if (data.size() == 0)
        {
          // legitimate (?) last receive of an empty string
          std::cerr << "server: received empty string \"" << data << "\"" << std::endl;
        }
        else
        {
          // report the value and check it's correct
          std::cerr << "server: received \"" << data << "\"" << std::endl;
          std::string value = std::string("error");
          if (request < values.size())
            value = values[request];
          if (data != value)
          {
            std::cerr << "server: ERROR: received data \"" << data << "\" != \"" << value << "\"" << std::endl;
            ++errors;
          }
          // now throw the same data back
          if (!connection.send_ready(timeout))
          {
            std::cerr << "server: ERROR: wait for send timed out" << std::endl;
            ++errors;
          }
          else
          {
            std::cerr << "server: sending \"" << data << "\"" << std::endl;
            if (!connection.send(data))
            {
              std::cerr << "server: ERROR: connection send failed after send_ready was true" << std::endl;
              ++errors;
            }
          }
          request++;
        }            
      }
      // just check for client having exited
      if (!client.tick())
      {
        std::cerr << "server: client has exited - closing connection" << std::endl;
        connection.close();
      }
    }
    std::cerr << "server: exited server loop" << std::endl;
    // wait for client to exit
    while (client.tick())
    {
      std::cerr << "server: client has not exited - waiting" << std::endl;
      sleep(1);
    }
    if (client.exit_status() != 0)
    {
      std::cerr << "server: ERROR: client has exited with status " << client.exit_status() << std::endl;
      errors += client.exit_status();
    }
  }
  std::cerr << "server: " << (errors ? "ERROR:" : "SUCCESS:") << " exiting with " << errors << " errors" << std::endl;
  return errors;
}

////////////////////////////////////////////////////////////////////////////////
// client

int client(std::vector<std::string> values, int port)
{
  int errors = 0;
  // this is the second-run instance and acts as the client
  std::cerr << "client: " << stlplus::build() << std::endl;
  std::cerr << "client: creating connection" << std::endl;
  stlplus::TCP_client connection("localhost", port, timeout);
  unsigned request = 0;
  while(connection.connected())
  {
    std::string value = values[request];
    // send this value
    std::cerr << "client: sending data" << std::endl;
    if (!connection.send_ready(timeout))
    {
      std::cerr << "client: ERROR: wait for send timed out" << std::endl;
      ++errors;
    }
    else
    {
      // avoid the data being consumed by the send
      std::string data = value;
      std::cerr << "client: sending \"" << data << "\"" << std::endl;
      if (!connection.send(data))
      {
        std::cerr << "client: ERROR: connection send failed after send_ready was true" << std::endl;
        ++errors;
      }
    }
    // check connection for incoming request
    if (!connection.receive_ready(timeout))
    {
      std::cerr << "client: ERROR: wait for receive timed out" << std::endl;
      ++errors;
    }
    else
    {
      // receive the request
      std::string data;
      if (!connection.receive(data))
      {
        std::cerr << "client: ERROR: connection receive failed after receive_ready was true" << std::endl;
        ++errors;
      }
      else
      {
        // report the value and check it's correct
        std::cerr << "client: received \"" << data << "\"" << std::endl;
        if (data != value)
        {
          std::cerr << "client: ERROR: received data \"" << data << "\" != \"" << value << "\"" << std::endl;
          ++errors;
        }
        request++;
      }            
    }
    if (request >= values.size())
    {
      std::cerr << "client: all values sent, closing connection" << std::endl;
      connection.close();
    }
  }
  std::cerr << "client: exited communication loop" << std::endl;
  std::cerr << "client: " << (errors ? "ERROR:" : "SUCCESS:") << " exiting with " << errors << " errors" << std::endl;
  return errors;
}

////////////////////////////////////////////////////////////////////////////////
// main program

int main (int argc, char* argv[])
{
  // code common to both instances to ensure both have the same information
  std::vector<std::string> values = stlplus::split("one:two:three", ":");
  int port = 3000;

  // now branch for the two instances
  int errors = 0;
  if (argc == 1)
  {
    std::string command = std::string(argv[0]) + std::string(" client");
    errors = server(values, port, command);
  }
  else
  {
    errors = client(values, port);
  }
  return errors;
}
