#pragma once

namespace Messerli::HerrmannUhr::Data {

struct DateDto {
    size_t seconds;
    size_t minutes;
    size_t hours;
    size_t day;
    size_t month;
    size_t year;
    CString timeZone;
};
}