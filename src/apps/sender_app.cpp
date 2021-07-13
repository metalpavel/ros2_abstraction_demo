
#include "src/interfaces/i_factory.h"

#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
    auto factory = makeFactory(argc, argv);

    auto sender = factory->makeSender("/hello/world/topic");

    int counter = 0;

    while (factory->isActive())
    {
        const auto str = "message " + std::to_string(counter);

        auto message = factory->makeMessage(str);

        sender->publish(message);

        counter++;

        std::cout << "SENT: " << str << "\n";

        factory->update();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}