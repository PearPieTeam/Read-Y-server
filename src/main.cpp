#include <iostream>
#include <iomanip>
#include <fstream>
#include <pistache/endpoint.h>
#include "../utils/utils.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filewritestream.h>

using namespace Pistache;
using namespace std;
using namespace rapidjson;

class RequestHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)

    //Request
    void onRequest(const Http::Request& request, Http::ResponseWriter response) override{
        UNUSED(request)

        auto hostIP = response.peer().get()->address().host();

        response.headers().add<Http::Header::Server>("Pistache/0.1");

        if (request.resource() == "/ip" && request.method() == Http::Method::Get) {
            response.send(Http::Code::Ok, "IP: " + hostIP);
        } else if (request.resource() == "/osinfo" && request.method() == Http::Method::Get) {
            Http::serveFile(response, "lsb.txt");
        }
        else if (request.resource() == "/register" && request.method() == Http::Method::Post) {

            /*Document document;
            document.Parse(request.body().c_str());

            FILE* fp = fopen("test.json", "w");
            char writeBuffer[65536];
            FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

            Writer<FileWriteStream> writer(os);
            document.Accept(writer);

            fclose(fp);*/



            cout << request.body() << endl;

            response.send(Http::Code::Ok);
        } else
            response.send(Http::Code::Forbidden, "There's nothing here =_=");
    }

    //Timeout
    void onTimeout(const Http::Request& reqest, Http::ResponseWriter response) override {
        UNUSED(reqest)
        response.send(Http::Code::Request_Timeout, "Timeout").then([=](ssize_t) { }, PrintException());
    }
};

int main() {
    cout << "Server started!" << endl;

    Utils::commandToFile("lsb_release -a", "lsb.txt");

    //TODO
    DataBaseUtils::establishConnection();

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<RequestHandler>());
    server.serve();

    return 0;
}