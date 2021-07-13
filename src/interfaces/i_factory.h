/// Abstraction factory interface.
#pragma once

#include "i_receiver.h"
#include "i_sender.h"

#include <memory>

class IFactory
{
public:
    virtual ~IFactory() = default;

    virtual std::shared_ptr<IReceiver> makeReceiver(const std::string &topic) = 0;

    virtual std::shared_ptr<ISender> makeSender(const std::string &topic) = 0;

    virtual std::shared_ptr<IMessage> makeMessage(const std::string &text) = 0;

    virtual void update() = 0;

    virtual bool isActive() = 0;
};

extern std::shared_ptr<IFactory> makeFactory(int argc, char *argv[]);