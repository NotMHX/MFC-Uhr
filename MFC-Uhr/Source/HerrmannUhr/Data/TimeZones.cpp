#include "pch.h"

#include <vector>
#include "HerrmannUhr/Data/TimeZones.h"

namespace Messerli::HerrmannUhr::Data {

const std::vector<std::pair<TimeZones, CString>> TimeZoneVec = {
    {TimeZones::PST, _T("Los Angeles")},
    {TimeZones::EST, _T("New York")},
    {TimeZones::UTC, _T("UTC")},
    {TimeZones::CET, _T("Zürich")},
    {TimeZones::MSK, _T("Moskau")},
    {TimeZones::CST, _T("Shanghai")},
    {TimeZones::JST, _T("Tokio")},
    {TimeZones::AET, _T("Sydney")}
};

}