//
// Created by xRoBoTx on 22.11.2019.
//

#ifndef SERVERBACKEND_RESPONSES_H
#define SERVERBACKEND_RESPONSES_H

#include "databaseController.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

using namespace Pistache;
using namespace std;
using namespace rapidjson;

namespace Responses {

    int rRegister(const Http::Request &request) {
        Document document;
        document.Parse(request.body().c_str());

        string nickname = document["nickname"].GetString();
        string password = document["password"].GetString();
        string avatar = document["avatar"].GetString();

        string sql = "INSERT INTO public.user (user_id, nickname, password, avatar) VALUES (uuid_generate_v4(), " +
                     ControllerDB::chatDBWork->quote(nickname) + ", " + ControllerDB::chatDBWork->quote(password) +
                     ", " + ControllerDB::chatDBWork->quote(avatar) + ")";

        //cout << sql << endl;

        try {
            ControllerDB::chatDBWork->exec0(sql);
            ControllerDB::chatDBWork->commit();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);
        }

        catch (const pqxx::sql_error &e) {
            ControllerDB::chatDBWork->abort();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);
            cerr << "SQL error: " << e.what() << endl
                 << "Query was: " << e.query() << endl;
            return -1;
        }

        return 0;
    }

    int rLogin(const Http::Request &request, User &user) {
        string nickname = request.headers().getRaw("nickname").value();
        string password = request.headers().getRaw("password").value();

        string sql = "SELECT nickname FROM public.user WHERE nickname=" + ControllerDB::chatDBWork->quote(nickname) +
                     " AND password=" + ControllerDB::chatDBWork->quote(password);

        //cout << sql << endl;

        try {
            ControllerDB::chatDBWork->exec1(sql);
            ControllerDB::chatDBWork->commit();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);

            //Get user ID
            sql = "SELECT user_id, avatar FROM public.user WHERE nickname=" + ControllerDB::chatDBWork->quote(nickname);

            cout << sql << endl;

            pqxx::result result = ControllerDB::chatDBWork->exec(sql);
            ControllerDB::chatDBWork->commit();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);

            user.id = result[0][0].as<std::string>();
            user.avatar = result[0][1].as<std::string>();
        }

        catch (const std::exception &e) {
            cerr << "Exception: " << e.what() << endl;
            return -1;
        }

        cout << request.body() << endl;
        return 0;
    }

    int rRoomAdd(const Http::Request &request) {
        Document document;
        document.Parse(request.body().c_str());

        string room_name = document["room_name"].GetString();
        string nickname = document["nickname"].GetString();
        string password = document["password"].GetString();

        string sql = "SELECT user_id FROM public.user WHERE nickname=" + ControllerDB::chatDBWork->quote(nickname);

        pqxx::result result = ControllerDB::chatDBWork->exec(sql);
        ControllerDB::chatDBWork->commit();
        ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);

        string id = result[0][0].as<std::string>();

        sql = "INSERT INTO public.room (room_id, user_admin_id, user_count, room_name) VALUES (uuid_generate_v4(), " +
              ControllerDB::chatDBWork->quote(id) + ", " + ControllerDB::chatDBWork->quote(1) +
              ", " + ControllerDB::chatDBWork->quote(room_name) + ")";

        try {
            ControllerDB::chatDBWork->exec0(sql);
            ControllerDB::chatDBWork->commit();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);
        }

        catch (const pqxx::sql_error &e) {
            ControllerDB::chatDBWork->abort();
            ControllerDB::chatDBWork = new pqxx::work(*ControllerDB::chatDB);
            cerr << "SQL error: " << e.what() << endl
                 << "Query was: " << e.query() << endl;
            return -1;
        }

        return 0;
    }
}

#endif //SERVERBACKEND_RESPONSES_H
