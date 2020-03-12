#include <iostream>
#include <iomanip>
#include <fstream>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include "../utils/utils.h"
#include "../utils/db_server/base64.h"
#include "../utils/executor.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filewritestream.h>

#include "../utils/chat_server/chat_server.hpp"
#include "../utils/db_server/request_handler.hpp"

using namespace Pistache;
using namespace std;
using namespace rapidjson;

using connection = pqxx::connection;
using work = pqxx::work;

int main() {
    Utils::commandToFile("lsb_release -a", "lsb.txt");

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    auto server = std::make_shared<Http::Endpoint>(addr);
    server->init(opts);
    server->setHandler(Http::make_handler<RequestHandler>());

    std::thread db_server_thread([&server] {
        server->serve();
    });

    cout << "DB server started successfully!" << endl;

    //TODO
    string host_address = "127.0.0.1";

    std::thread chat_server_thread([&host_address] {
        if (serverStart(host_address) == 1)
            return -1;
    });

    cout << "Chat server started successfully!" << endl;

    db_server_thread.join();
    chat_server_thread.join();

    return 0;
}