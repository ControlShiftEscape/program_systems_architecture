// TelemetryEmulator.hpp
#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "../Emulator.hpp"
#include "ACContext.hpp"
#include "TelemetryData.hpp"

class TelemetryEmulator : public Emulator {
public:
    std::unique_ptr<Payload> emulate(const EmulatorContext& context) override {
        const ACContext& ac = dynamic_cast<const ACContext&>(context);

        double level = std::max(0.0, std::min(ac.getCheatLevel(), 1.0));

        std::vector<Point3D> positions;
        std::vector<Vector3D> vectors;
        double maxSpeed = 0.0;
        double aimJitter = 0.0;

        if (level < 0.3) {
            positions = { {0.0, 0.0, 0.0} };
            vectors = { {0.0, 0.0, 0.0} };
            maxSpeed = 5.0;
            aimJitter = 0.1;
        }
        else if (level < 0.7) {
            positions = { {0.0, 0.0, 0.0}, {1.0, 1.0, 0.0} };
            vectors = { {1.0, 1.0, 0.0} };
            maxSpeed = 10.0;
            aimJitter = 0.5;
        }
        else {
            positions = { {0.0, 0.0, 0.0}, {100.0, 100.0, 100.0} };
            vectors = { {100.0, 100.0, 100.0} };
            maxSpeed = 500.0;
            aimJitter = 0.95;
        }

        return std::make_unique<TelemetryData>(
            ac.getPlayerId(),
            ac.getCurrentTime(),
            std::move(positions),
            std::move(vectors),
            maxSpeed,
            aimJitter
        );
    }
};