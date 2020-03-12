//
// Created by xRoBoTx on 12.03.2020.
//

#ifndef SERVERBACKEND_CHAT_SERVER_HPP
#define SERVERBACKEND_CHAT_SERVER_HPP

#include <iostream>
#include <ixwebsocket/IXSocket.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketServer.h>

using namespace ix;
using namespace std;

int serverStart(std::string &host) {
    ix::WebSocketServer server(10215, host);


    server.setOnConnectionCallback(
            [&server](std::shared_ptr<WebSocket> webSocket,
                      std::shared_ptr<ConnectionState> connectionState) {
                webSocket->setOnMessageCallback(
                        [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg) {
                            if (msg->type == ix::WebSocketMessageType::Open) {
                                std::cerr << "New connection" << std::endl;

                                // A connection state object is available, and has a default id
                                // You can subclass ConnectionState and pass an alternate factory
                                // to override it. It is useful if you want to store custom
                                // attributes per connection (authenticated bool flag, attributes, etc...)
                                std::cerr << "id: " << connectionState->getId() << std::endl;

                                // The uri the client did connect to.
                                std::cerr << "Uri: " << msg->openInfo.uri << std::endl;

                                std::cerr << "Headers:" << std::endl;
                                for (auto it : msg->openInfo.headers) {
                                    std::cerr << it.first << ": " << it.second << std::endl;
                                }
                            } else if (msg->type == ix::WebSocketMessageType::Message) {
                                //TODO Chat
                                time_t raw_time;
                                struct tm *time_info;
                                char message_time[64];

                                time(&raw_time);
                                time_info = localtime(&raw_time);

                                strftime(message_time, 64, "%H:%M:%S", time_info);

                                //string message_string = string("[") + string(message_time) + string("] ") + msg->str;
                                string message_string = string(message_time) + string("|") + msg->str;

                                std::cerr << "Received " << msg->wireSize << " bytes" << std::endl;

                                for (auto &&client : server.getClients()) {
                                    //if (client != webSocket)
                                    //{
                                    client->send(message_string, msg->binary, [](int current, int total) -> bool {
                                        std::cerr << "Step " << current << " out of " << total << std::endl;
                                        return true;
                                    });

                                    do {
                                        size_t bufferedAmount = client->bufferedAmount();
                                        std::cerr << bufferedAmount << " bytes left to be sent"
                                                  << std::endl;

                                        std::chrono::duration<double, std::milli> duration(10);
                                        std::this_thread::sleep_for(duration);
                                    } while (client->bufferedAmount() != 0);
                                    //}
                                }

                                //webSocket->send(msg->str, msg->binary);
                            }
                        }
                );
            }
    );

    auto res = server.listen();
    if (!res.first) {
        // Error handling
        std::cerr << res.second << std::endl;
        return 1;
    }

    // Run the server in the background. Server can be stoped by calling server.stop()
    server.start();
    //cout << "Server successfully started!" << endl;

// Block until server.stop() is called.
    server.wait();
}

#endif //SERVERBACKEND_CHAT_SERVER_HPP
