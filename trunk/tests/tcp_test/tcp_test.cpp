#include "build.hpp"
#include "tcp.hpp"
#include <string>
#include <iostream>

int main (int argc, char* argv[])
{
  std::cerr << stlplus::build() << std::endl;
  // connect to the standard HTTP port of the first argument
  stlplus::TCP_client connection("www.andyrushton.co.uk", 80, 5000000);
  if (connection.error())
  {
    std::cerr << "error whilst connecting: " << connection.message() << std::endl;
    return -1;
  }
  // report on parameters
  std::cerr << "address: " << connection.address() 
            << ", remote port: " << connection.remote_port()
            << ", local port: " << connection.local_port() << std::endl;
  // wait until the connection is ready to go - this is usually the longest delay
  if (!connection.connected())
  {
    std::cerr << "error whilst waiting to send: " << connection.message() << std::endl;
    return -2;
  }
  // send the URL request in HTTP version 1.0 protocol
  std::string request = 
    std::string("GET / HTTP/1.0\r\n") +
    std::string("User-Agent: tcp_test\r\n") + 
    std::string("\r\n");
  std::cerr << "sending request: " << request;
  while (!request.empty())
  {
    if (!connection.send_ready(1000000))
    {
      std::cerr << "error whilst waiting to send: " << connection.message() << std::endl;
      return -2;
    }
    if (!connection.send(request))
    {
      std::cerr << "error whilst sending: " << connection.message() << std::endl;
      return -3;
    }
  }
  // now fetch the response and write it to the screen
  std::string returned;
  while (connection.receive_ready(1000000))
  {
    if (!connection.receive(returned))
    {
      std::cerr << "receive failed: " << connection.message() << std::endl;
      return -4;
    }
  }
  if (!connection.initialised())
  {
    std::cerr << "connection has closed" << std::endl;
  }
  std::cerr << "received \"" << returned << "\"" << std::endl;
  return 0;
}
