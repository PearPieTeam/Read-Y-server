#include <iostream>
#include <iomanip>
#include <fstream>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include "../utils/utils.h"
#include "../utils/base64.h"
#include "../utils/executor.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filewritestream.h>
#include "../utils/chat.h"
#include "../utils/responces.h"

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

        //Chat
        if (request.resource() == "/chat" && request.method() == Http::Method::Post) {
            Responces::rChat(request);
            return;
        }

        if (request.resource() == "/register" && request.method() == Http::Method::Post) {
            Responces::rRegister(request);
            response.send(Http::Code::Ok);
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

int main() {
    cout << "Server started!" << endl;

    //connection chatDB = DataBaseUtils::establishConnection();

    //work chatDBWork = DataBaseUtils::startWork(static_cast<connection &&>(chatDB));

    /*connection c("dbname = Chat user = Admin password = 228995 hostaddr = 127.0.0.1 port = 5432");

    work w(c);*/

    //cout << chatDB.server_version() << endl;

    /*pqxx::row r = w.exec1(
            "SELECT avatar "
            "FROM public.user "
            "WHERE user_id=123 ");*/

    /*chatDBWork.exec1(
            "SELECT Nickname "
            "FROM User ");*/

    //int g = r[0].as<int>();

    //cout << g << endl;





    //

    Utils::commandToFile("lsb_release -a", "lsb.txt");

    //TODO
    //DataBaseUtils::establishConnection();

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<RequestHandler>());
    server.serve();

    return 0;
}