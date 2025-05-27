#pragma once
#include "HerrmannUhr/UhrDlg.h"

namespace Messerli::HerrmannUhr {

void StartApp(CWnd* pWnd);

extern std::vector<std::unique_ptr<UhrDlg>> m_instances;
extern int m_instanceCount;

void AddInstance(int appearanceIndex, int timeZoneIndex, CWnd* wnd);

}
