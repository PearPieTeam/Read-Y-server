//
// Created by xRoBoTx on 22.11.2019.
//

#ifndef SERVERBACKEND_RESPONCES_H
#define SERVERBACKEND_RESPONCES_H

using namespace Pistache;
using namespace std;
using namespace rapidjson;

namespace Responces {
    void rChat(const Http::Request& request) {
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

    void rRegister(const Http::Request& request) {
        Document document;
        document.Parse(request.body().c_str());

        FILE* file = fopen("test.json", "w");
        char writeBuffer[65536];
        FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

        Writer<FileWriteStream> writer(os);
        document.Accept(writer);

        fclose(file);

        cout << request.body() << endl;
    }
}

#endif //SERVERBACKEND_RESPONCES_H
