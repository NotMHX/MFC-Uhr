#include "pch.h"
#include "HerrmannUhr/Painter/PainterFacility.h"
#include "HerrmannUhr/Painter/AnalogPainter.h"
#include "HerrmannUhr/Painter/BinaryPainter.h"

namespace Messerli::HerrmannUhr::Painter {

auto PainterFacility::CreatePainter(Data::Appearances a) -> std::unique_ptr<AbstractPainter>
{
    switch (a) {
        case Data::Appearances::Analog:
        {
            auto rectGetter = [](auto& client) {
                return Tools::GetRectFromCDC(client, 20);
                };
            return std::make_unique<AnalogPainter>(rectGetter);
        }
        case Data::Appearances::Binary:
        {
            auto rectGetter = [](auto& client) {
                return Tools::GetRectFromCDC(client, 40);
                };
            return std::make_unique<BinaryPainter>(rectGetter);
        }
        default:
        {
            auto rectGetter = [](auto& client) {
                return Tools::GetRectFromCDC(client, 20);
                };
            return std::make_unique<AnalogPainter>(rectGetter);

        }
    }
}

}