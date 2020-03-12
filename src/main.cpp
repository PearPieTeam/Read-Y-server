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
#include "../utils/chat.h"
#include "../utils/db_server/responses.h"

#include "../utils/chat_server/chat_server.hpp"

using namespace Pistache;
using namespace std;
using namespace rapidjson;

class RequestHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)

    //Request
    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        UNUSED(request)

        auto hostIP = response.peer().get()->address().host();

        //response.headers().add<Http::Header::Server>("Pistache/0.1");

        //TODO Routes

        if (request.resource() == "/ip" && request.method() == Http::Method::Get) {
            response.send(Http::Code::Ok, "IP: " + hostIP);
            return;
        }
        if (request.resource() == "/osinfo" && request.method() == Http::Method::Get) {
            Http::serveFile(response, "lsb.txt");
            return;
        }

        if (request.resource() == "/register" && request.method() == Http::Method::Post) {

            //cout << request.body() << endl;

            if (Responses::rRegister(request) == 0)
            response.send(Http::Code::Ok);
            else
                response.send(Http::Code::Bad_Request);
            return;
        }

        if (request.resource() == "/login" && request.method() == Http::Method::Get) {
            User user;
            if (Responses::rLogin(request, user) == 0) {
                Http::Cookie c("id", user.id);
                response.cookies().add(c);
                c = Http::Cookie("avatar", user.avatar);
                response.cookies().add(c);

                response.send(Http::Code::Ok);
            }
            else
                response.send(Http::Code::Unauthorized);
            return;
        }

        response.send(Http::Code::Forbidden, "There's nothing here =_=");
    }

    //Timeout
    void onTimeout(const Http::Request& reqest, Http::ResponseWriter response) override {
        UNUSED(reqest)
        response.send(Http::Code::Request_Timeout, "Timeout").then([=](ssize_t) { }, PrintException());
    }
};

using connection = pqxx::connection;
using work = pqxx::work;

void run(Http::Endpoint &server) {
    server.serve();
}

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