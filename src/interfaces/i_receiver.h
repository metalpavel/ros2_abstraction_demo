/// Abstraction interface for messages receiving.
#pragma once

#include "i_message.h"

#include <memory>
#include <functional>

class IReceiver
{
public:
    virtual ~IReceiver() = default;

    virtual bool isValid() const = 0;

    virtual std::string getTopic() const = 0;

    std::function<void(std::shared_ptr<IMessage> message)> onMessageReceive;
};