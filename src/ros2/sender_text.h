/// Text sender ROS2 implementation.
#pragma once

#include "src/interfaces/i_sender.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>

class SenderText final : public ISender
{
public:
    SenderText(std::shared_ptr<rclcpp::Node> node, const std::string &topic) : senderTopic(topic)
    {
        publisher = node->create_publisher<std_msgs::msg::String>(topic, 10);
    }

    bool isValid() const override { return publisher != nullptr; }

    std::string getTopic() const override { return senderTopic; }

    void publish(std::shared_ptr<IMessage> message) override
    {
        const auto data = message->getData();

        std_msgs::msg::String msg;
        msg.data = std::string{data.begin(), data.end()};

        publisher->publish(msg);
    }

private:
    std::string senderTopic;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
};