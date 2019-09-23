#include <iostream>
#include <iomanip>
#include <fstream>
#include <pistache/endpoint.h>
#include "../utils/utils.h"
#include "../utils/base64.h"
#include "../utils/base64.cpp"
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

            Document document;
            document.Parse(request.body().c_str());

            FILE* file = fopen("test.json", "w");
            char writeBuffer[65536];
            FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

            Writer<FileWriteStream> writer(os);
            document.Accept(writer);

            fclose(file);


            cout << request.body() << endl;

            response.send(Http::Code::Ok);
        }
        else if (request.resource() == "/compile/cpp" && request.method() == Http::Method::Post) {

            Document document;
            document.Parse(request.body().c_str());

            if (!document.HasMember("program") || (!document["program"].HasMember("arguments") || !document["program"].HasMember("base64") || !document["program"].HasMember("output_file"))) {
                response.send(Http::Code::Bad_Request);
                return;
            }

            if (!document.HasMember("dependencies") || (!document["dependencies"].HasMember("file_name") || !document["dependencies"].HasMember("base64"))) {
                response.send(Http::Code::Bad_Request);
                return;
            }

                string program_compile_args = document["program"]["arguments"].GetString();
                string base64_file = document["program"]["base64"].GetString();
                string output_file_name = document["program"]["output_file"].GetString();

                string dependency_file_name = document["dependencies"]["file_name"].GetString();
                string dependency_base64_file = document["dependencies"]["base64"].GetString();

            /*FILE* fp = fopen("request.json", "w");
            char writeBuffer[65536];
            FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

            Writer<FileWriteStream> writer(os);
            document.Accept(writer);

            fclose(fp);*/

            //base64 decoding and writing to file
            string decodedString;

            decodedString = Base64::decode(base64_file.c_str(), base64_file.size());

            ofstream file;
            file.open("files/input_file.cpp");
            if (file.is_open()) {
                file.write(decodedString.c_str(), decodedString.length());
                file.close();
            }

            decodedString = Base64::decode(dependency_base64_file.c_str(), dependency_base64_file.size());

            file.open("files/" + dependency_file_name);
            if (file.is_open()) {
                file.write(decodedString.c_str(), decodedString.length());
                file.close();
            }

            //Construct build command and run it
            string build_command("g++ " + program_compile_args + " files/input_file.cpp" + " -o " + "files/" + output_file_name);

            if (system(build_command.c_str()))
            {
                response.send(Http::Code::I_m_a_teapot);
                return;
            }

            //cout << decodedString << endl;

            //cout << request.body() << endl;

            response.send(Http::Code::Ok);
        }
        else
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