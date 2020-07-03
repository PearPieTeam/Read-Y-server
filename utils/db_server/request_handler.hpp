//
// Created by xRoBoTx on 13.03.2020.
//

#ifndef SERVERBACKEND_REQUEST_HANDLER_HPP
#define SERVERBACKEND_REQUEST_HANDLER_HPP

#include <pistache/http.h>
#include "../utils.h"
#include "responses.h"

using namespace Pistache;

class RequestHandler : public Http::Handler {
public:
HTTP_PROTOTYPE(RequestHandler)

    //Request
    void onRequest(const Http::Request &request, Http::ResponseWriter response) override {
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
            } else
                response.send(Http::Code::Unauthorized);
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

        if (request.resource() == "/rooms/add" && request.method() == Http::Method::Post) {

            //cout << request.body() << endl;

            if (Responses::rRoomAdd(request) == 0)
                response.send(Http::Code::Ok);
            else
                response.send(Http::Code::Bad_Request);
            return;
        }

        response.send(Http::Code::Forbidden, "There's nothing here =_=");
    }

    //Timeout
    void onTimeout(const Http::Request &request, Http::ResponseWriter response) override {
        UNUSED(request)
        response.send(Http::Code::Request_Timeout, "Timeout").then([=](ssize_t) {}, PrintException());
    }
};

#endif //SERVERBACKEND_REQUEST_HANDLER_HPP
