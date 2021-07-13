
#include "factory_ros2.h"

#include "receiver_text.h"
#include "sender_text.h"
#include "src/common/message_text.h"

#include <iostream>

FactoryRos2::FactoryRos2(const std::string &nodeName)
{
    node = std::make_shared<rclcpp::Node>(nodeName);
}

FactoryRos2::~FactoryRos2()
{
    rclcpp::shutdown();
}

std::shared_ptr<IReceiver> FactoryRos2::makeReceiver(const std::string &topic)
{
    return std::make_shared<ReceiverText>(node, topic);
}

std::shared_ptr<ISender> FactoryRos2::makeSender(const std::string &topic)
{
    return std::make_shared<SenderText>(node, topic);
}

std::shared_ptr<IMessage> FactoryRos2::makeMessage(const std::string &text)
{
    return std::make_shared<MessageText>(text);
}

void FactoryRos2::update()
{
    rclcpp::spin_some(node);
}

bool FactoryRos2::isActive()
{
    return rclcpp::ok();
}

std::shared_ptr<IFactory> makeFactory(int argc, char *argv[])
{
    std::cout << "Initializing ROS2 factory...\n";

    rclcpp::init(argc, argv);

    return std::make_shared<FactoryRos2>("ros2_abstraction_demo");
}