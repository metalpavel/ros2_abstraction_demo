/// Text sender socket implementation.
#pragma once

#include "src/interfaces/i_sender.h"

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class SenderTextSocket final : public ISender
{
public:
    SenderTextSocket(int socketDescriptor, const sockaddr *sockAddress, const std::string &topic)
        : senderTopic(topic), socketAddress(sockAddress), descriptor(socketDescriptor)
    {
    }

    bool isValid() const override { return descriptor >= 0 && socketAddress != nullptr; }

    std::string getTopic() const override { return senderTopic; }

    void publish(std::shared_ptr<IMessage> message) override
    {
        const auto data = message->getData();

        std::vector<char> buffer;

        // topic length
        buffer.push_back(senderTopic.size());

        buffer.insert(buffer.end(), senderTopic.begin(), senderTopic.end());

        // message length
        buffer.push_back(data.size());

        buffer.insert(buffer.end(), data.begin(), data.end());

        sendto(descriptor, buffer.data(), buffer.size(), 0, socketAddress, sizeof(sockaddr_in));
    }

private:
    std::string senderTopic;

    const sockaddr *socketAddress;

    int descriptor{0};
};