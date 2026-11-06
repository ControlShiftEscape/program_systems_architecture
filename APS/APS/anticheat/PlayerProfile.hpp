// PlayerProfile.hpp
#pragma once

#include <algorithm>
#include <cmath>
#include <string>

#include "PlayerState.h"

class ACAnalysisResult;

class PlayerProfile {
public:
    explicit PlayerProfile(int playerId, double sessionStartTime)
        : playerId_(playerId),
        state_(PlayerState::NORMAL),
        sessionStartTime_(sessionStartTime),
        currentSuspicionScore_(0.0),
        lastResultTime_(sessionStartTime) {
    }

    void mergeResult(const ACAnalysisResult& result);

    PlayerState getStatus() const noexcept {
        return state_;
    }

    int getPlayerId() const noexcept { return playerId_; }
    double getCurrentSuspicionScore() const noexcept { return currentSuspicionScore_; }

private:
    void decayScore(double timePassed);

    void updateState();

    int playerId_;
    PlayerState state_;
    double sessionStartTime_;
    double currentSuspicionScore_;

    double lastResultTime_;

    static constexpr double banThreshold_ = 0.95;
    static constexpr double warningThreshold_ = 0.50;

    static constexpr double decayRate_ = 0.05;
};