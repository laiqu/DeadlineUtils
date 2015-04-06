#include "Connections.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "need host and port\n"; 
        return -1;
    }   
    auto connection_ptr = get_connection(std::string(argv[1]), std::string(argv[2]));
    Connection& conn = *connection_ptr;
    if(!login(conn, "asf", "qwer")) {
        return -1;
    }
    conn << "KOKOJAMBO";
    std::cout << precommand(conn) << std::endl;
}
