#include "pch.h"
#include "HerrmannUhr/UhrDlg.h"
#include "HerrmannUhr/HerrmannUhr.h"
#include "resource.h"
#include <memory>

namespace Messerli::HerrmannUhr {

UhrDlg::UhrDlg(CWnd* pParent, std::function<UhrController()> createController)
    : CDialogEx(IDD_UHRDLG, pParent), m_controller(createController())
{
}

BEGIN_MESSAGE_MAP(UhrDlg, CDialogEx)
    ON_WM_TIMER()
    ON_WM_SIZE()
    ON_BN_CLICKED(DlgControls::IDC_CREATE, OnClickCreate)
    ON_WM_CLOSE()
END_MESSAGE_MAP()

auto UhrDlg::OnInitDialog() -> BOOL
{
    __super::OnInitDialog();

    for (const auto& app : Data::AppearanceVec) {
        m_appearanceBox.AddString(app.second);
    }
    m_appearanceBox.SetCurSel(0);

    for (const auto& tz : Data::TimeZoneVec) {
        m_timeZoneBox.AddString(tz.second);
    }
    m_timeZoneBox.SetCurSel(2);

    SetTimer(static_cast<UINT_PTR>(DlgControls::IDT_TIMER), 1000, nullptr);
    Update();

    return TRUE;
}

auto UhrDlg::DoDataExchange(CDataExchange* pDX) -> void
{
    __super::DoDataExchange(pDX);

    DDX_Control(pDX, static_cast<long>(DlgControls::IDC_APPEARANCE), m_appearanceBox);
    DDX_Control(pDX, static_cast<long>(DlgControls::IDC_TIMEZONE), m_timeZoneBox);
}

auto UhrDlg::OnTimer(UINT_PTR nIDEvent) -> void
{
    if (nIDEvent == static_cast<long>(DlgControls::IDT_TIMER)) {
        Update();
    }
}

auto UhrDlg::OnSize(UINT nType, int w, int h) -> void
{
    __super::OnSize(nType, w, h);

    if (IsWindowVisible() == TRUE) {
        Invalidate();
        Update();
    }
}

auto UhrDlg::OnClickCreate() -> void
{
    m_controller.AddDialog(m_appearanceBox.GetCurSel(), m_timeZoneBox.GetCurSel(), m_pParentWnd);
}

auto UhrDlg::OnClose() -> void
{
    --m_instanceCount;
    __super::OnClose();
}

void UhrDlg::Update()
{
    CClientDC client(this);
    UpdateWindow();
    m_controller.UpdateClock(client);
}

}
