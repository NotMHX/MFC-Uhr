#include "pch.h"
#include "HerrmannUhr/Tools/WndConverter.h"

#include <bitset>
#include <vector>
#include <algorithm>
#ifdef min
#undef min
#endif

namespace Messerli::HerrmannUhr::Tools {

auto GetRectFromCDC(CDC& client, const int border) -> CRect
{
    auto window = WindowFromDC(client);
    CRect pRect;
    if (window != nullptr) {
        CRect tempRect;
        if (GetClientRect(window, &tempRect) == TRUE) {
            pRect = tempRect;
        } else {
            ASSERT(_T("can't retrieve client canvas"));
        }
    } else {
        ASSERT(_T("can't locate a window"));
    }

    // Calculate the width and height for the circle
    int maxDiameter = std::min(pRect.Width(), pRect.Height() - 80) - 2 * border;

    // Define the circle's rectangle
    return CRect(
        pRect.left + border,
        pRect.top + 80 + border,
        pRect.left + border + maxDiameter,
        pRect.top + 80 + border + maxDiameter
    );
}

auto ConvertNumToBinVec(size_t number, size_t bits) -> std::vector<int>
{
    std::bitset<6> binary(number); // Use 6 bits for consistency, and slice if needed
    std::vector<int> result(bits);

    for (size_t i = 0; i < bits; ++i) {
        result[i] = binary[bits - 1 - i];
    }

    return result;
}

}
