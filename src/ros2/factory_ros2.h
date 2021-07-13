/// ROS2 factory implementation.
#pragma once

#include "src/interfaces/i_factory.h"

#include "rclcpp/rclcpp.hpp"

class FactoryRos2 final : public IFactory
{
public:
    FactoryRos2(const std::string &nodeName);
    ~FactoryRos2();

    std::shared_ptr<IReceiver> makeReceiver(const std::string &topic) override;

    std::shared_ptr<ISender> makeSender(const std::string &topic) override;

    std::shared_ptr<IMessage> makeMessage(const std::string &text) override;

    void update() override;

    bool isActive() override;

private:
    std::shared_ptr<rclcpp::Node> node;
};

std::shared_ptr<IFactory> makeFactory(int argc, char *argv[]);