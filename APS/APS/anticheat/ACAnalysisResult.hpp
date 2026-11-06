// ACAnalysisResult.hpp
#pragma once

#include <string>
#include <utility>

#include "../BaseAnalysisResult.hpp"

class ACAnalysisResult : public BaseAnalysisResult {
public:
    ACAnalysisResult(int playerId,
        double suspicionScore,
        std::string reason,
        double timestamp)
        : playerId_(playerId),
        suspicionScore_(suspicionScore),
        reason_(std::move(reason)),
        timestamp_(timestamp)
    {
        if (suspicionScore_ < 0.0) suspicionScore_ = 0.0;
        if (suspicionScore_ > 1.0) suspicionScore_ = 1.0;
    }

    double getTimestamp() const override {
        return timestamp_;
    }

    int getPlayerId() const noexcept {
        return playerId_;
    }

    double getSuspicionScore() const noexcept {
        return suspicionScore_;
    }

    const std::string& getReason() const noexcept {
        return reason_;
    }

private:
    int playerId_;
    double suspicionScore_;
    std::string reason_;
    double timestamp_;
};