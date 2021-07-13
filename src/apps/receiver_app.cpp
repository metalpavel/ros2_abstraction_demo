
#include "src/interfaces/i_factory.h"

#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
    auto factory = makeFactory(argc, argv);

    auto receiver = factory->makeReceiver("/hello/world/topic");

    receiver->onMessageReceive = [](std::shared_ptr<IMessage> message)
    {
        const auto data = message->getData();

        std::cout << "RECEIVED: " << std::string(data.begin(), data.end()) << "\n";
    };

    while (factory->isActive())
    {
        factory->update();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}