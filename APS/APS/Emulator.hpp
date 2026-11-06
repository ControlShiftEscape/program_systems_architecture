// Emulator.hpp
#pragma once

#include <memory>

class Payload;
class EmulatorContext;

class Emulator {
public:
    virtual ~Emulator() = default;
    virtual std::unique_ptr<Payload> emulate(const EmulatorContext& context) = 0;
};