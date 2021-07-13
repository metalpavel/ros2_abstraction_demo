/// Text receiver ROS2 implementation.
#pragma once

#include "src/interfaces/i_receiver.h"
#include "src/common/message_text.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>

class ReceiverText final : public IReceiver
{
public:
    ReceiverText(std::shared_ptr<rclcpp::Node> node, const std::string &topic) : receiverTopic(topic)
    {
        subscription = node->create_subscription<std_msgs::msg::String>(
            topic, 10, std::bind(&ReceiverText::callback, this, std::placeholders::_1));
    }

    bool isValid() const override { return subscription != nullptr; }

    std::string getTopic() const override { return receiverTopic; }

private:
    void callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        if (onMessageReceive)
            onMessageReceive(std::make_shared<MessageText>(msg->data));
    }

    std::string receiverTopic;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
};