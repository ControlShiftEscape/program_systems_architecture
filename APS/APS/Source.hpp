// Source.hpp
#pragma once

#include <memory>
#include <random>

#include "Request.hpp"
#include "Emulator.hpp"
#include "EmulatorContext.hpp"
#include "anticheat/ACContext.hpp"

class Source {
public:
    Source(int id, double lambda, Emulator& emulator, EmulatorContext& context)
        : id_(id),
        lambda_(lambda),
        emulator_(emulator),
        context_(context),
        rng_(std::random_device{}()),
        dist_(lambda) {
    }

    int getId() const noexcept { return id_; }

    double generateNextInterval() { 
        return dist_(rng_);
    }

    std::unique_ptr<Request> generateRequest(double currentTime) {
        dynamic_cast<ACContext&>(context_).setCurrentTime(currentTime);

        auto payload = emulator_.emulate(context_);

        return std::make_unique<Request>(
            nextRequestId_++,
            id_,
            currentTime,
            std::move(payload)
        );
    }

private:
    int id_;
    double lambda_;

    Emulator& emulator_;
    EmulatorContext& context_; 

    std::mt19937 rng_;
    std::exponential_distribution<double> dist_;

    int nextRequestId_ = 1; 
};