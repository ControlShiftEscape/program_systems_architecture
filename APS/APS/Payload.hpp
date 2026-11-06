// Payload.hpp
#pragma once

#include <map>
#include <string>

class Payload {
public:
    virtual ~Payload() = default;

    virtual double getTimestamp() const = 0;
};