#pragma once

#include "HerrmannUhr/Painter/AbstractPainter.h"
#include "HerrmannUhr/Data/TimeZones.h"

#include <chrono>
#include <memory>
#include <functional>

namespace Messerli::HerrmannUhr {

using AddFn = std::function<void(int, int, CWnd*)>;

class UhrController {
public:
    UhrController(std::unique_ptr<Painter::AbstractPainter> p, Data::TimeZones tz, AddFn addFn);

    auto UpdateClock(CDC& client) -> void;

    auto AddDialog(int appearanceIndex, int timeZoneIndex, CWnd* wnd) -> void;

private:
    auto SetZonedTime(Data::TimeZones tz) -> void;

    std::unique_ptr<Painter::AbstractPainter> m_painter;
    Data::TimeZones m_timeZone;
    AddFn m_addDialogFunction;

    std::chrono::zoned_seconds m_time;
};
}