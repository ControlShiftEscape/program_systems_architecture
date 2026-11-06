// PlayerProfile.cpp
#include "PlayerProfile.hpp"
#include "ACAnalysisResult.hpp"

void PlayerProfile::decayScore(double timePassed) {
    if (timePassed <= 0.0 || currentSuspicionScore_ <= 0.0) {
        return;
    }

    currentSuspicionScore_ *= std::exp(-decayRate_ * timePassed);

    currentSuspicionScore_ = std::max(0.0, currentSuspicionScore_);
}

void PlayerProfile::updateState() {
    if (currentSuspicionScore_ >= banThreshold_) {
        state_ = PlayerState::BANNED;
    }
    else if (currentSuspicionScore_ >= warningThreshold_) {
        state_ = PlayerState::WARNING;
    }
    else {
        state_ = PlayerState::NORMAL;
    }
}

void PlayerProfile::mergeResult(const ACAnalysisResult& result) {
    double timePassed = result.getTimestamp() - lastResultTime_;

    if (timePassed > 0.0) {
        decayScore(timePassed);
    }

    currentSuspicionScore_ = std::min(1.0, currentSuspicionScore_ + result.getSuspicionScore());

    lastResultTime_ = result.getTimestamp();
    updateState();
}