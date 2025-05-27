#pragma once

#include <chrono>
#include "HerrmannUhr/Data/DateDto.h"

namespace Messerli::HerrmannUhr::Painter {

class AbstractPainter {
public:
    auto Paint(Data::DateDto dayTime, CDC& client) -> void;

    virtual ~AbstractPainter() = default;

private:
    virtual auto PaintStaticParts(CDC& client) -> void abstract;

    virtual auto PaintMovingParts(Data::DateDto time, CDC& client) -> void abstract;

    virtual auto PaintDate(Data::DateDto date, CDC& client) -> void abstract;
};
}