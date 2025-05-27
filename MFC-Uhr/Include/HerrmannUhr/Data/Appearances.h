#pragma once
#include <vector>

namespace Messerli::HerrmannUhr::Data {

enum class Appearances {
    Analog = 0,
    Binary
};

extern const std::vector<std::pair<Appearances, CString>> AppearanceVec;

}