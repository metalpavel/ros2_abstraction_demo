
#include "factory_socket.h"

#include "receiver_text_socket.h"
#include "sender_text_socket.h"
#include "src/common/message_text.h"

#include <iostream>
#include <cstring>

FactorySocket::FactorySocket(const std::string &nodeName)
{
    if ((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        std::cerr << "socket\n";
        return;
    }

    memset(&addr, 0, sizeof(addr));
    memset(&senderaddr, 0, sizeof(senderaddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_aton("127.0.0.1", &addr.sin_addr);

    senderaddr.sin_family = AF_INET;
    senderaddr.sin_port = htons(8889);
    inet_aton("127.0.0.1", &senderaddr.sin_addr);

    if (bind(socketDescriptor, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        if (bind(socketDescriptor, (struct sockaddr *)&senderaddr, sizeof(senderaddr)) == -1)
        {
            std::cerr << "bind\n";
            return;
        }

        isClient = true;
    }

    active = 1;

    receiverThread = std::thread([this]()
                                 {
                                     while (active == 1)
                                     {
                                         std::vector<char> buffer(1024);

                                         sockaddr_in otheraddr;
                                         memset(&otheraddr, 0, sizeof(otheraddr));

                                         socklen_t slen = 0;

                                         int receivedLen = recvfrom(socketDescriptor,
                                                                    buffer.data(), buffer.size(), 0,
                                                                    (struct sockaddr *)&otheraddr,
                                                                    &slen);

                                         if (receivedLen == -1)
                                         {
                                             std::cerr << "recvfrom\n";
                                             return;
                                         }

                                         std::lock_guard<std::mutex> lock(receiverMutex);

                                         receivedBuffer =
                                             std::vector<char>(buffer.begin(), buffer.begin() + receivedLen);
                                     }
                                 });
}

FactorySocket::~FactorySocket()
{
    active = 0;

    if (receiverThread.joinable())
        receiverThread.join();
}

std::shared_ptr<IReceiver> FactorySocket::makeReceiver(const std::string &topic)
{
    auto receiver = std::make_shared<ReceiverTextSocket>(topic);
    receivers.push_back(receiver);
    return receiver;
}

std::shared_ptr<ISender> FactorySocket::makeSender(const std::string &topic)
{
    return std::make_shared<SenderTextSocket>(socketDescriptor, (struct sockaddr *)&senderaddr, topic);
}

std::shared_ptr<IMessage> FactorySocket::makeMessage(const std::string &text)
{
    return std::make_shared<MessageText>(text);
}

void FactorySocket::update()
{
    std::lock_guard<std::mutex> lock(receiverMutex);

    if (receivedBuffer.empty())
        return;

    std::string topic;

    for (int i = 0; i < receivedBuffer[0]; ++i)
    {
        topic += receivedBuffer[i + 1];
    }

    std::string messageText;

    const int offset = topic.size() + 2;

    for (int i = 0; i < receivedBuffer[offset - 1]; ++i)
    {
        messageText += receivedBuffer[i + offset];
    }

    auto message = makeMessage(messageText);

    for (auto &receiver : receivers)
    {
        if (receiver->getTopic() == topic)
            receiver->received(message);
    }

    receivedBuffer.clear();
}

bool FactorySocket::isActive()
{
    return true;
}

std::shared_ptr<IFactory> makeFactory(int argc, char *argv[])
{
    std::cout << "Initializing Socket factory...\n";

    return std::make_shared<FactorySocket>("ros2_abstraction_demo");
}