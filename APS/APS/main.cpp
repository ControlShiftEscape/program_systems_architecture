// main.cpp (или метод инициализации SimulationEngine)
#include <iostream>
#include <vector>
#include <memory>

#include "Source.hpp"
#include "anticheat/TelemetryEmulator.hpp"
#include "anticheat/ACContext.hpp"

int main() {
    TelemetryEmulator globalEmulator;

    ACContext legitPlayerCtx(1, 0.1, 0.0);    // Ќормис (10% подозрительности)
    ACContext susPlayerCtx(2, 0.5, 0.0);      // ѕодозрительный (50%)
    ACContext cheaterCtx(3, 0.95, 0.0);       // „итер (95%)

    // 3. —оздаем источники (игроков). 
    // lambda = 10.0 означает в среднем 10 за€вок в единицу времени (тикрейт)
    Source player1(1, 10.0, globalEmulator, legitPlayerCtx);
    Source player2(2, 10.0, globalEmulator, susPlayerCtx);
    Source player3(3, 10.0, globalEmulator, cheaterCtx);



    return 0;
}