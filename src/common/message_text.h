/// Text message implementation.
#pragma once

#include "src/interfaces/i_message.h"

#include <string>
#include <vector>

class MessageText final : public IMessage
{
public:
    MessageText(const std::string &text) : buffer(text.begin(), text.end())
    {
    }

    uint32_t size() const override { return buffer.size(); }

    std::vector<char> getData() const override { return buffer; }

private:
    std::vector<char> buffer;
};