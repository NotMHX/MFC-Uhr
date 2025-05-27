#pragma once
#include "HerrmannUhr/Painter/AbstractPainter.h"

#include "HerrmannUhr/Tools/WndConverter.h"

namespace Messerli::HerrmannUhr::Painter {

class AnalogPainter : public AbstractPainter {
public:
    AnalogPainter(Tools::CRectGetter getFn);
private:
    virtual auto PaintStaticParts(CDC& client) -> void override;

    virtual auto PaintMovingParts(Data::DateDto time, CDC& client) -> void override;

    virtual auto PaintDate(Data::DateDto date, CDC& client) -> void override;

    Tools::CRectGetter m_getDrawableRect;
};
}