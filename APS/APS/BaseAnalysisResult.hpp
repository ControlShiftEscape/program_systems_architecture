#pragma once

class BaseAnalysisResult {
public:
    virtual ~BaseAnalysisResult() = default;

    virtual double getTimestamp() const = 0;
};