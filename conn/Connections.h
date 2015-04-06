#include <memory>
#include <iostream>
#include <boost/asio.hpp>
typedef boost::asio::ip::tcp::iostream Connection;
std::shared_ptr<Connection> get_connection(std::string host, std::string port) {
    std::cerr << "Connecting to " << host << " " << port << std::endl;
    auto conn = std::make_shared<Connection>();
    conn->connect(host, port);
    if (!conn->good()) {
        std::cerr << "Connection fail: " << conn->error().message() << std::endl;
        throw std::string("connection isn't good :(");
    }
    boost::asio::ip::tcp::no_delay opt(true);
    conn->rdbuf()->set_option(opt);
    return conn;
} 

bool starts_with(std::string& str, std::string prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.substr(0, prefix.length()) == str;
}

bool login(Connection& conn, std::string name, std::string pass) {
    std::string msg;
    conn >> msg;
    if (msg != "LOGIN") {
        std::cerr << "Login fail: " << msg << std::endl;
        return false;
    }
    conn << name;
    conn >> msg;
    if (msg != "PASS") {
        std::cerr << "Login fail: " << msg << std::endl;
        return false;
    }
    conn << pass;
    conn >> msg;
    if (msg != "OK") {
        std::cerr << "Login fail: " << msg << std::endl;
        return false;
    }
    return true;
}
bool precommand(Connection& conn) {
    std::string msg;
    conn >> msg;
    if (msg != "OK") {
        std::cerr << "Precommand fail: " << msg;
        return false;
    }
    return true;
}
