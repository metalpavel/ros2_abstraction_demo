/// Socket factory implementation.
#pragma once

#include "src/interfaces/i_factory.h"

#include "receiver_text_socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>

#include <thread>
#include <mutex>
#include <atomic>

class FactorySocket final : public IFactory
{
public:
    FactorySocket(const std::string &nodeName);
    ~FactorySocket();

    std::shared_ptr<IReceiver> makeReceiver(const std::string &topic) override;

    std::shared_ptr<ISender> makeSender(const std::string &topic) override;

    std::shared_ptr<IMessage> makeMessage(const std::string &text) override;

    void update() override;

    bool isActive() override;

private:
    int socketDescriptor{-1};

    sockaddr_in addr;
    sockaddr_in senderaddr;

    std::vector<std::shared_ptr<ReceiverTextSocket>> receivers;

    std::thread receiverThread;
    std::mutex receiverMutex;
    std::atomic_int active;

    std::vector<char> receivedBuffer;

    bool isClient{false};
};

std::shared_ptr<IFactory> makeFactory(int argc, char *argv[]);