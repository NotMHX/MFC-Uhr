#include "pch.h"

#include "HerrmannUhr/HerrmannUhr.h"

#include "HerrmannUhr/Painter/AnalogPainter.h"
#include "HerrmannUhr/Painter/PainterFacility.h"
#include "HerrmannUhr/Data/Appearances.h"
#include "resource.h"

namespace Messerli::HerrmannUhr {

std::vector<std::unique_ptr<UhrDlg>> m_instances;
int m_instanceCount = 0;

void StartApp(CWnd* pWnd) // todo: call this method in Adrtest.cpp to start app
{
    AddInstance(static_cast<int>(Data::Appearances::Analog), static_cast<int>(Data::TimeZones::UTC), pWnd);

    while (m_instanceCount > 0) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(10);
    }
}

void AddInstance(int appearanceIndex, int timeZoneIndex, CWnd* pWnd)
{
    auto adder = [](int appearanceI, int timeZoneI, CWnd* pWindow) {
        AddInstance(appearanceI, timeZoneI, pWindow);
        };

    std::function<UhrController()> controllerCreator = [&appearanceIndex, &timeZoneIndex, &pWnd, &adder]() {
        return UhrController(Painter::PainterFacility::CreatePainter(
            Data::AppearanceVec[appearanceIndex].first),
            Data::TimeZoneVec[timeZoneIndex].first, adder);
        };

    std::unique_ptr<UhrDlg> uhr = std::make_unique<UhrDlg>(pWnd, controllerCreator);
    m_instances.push_back(std::move(uhr));
    m_instances.back()->Create(IDD_UHRDLG, pWnd);
    m_instances.back()->ShowWindow(SW_NORMAL);

    ++m_instanceCount;
}
}
