#include <iostream>
#include <iomanip>
#include <pistache/endpoint.h>
#include "../utils/utils.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace Pistache;
using namespace std;

class RequestHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)

    //Request
    void onRequest(const Http::Request& request, Http::ResponseWriter response) override{
        UNUSED(request)

        auto hostIP = response.peer().get()->address().host();

        response.headers().add<Http::Header::Server>("Pistache/0.1");

        if (request.resource() == "/ip" && request.method() == Http::Method::Get) {
            response.send(Pistache::Http::Code::Ok, "IP: " + hostIP);
        } else if (request.resource() == "/osinfo" && request.method() == Http::Method::Get) {
            Http::serveFile(response, "lsb.txt");
        } else
            response.send(Pistache::Http::Code::Forbidden, "There's nothing here =_=");

        cout << "IP: " << hostIP << endl;
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

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<RequestHandler>());
    server.serve();

    return 0;
}