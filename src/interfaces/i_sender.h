/// Abstraction interface for messages sender.
#pragma once

#include "i_message.h"

#include <memory>

class ISender
{
public:
    virtual ~ISender() = default;

    virtual bool isValid() const = 0;

    virtual std::string getTopic() const = 0;

    virtual void publish(std::shared_ptr<IMessage> message) = 0;
};