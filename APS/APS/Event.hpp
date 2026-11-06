// Event.hpp
#pragma once

#include <memory>

enum class EventType {
    SERVICE_END = 0,
    ARRIVAL = 1
};

class SimulationEngine; // forward declaration
class Request;          // forward declaration

class Event {
public:
    virtual ~Event() = default;

    virtual void handle(SimulationEngine& engine) = 0;
    virtual EventType getType() const = 0;

    double getTime() const { return time_; }

protected:
    explicit Event(double time) : time_(time) {}

private:
    double time_;
};

class ArrivalEvent : public Event {
public:
    ArrivalEvent(double time, std::unique_ptr<Request> req)
        : Event(time), request_(std::move(req)) {
    }

    void handle(SimulationEngine& engine) override {

    }

    EventType getType() const override { return EventType::ARRIVAL; }

    std::unique_ptr<Request> getRequest() { return std::move(request_); }

private:
    std::unique_ptr<Request> request_;
};

class ServiceEndEvent : public Event {
public:
    ServiceEndEvent(double time, int deviceId)
        : Event(time), deviceId_(deviceId) {
    }

    void handle(SimulationEngine& engine) override {

    }

    EventType getType() const override { return EventType::SERVICE_END; }

    int getDeviceId() const { return deviceId_; }

private:
    int deviceId_;
};