//
// Created by xRoBoTx on 22.11.2019.
//

#ifndef SERVERBACKEND_RESPONCES_H
#define SERVERBACKEND_RESPONCES_H

#include
#include "databaseController.h"

using namespace Pistache;
using namespace std;
using namespace rapidjson;

namespace Responces {
    void rChat(const Http::Request &request) {
        auto messageReciveTime = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(messageReciveTime);
        Document document;
        document.Parse(request.body().c_str());
        /*msg.nickname = document["nickname"].GetString();
        msg.text = document["message"].GetString();
        messagesBuffer.push_back(msg);*/
        cout << ctime(&end_time) << endl;

        cout << request.body() << endl;
        //cout << msg.toJSONString() << endl;
    }

    void rRegister(const Http::Request &request) {
        Document document;
        document.Parse(request.body().c_str());

        string user_id = "";
        string nickname = document["nickname"].GetString();
        string password = document["password"].GetString();
        string avatar = document["avatar"].GetString();


        ControllerDB::chatDBWork.exec0(
                "INSERT INTO public.user (user_id, nickname, password, avatar) VALUES ('" + user_id + "', '" +
                nickname + "', '" + password + "', '" + avatar + "'");

        /*pqxx::connection chatDB("dbname = Chat user = Admin password = 228995 hostaddr = 127.0.0.1 port = 5432");

        pqxx::work chatDBWork(chatDB);*/

        //chatDBWork.exec()


        /*FILE* file = fopen("test.json", "w");
        char writeBuffer[65536];
        FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

        Writer<FileWriteStream> writer(os);
        document.Accept(writer);*/

        //fclose(file);

        cout << request.body() << endl;
    }
}

#endif //SERVERBACKEND_RESPONCES_H
