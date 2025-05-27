#pragma once
#include "HerrmannUhr/Painter/AbstractPainter.h"

#include "HerrmannUhr/Tools/WndConverter.h"
#include <functional>

namespace Messerli::HerrmannUhr::Painter {

class BinaryPainter : public AbstractPainter {
public:
    // Methods
    BinaryPainter(Tools::CRectGetter getFn);

private:
    // Functions
    virtual auto PaintStaticParts(CDC& client) -> void override;
    virtual auto PaintMovingParts(Data::DateDto time, CDC& client) -> void override;
    virtual auto PaintDate(Data::DateDto date, CDC& client) -> void override;

    auto PaintField(size_t index, CDC& client, bool isLit, std::function<void(CDC&, int)> shapeFn) -> void;

private:
    // Members
    CRect m_hourFields[5];
    CRect m_minuteFields[6];
    CRect m_secondFields[6];

    Tools::CRectGetter m_getDrawableRect;

    std::function<void(CDC&, int)> m_paintHourShape;
    std::function<void(CDC&, int)> m_paintMinuteShape;
    std::function<void(CDC&, int)> m_paintSecondShape;

};
}