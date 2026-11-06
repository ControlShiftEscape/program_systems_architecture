// RingBuffer.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Request.hpp"

class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity)
        : capacity_(capacity), slots_(capacity) {
        if (capacity == 0)
            throw std::invalid_argument("RingBuffer: capacity must be > 0");
    }

    bool isFull() const { return count_ == capacity_; }
    bool isEmpty() const { return count_ == 0; }
    std::size_t size() const { return count_; }
    std::size_t getCapacity() const { return capacity_; }

    // ƒ10«1 + ƒ10ќ3.
    // ѕишет за€вку в слот writePointer_.
    // ≈сли буфер полон, сначала вытесн€етс€ сама€ стара€ за€вка (она лежит
    // в readPointer_), и readPointer_ сдвигаетс€ за неЄ.
    // ¬озвращает вытесненную за€вку (чтобы вызывающий залогировал отказ
    // и учЄл его в статистике) или nullptr, если вытеснени€ не было.
    std::unique_ptr<Request> write(std::unique_ptr<Request> req) {
        if (!req)
            throw std::invalid_argument("RingBuffer::write: null request");

        std::unique_ptr<Request> rejected;
        if (isFull()) {
            rejected = std::move(slots_[readPointer_]);
            next(readPointer_);
            // здесь было прин€то решение сдвигать readPointer если места не хватает
            // иначе нужно будет это делать в самом read, тогда нужно будет 
            // считать разницу между capacity и max_capacity или что то такое
            // короче не оч вариант

            --count_;
        }

        slots_[writePointer_] = std::move(req);
        next(writePointer_);
        ++count_;
        return rejected;
    }

    // ƒ2Ѕ3: извлекает за€вку из readPointer_ и сдвигает указатель.
    // ≈сли буфер пуст, возвращает nullptr.
    std::unique_ptr<Request> readNext() {
        if (isEmpty()) return nullptr;

        auto req = std::move(slots_[readPointer_]);
        next(readPointer_);
        --count_;
        return req;
    }

    // —ама€ стара€ за€вка, только просмотр. nullptr, если буфер пуст.
    const Request* findOldest() const {
        return isEmpty() ? nullptr : slots_[readPointer_].get();
    }

private:
    void next(std::size_t& i) const { i = (i + 1) % capacity_; }

    std::size_t capacity_;
    std::vector<std::unique_ptr<Request>> slots_;
    std::size_t writePointer_ = 0;  // по сути указывает на следующий индекс дл€ записи
    std::size_t readPointer_ = 0;   // указывает на индекс, откуда будет сделано следующее чтение
    std::size_t count_ = 0;
};