#pragma once

enum class LogType {
    EVENT,
    GENERATION,
    BUFFER_WRITE,
    BUFFER_READ,
    REJECTION,
    SERVICE_START,
    SERVICE_END,
    STATE,
    STATISTICS
};

inline const char* toString(LogType type) {
    switch (type) {
    case LogType::EVENT:         return "EVENT";
    case LogType::GENERATION:    return "GENERATION";
    case LogType::BUFFER_WRITE:  return "BUFFER_WRITE";
    case LogType::BUFFER_READ:   return "BUFFER_READ";
    case LogType::REJECTION:     return "REJECTION";
    case LogType::SERVICE_START: return "SERVICE_START";
    case LogType::SERVICE_END:   return "SERVICE_END";
    case LogType::STATE:         return "STATE";
    case LogType::STATISTICS:    return "STATISTICS";
    }
    return "UNKNOWN";
}