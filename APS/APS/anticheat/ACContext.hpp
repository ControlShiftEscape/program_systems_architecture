// ACContext.hpp
#pragma once

#include "../EmulatorContext.hpp"

class ACContext : public EmulatorContext {
public:
    ACContext(int playerId, double cheatLevel, double currentTime)
        : playerId_(playerId),
        cheatLevel_(cheatLevel),
        currentTime_(currentTime) {
    }

    int getPlayerId() const noexcept { return playerId_; }
    double getCheatLevel() const noexcept { return cheatLevel_; }
    double getCurrentTime() const noexcept { return currentTime_; }

    void setCheatLevel(double level) noexcept { cheatLevel_ = level; }
    void setCurrentTime(double time) noexcept { currentTime_ = time; }

private:
    int playerId_;
    double cheatLevel_;
    double currentTime_;
};