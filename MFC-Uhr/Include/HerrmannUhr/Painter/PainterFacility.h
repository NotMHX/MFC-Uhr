#pragma once
#include "HerrmannUhr/Painter/AbstractPainter.h"
#include "HerrmannUhr/Data/Appearances.h"

namespace Messerli::HerrmannUhr::Painter {

class PainterFacility {
public:
    static auto CreatePainter(Data::Appearances a) -> std::unique_ptr<AbstractPainter>;
};

}