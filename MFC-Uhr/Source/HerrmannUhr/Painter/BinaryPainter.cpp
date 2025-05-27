#include "pch.h"
#include "HerrmannUhr/Painter/BinaryPainter.h"

namespace Messerli::HerrmannUhr::Painter {
const int padding = 15;

BinaryPainter::BinaryPainter(Tools::CRectGetter getFn)
    : m_getDrawableRect(getFn)
{
    m_paintHourShape = [this](CDC& client, int index) {
        client.Ellipse(m_hourFields[index]);
        };

    m_paintMinuteShape = [this](CDC& client, int index) {
        // Line from bottom left to top right
        client.MoveTo(m_minuteFields[index].left, m_minuteFields[index].bottom);
        client.LineTo(m_minuteFields[index].right, m_minuteFields[index].top);

        // Line from top left to bottom right
        client.MoveTo(m_minuteFields[index].left, m_minuteFields[index].top);
        client.LineTo(m_minuteFields[index].right, m_minuteFields[index].bottom);
        };

    m_paintSecondShape = [this](CDC& client, int index) {
        client.Rectangle(m_secondFields[index]);
        };
}

auto BinaryPainter::PaintStaticParts(CDC & client) -> void
{
    CRect drawableRect = m_getDrawableRect(client);
    // Calculate width and height for each small CRect
    int fieldWidth = (drawableRect.Width() - padding * 5) / 6;
    int fieldHeight = (drawableRect.Height() - padding * 2) / 6;

    // Calculate the starting positions for each row
    int startYHour = drawableRect.top;
    int startYMinute = startYHour + fieldHeight + padding;
    int startYSecond = startYMinute + fieldHeight + padding;

    for (int i = 0; i < 5; ++i) {
        // X position for each field (from right to left)
        int startX = drawableRect.right - (fieldWidth * (5 - i)) - padding * (4 - i);

        // Assign the CRect to m_hourFields
        m_hourFields[i] = CRect(startX, startYHour, startX + fieldWidth, startYHour + fieldHeight);
        PaintField(i, client, false, m_paintHourShape);
    }

    for (int i = 0; i < 6; ++i) {
        // X position for each field (from right to left)
        int startX = drawableRect.left + i * (fieldWidth + padding);

        // Fill minute fields
        m_minuteFields[i] = CRect(startX, startYMinute, startX + fieldWidth, startYMinute + fieldHeight);
        PaintField(i, client, false, m_paintMinuteShape);

        // Fill second fields
        m_secondFields[i] = CRect(startX, startYSecond, startX + fieldWidth, startYSecond + fieldHeight);
        PaintField(i, client, false, m_paintSecondShape);
    }
}

auto BinaryPainter::PaintMovingParts(Data::DateDto time, CDC & client) -> void
{
    std::vector<int> hoursBinary = Tools::ConvertNumToBinVec(time.hours, 5);
    std::vector<int> minutesBinary = Tools::ConvertNumToBinVec(time.minutes, 6);
    std::vector<int> secondsBinary = Tools::ConvertNumToBinVec(time.seconds, 6);

    for (size_t i = 0; i < 5; ++i) {
        if (hoursBinary[i] == 1) {
            PaintField(i, client, true, m_paintHourShape);
        }
    }
    for (size_t i = 0; i < 6; ++i) {
        if (minutesBinary[i] == 1) {
            PaintField(i, client, true, m_paintMinuteShape);
        }
        if (secondsBinary[i] == 1) {
            PaintField(i, client, true, m_paintSecondShape);
        }
    }
}

auto BinaryPainter::PaintDate(Data::DateDto date, CDC & client) -> void
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
        _T("Lucida Console"));    // Font name

    CRect textRect(drawableRect.left - padding / 2, drawableRect.Height(), drawableRect.right - padding / 2, drawableRect.Height() + fontHeight);

    CFont* pOldFont = client.SelectObject(&font);
    client.SetTextColor(RGB(0, 150, 255));
    client.SetBkMode(TRANSPARENT); // Remove white background
    client.DrawText(todaysDate, textRect, DT_LEFT);

    client.SelectObject(pOldFont); // Reset text
}

auto BinaryPainter::PaintField(size_t index, CDC & client, bool isLit, std::function<void(CDC&, int)> shapeFn) -> void
{
    CPen* pOldPen = client.GetCurrentPen();

    COLORREF lineColor = RGB(200, 200, 200); // Grey
    if (isLit) {
        lineColor = RGB(0, 150, 255); // Blue
    }
    CPen linePen(PS_SOLID, (padding / 4 * 3), lineColor);
    client.SelectObject(linePen);
    client.SelectStockObject(NULL_BRUSH); // Prevents default fill

    shapeFn(client, index);

    client.SelectObject(pOldPen);
}

}
