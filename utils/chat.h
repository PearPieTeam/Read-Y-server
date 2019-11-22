//
// Created by xRoBoTx on 18.11.2019.
//

#ifndef SERVERBACKEND_CHAT_H
#define SERVERBACKEND_CHAT_H

namespace Chat {
    class Message {
    public:
        string nickname;
        string text;

        string toJSONString() {
            return string("{\"nickname\":\"") + nickname + string("\",\"message\":\"") + text + string("\"}");
        }
    };
}

#endif //SERVERBACKEND_CHAT_H
