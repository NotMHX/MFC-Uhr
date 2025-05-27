#pragma once

namespace Messerli::HerrmannUhr::Data {

enum class TimeZones {
    PST = 0,    // USA Pacific Time
    EST,        // USA Eastern Time
    UTC,        // Coordinated Universal Time
    CET,        // Central European Time
    MSK,        // Moscow Standard Time
    CST,        // China Standard Time
    JST,        // Japan Standard Time
    AET         // Australian Eastern Time
};

extern const std::vector<std::pair<TimeZones, CString>> TimeZoneVec;
}