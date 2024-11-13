#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 22354));
    
    while(true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      std::cout<<"Connection from: "<<socket.remote_endpoint().address().to_string()<<std::endl;
      std::string message = "AMOGUS SUS MFS";

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
