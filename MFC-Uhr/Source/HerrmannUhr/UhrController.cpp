#include "pch.h"
#include "HerrmannUhr/UhrController.h"

#include "HerrmannUhr/Painter/PainterFacility.h"
#include "HerrmannUhr/Data/Appearances.h"
#include "HerrmannUhr/Data/DateDto.h"
#include "HerrmannUhr/UhrDlg.h"

#include <string>
#include <memory>

namespace Messerli::HerrmannUhr {

UhrController::UhrController(std::unique_ptr<Painter::AbstractPainter> p, Data::TimeZones tz, AddFn addFn)
    : m_painter(std::move(p)), m_timeZone(tz), m_addDialogFunction(addFn)
{
}

auto UhrController::UpdateClock(CDC& client) -> void
{
    SetZonedTime(m_timeZone);

    // Get the local time point
    auto localTime = m_time.get_local_time();
    auto dp = std::chrono::floor<std::chrono::days>(localTime);

    // Extract date
    Data::DateDto dto;
    std::chrono::year_month_day date {dp};
    dto.year = int(date.year());
    dto.month = unsigned(date.month());
    dto.day = unsigned(date.day());

    // Extract hour, minute, second
    auto time = std::chrono::hh_mm_ss(localTime - dp);
    dto.hours = time.hours().count();
    dto.minutes = time.minutes().count();
    dto.seconds = time.seconds().count();

    const auto comparer = [this](const auto& p) {
        return p.first == m_timeZone;
        };
    auto iterator = std::find_if(Data::TimeZoneVec.cbegin(), Data::TimeZoneVec.cend(), comparer);
    dto.timeZone = (*iterator).second;

    m_painter->Paint(dto, client);
}

auto UhrController::AddDialog(int appearanceIndex, int timeZoneIndex, CWnd* wnd) -> void
{
    m_addDialogFunction(appearanceIndex, timeZoneIndex, wnd);
}

auto UhrController::SetZonedTime(Data::TimeZones tz) -> void
{
    std::string_view location;

    switch (tz) {
        case Data::TimeZones::PST:
            location = "America/Los_Angeles";
            break;
        case Data::TimeZones::EST:
            location = "America/New_York";
            break;
        case Data::TimeZones::UTC:
            location = "UTC";
            break;
        case Data::TimeZones::CET:
            location = "Europe/Zurich";
            break;
        case Data::TimeZones::MSK:
            location = "Europe/Moscow";
            break;
        case Data::TimeZones::CST:
            location = "Asia/Shanghai";
            break;
        case Data::TimeZones::JST:
            location = "Asia/Tokyo";
            break;
        case Data::TimeZones::AET:
            location = "Oceania/Sydney";
            break;
    }

    std::chrono::zoned_seconds zt(location, std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now()));
    m_time = zt;
}
}
