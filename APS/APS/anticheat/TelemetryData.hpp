// TelemetryData.hpp
#pragma once

#include <map>
#include <string>
#include <vector>

#include "../Payload.hpp"
#include "../Primitives.hpp"

class TelemetryData : public Payload {
public:
    TelemetryData(int playerId,
        double tickTimestamp,
        std::vector<Point3D> positionSamples,
        std::vector<Vector3D> movementVectors,
        double maxSpeed100ms,
        double aimJitterScore)
        : playerId_(playerId),
        tickTimestamp_(tickTimestamp),
        positionSamples_(std::move(positionSamples)),
        movementVectors_(std::move(movementVectors)),
        maxSpeed100ms_(maxSpeed100ms),
        aimJitterScore_(aimJitterScore) {
    }

    int getPlayerId() const { return playerId_; }
    double getTimestamp() const override { return tickTimestamp_; }

    std::map<std::string, double> getMetrics() const {
        return {
            {"maxSpeed100ms", maxSpeed100ms_},
            {"aimJitterScore", aimJitterScore_}
        };
    }

    // Нужны анализатору: через интерфейс Payload эти данные не достать
    const std::vector<Point3D>& getPositionSamples() const { return positionSamples_; }
    const std::vector<Vector3D>& getMovementVectors() const { return movementVectors_; }

    double getMaxSpeed100ms() const noexcept {
        return maxSpeed100ms_;
    }

    double getAimJitterScore() const noexcept {
        return aimJitterScore_;
    }

private:
    int playerId_;
    double tickTimestamp_;
    std::vector<Point3D> positionSamples_;
    std::vector<Vector3D> movementVectors_;
    double maxSpeed100ms_;
    double aimJitterScore_;
};