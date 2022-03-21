/*
 * Simple MQTT Client
 *
 * Copyright (C) 2022 Marc S. Ressl
 */

#include <string>
#include <vector>

#include <mosquitto.h>

class MQTTMessage
{
public:
    std::string topic;
    std::vector<char> payload;
};

class MQTTClient
{
public:
    MQTTClient();
    ~MQTTClient();

    bool connect(std::string host, std::string username, std::string password);
    bool isConnected();
    void disconnect();

    bool publish(std::string topic, std::vector<char> &payload);

    bool subscribe(std::string topic);
    bool unsubscribe(std::string topic);

    std::vector<MQTTMessage> getMessages();

private:
    struct mosquitto *mosquittoInstance;
    bool connected;

    std::vector<MQTTMessage> lastMessages;

    friend void onMQTTMessage(struct mosquitto *mosquittoClient,
                              void *context,
                              const struct mosquitto_message *message);
};
