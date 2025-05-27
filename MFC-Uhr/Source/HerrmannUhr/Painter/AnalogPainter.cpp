#include "pch.h"
#include "HerrmannUhr/Painter/AnalogPainter.h"

#include <numbers>

namespace Messerli::HerrmannUhr::Painter {

AnalogPainter::AnalogPainter(Tools::CRectGetter getFn)
    : m_getDrawableRect(getFn)
{
}

auto AnalogPainter::PaintStaticParts(CDC& client) -> void
{
    CRect drawableRect = m_getDrawableRect(client);

    // Draw the clock face
    client.Ellipse(drawableRect);

    // Calculate the center and radius of the clock face
    int centerX = (drawableRect.left + drawableRect.right) / 2;
    int centerY = (drawableRect.top + drawableRect.bottom) / 2;
    int radius = (drawableRect.right - drawableRect.left) / 2;

    // Pen for minute markers (thin lines)
    CPen minutePen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = client.SelectObject(&minutePen);

    // Draw the 60 minute markers
    for (int i = 0; i < 60; ++i) {
        // Angle in radians for each marker
        double angle = (i * 6) * std::numbers::pi / 180.0;

        // Start and end points for the minute markers
        int startX = static_cast<int>(centerX + (radius - 10) * cos(angle));
        int startY = static_cast<int>(centerY + (radius - 10) * sin(angle));
        int endX = static_cast<int>(centerX + radius * cos(angle));
        int endY = static_cast<int>(centerY + radius * sin(angle));

        client.MoveTo(startX, startY);
        client.LineTo(endX, endY);
    }

    // Pen for hour markers (thicker lines)
    CPen hourPen(PS_SOLID, 3, RGB(0, 0, 0));
    client.SelectObject(&hourPen);

    // Draw the 12 hour markers
    for (int i = 0; i < 12; ++i) {
        // Angle in radians for each hour marker
        double angle = (i * 30) * std::numbers::pi / 180.0;

        // Start and end points for the hour markers
        int startX = static_cast<int>(centerX + (radius - 20) * cos(angle));
        int startY = static_cast<int>(centerY + (radius - 20) * sin(angle));
        int endX = static_cast<int>(centerX + radius * cos(angle));
        int endY = static_cast<int>(centerY + radius * sin(angle));

        client.MoveTo(startX, startY);
        client.LineTo(endX, endY);
    }

    // Restore the old pen
    client.SelectObject(pOldPen);
}

auto AnalogPainter::PaintMovingParts(Data::DateDto time, CDC& client) -> void
{
    CRect drawableRect = m_getDrawableRect(client);

    int centerX = (drawableRect.right + drawableRect.left) / 2;
    int centerY = (drawableRect.bottom + drawableRect.top) / 2;

    // Calculate the angles in radians
    double angleSeconds = (time.seconds / 60.0) * 2 * std::numbers::pi;
    double angleMinutes = ((time.minutes + time.seconds / 60.0) / 60.0) * 2 * std::numbers::pi;
    double angleHours = ((time.hours % 12 + time.minutes / 60.0) / 12.0) * 2 * std::numbers::pi;

    // Define lengths for each hand
    int secondHandLength = static_cast<int>((drawableRect.right - drawableRect.left) * 0.45);
    int minuteHandLength = static_cast<int>((drawableRect.right - drawableRect.left) * 0.35);
    int hourHandLength = static_cast<int>((drawableRect.right - drawableRect.left) * 0.25);

    // Select default pen
    CPen* pOldPen = client.GetCurrentPen();

    // Set thick line
    CPen thickClockHand(PS_SOLID, 10, RGB(0, 0, 0));
    client.SelectObject(thickClockHand);

    // Hour hand
    client.MoveTo(centerX, centerY);
    int hourX = centerX + static_cast<int>(hourHandLength * sin(angleHours));
    int hourY = centerY - static_cast<int>(hourHandLength * cos(angleHours));
    client.LineTo(hourX, hourY);

    // Minute hand
    client.MoveTo(centerX, centerY);
    int minuteX = centerX + static_cast<int>(minuteHandLength * sin(angleMinutes));
    int minuteY = centerY - static_cast<int>(minuteHandLength * cos(angleMinutes));
    client.LineTo(minuteX, minuteY);

    // Set thin line
    CPen thinClockHand(PS_SOLID, 2, RGB(255, 0, 0));
    client.SelectObject(thinClockHand);

    // Second hand
    client.MoveTo(centerX, centerY);
    int secondX = centerX + static_cast<int>(secondHandLength * sin(angleSeconds));
    int secondY = centerY - static_cast<int>(secondHandLength * cos(angleSeconds));
    client.LineTo(secondX, secondY);

    // Select original pen
    client.SelectObject(pOldPen);
}

auto AnalogPainter::PaintDate(Data::DateDto date, CDC& client) -> void
{
    CRect drawableRect = m_getDrawableRect(client);

    CString todaysDate;
    todaysDate.Format(_T("%zu.%zu.%zu | %s"), date.day, date.month, date.year, date.timeZone.GetString());

    const int fontHeight = drawableRect.Height() / 20;
    CFont font;
    font.CreateFont(
        -fontHeight,              // Height of the font
        0,                        // Width of the font (0 means default)
        0,                        // Escapement
        0,                        // Orientation
        FW_NORMAL,                // Weight (boldness)
        FALSE,                    // Italic
        FALSE,                    // Underline
        0,                        // Strikeout
        DEFAULT_CHARSET,          // Character set
        OUT_DEFAULT_PRECIS,       // Output precision
        CLIP_DEFAULT_PRECIS,      // Clipping precision
        DEFAULT_QUALITY,          // Quality
        DEFAULT_PITCH | FF_SWISS, // Pitch and family
        _T("Bahnschrift"));       // Font name

    CFont* pOldFont = client.SelectObject(&font);

    int bottomPadding = drawableRect.bottom - (drawableRect.bottom / 5);

    CRect textRect(drawableRect.left, bottomPadding, drawableRect.right, bottomPadding + fontHeight);
    client.DrawText(todaysDate, textRect, DT_CENTER);

    client.SelectObject(pOldFont); // Reset text
}

}