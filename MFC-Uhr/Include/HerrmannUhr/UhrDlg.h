#pragma once
#include "HerrmannUhr/UhrController.h"
#include "HerrmannUhr/Data/Appearances.h"
#include "HerrmannUhr/Data/TimeZones.h"

namespace Messerli::HerrmannUhr {

class UhrDlg : public CDialogEx {
public:
    UhrDlg(CWnd* pParent, std::function<UhrController()> createController);

protected:
    auto OnInitDialog() -> BOOL override;
    auto DoDataExchange(CDataExchange* pDX) -> void override;	// DDX/DDV support
    DECLARE_MESSAGE_MAP();

    auto OnTimer(UINT_PTR nIDEvent) -> void;
    auto OnSize(UINT nType, int w, int h) -> void;
    auto OnClickCreate() -> void;
    auto OnClose() -> void;

    auto Update() -> void;

    enum class DlgControls {
        IDC_APPEARANCE = 102,
        IDC_TIMEZONE = 103,
        IDT_TIMER = 104,
        IDC_CREATE = 105
    };

    UhrController m_controller;

    CComboBox m_appearanceBox;
    CComboBox m_timeZoneBox;
};
}