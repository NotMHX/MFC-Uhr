#pragma once
#include "pch.h"
#include <functional>

namespace Messerli::HerrmannUhr::Tools {

using CRectGetter = std::function<CRect(CDC&)>;

auto GetRectFromCDC(CDC& client, const int border) -> CRect;

auto ConvertNumToBinVec(size_t value, size_t bits) -> std::vector<int>;

}