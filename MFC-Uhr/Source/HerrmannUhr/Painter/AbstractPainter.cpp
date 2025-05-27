#include "pch.h"
#include "HerrmannUhr/Painter/AbstractPainter.h"

#include "HerrmannUhr/Tools/WndConverter.h"

namespace Messerli::HerrmannUhr::Painter {

auto AbstractPainter::Paint(Data::DateDto dayTime, CDC & client) -> void
{
    PaintStaticParts(client);
    PaintDate(dayTime, client);
    PaintMovingParts(dayTime, client);
}
}