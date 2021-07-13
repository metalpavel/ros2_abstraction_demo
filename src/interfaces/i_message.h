/// Abstraction interface for message.
#pragma once

#include <vector>
#include <cstdint>

class IMessage
{
public:
    virtual ~IMessage() = default;

    virtual uint32_t size() const = 0;

    virtual std::vector<char> getData() const = 0;
};