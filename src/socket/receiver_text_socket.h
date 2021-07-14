/// Text receiver socket implementation.
#pragma once

#include "src/interfaces/i_receiver.h"

#include <string>

class ReceiverTextSocket final : public IReceiver
{
public:
    ReceiverTextSocket(const std::string &topic) : receiverTopic(topic)
    {
    }

    bool isValid() const override { return !receiverTopic.empty(); }

    std::string getTopic() const override { return receiverTopic; }

    void received(std::shared_ptr<IMessage> message)
    {
        if (onMessageReceive)
            onMessageReceive(message);
    }

private:
    std::string receiverTopic;
};