// LogSystem.hpp
#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "LogType.hpp"

class Log {
public:
    Log(double date, std::string logContent)
        : date_(date), logContent_(std::move(logContent)) {
    }

    const std::string& getLogContent() const { return logContent_; }
    double getLogDate() const { return date_; }

private:
    double date_;
    std::string logContent_;
};

class Logger {
public:
    void log(LogType type, const Log& log) {
        logs_[type].push_back(log);
    }

    const std::vector<Log>& getLogs(LogType type) const {
        static const std::vector<Log> empty;
        auto it = logs_.find(type);
        return it != logs_.end() ? it->second : empty;
    }

    void clear() { logs_.clear(); }

    void printAll() const {
        for (const auto& pair : logs_) {
            LogType type = pair.first;
            const std::vector<Log>& entries = pair.second;

            std::cout << "=== " << toString(type) << " (" << entries.size() << ") ===\n";
            for (const auto& entry : entries) {
                std::cout << "[" << entry.getLogDate() << "] "
                    << entry.getLogContent() << '\n';
            }
        }
    }

private:

    std::map<LogType, std::vector<Log>> logs_;
};