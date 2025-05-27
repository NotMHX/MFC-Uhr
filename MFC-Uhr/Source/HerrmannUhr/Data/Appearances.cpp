#include "pch.h"

#include "HerrmannUhr/Data/Appearances.h"
#include <vector> 

namespace Messerli::HerrmannUhr::Data {
const std::vector<std::pair<Appearances, CString>> AppearanceVec = {
    {Appearances::Analog, _T("Analog")},
    {Appearances::Binary, _T("Binär")}
};

}