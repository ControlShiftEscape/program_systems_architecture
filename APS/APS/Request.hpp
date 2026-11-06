// Request.hpp
#pragma once

#include <memory>
#include <utility>

#include "Payload.hpp"

class Request {
public:
    Request(int id, int sourceId, double generationTime,
        std::unique_ptr<Payload> payload)
        : id_(id),
        sourceId_(sourceId),
        generationTime_(generationTime),
        payload_(std::move(payload)) {
    }

    // Из-за unique_ptr копировать нельзя, только перемещать
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;
    Request(Request&&) = default;
    Request& operator=(Request&&) = default;


    double getAge(double currentTime) const { return currentTime - generationTime_; }
    const Payload& getPayload() const { return *payload_; }

    int getId() const { return id_; }
    int getSourceId() const { return sourceId_; }
    double getGenerationTime() const { return generationTime_; }

private:
    int id_;
    int sourceId_;

    // считаем, что время генерации заявки и время ее прибытия в центр распределения
    // на диспетчеры, то есть в SimulationEngine, - это одно и то же
    double generationTime_;

    // вполне логично утвердить, что никто кроме данной заявки
    // владеть данными этого запроса не будет
    std::unique_ptr<Payload> payload_;
};