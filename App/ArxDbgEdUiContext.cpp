//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgEdUiContext.h"
#include "ArxDbgApp.h"
#include "AcExtensionModule.h"
#include "Res_ArxDbg.h"



//ACRX_CONS_DEFINE_MEMBERS(ArxDbgEdUiContextApp, AcEdUiContext, 1)

/**************************************************************************
**
**  ArxDbgEdUiContextApp::ArxDbgEdUiContextApp
**
**  **jma
**
*************************************/

ArxDbgEdUiContextApp::ArxDbgEdUiContextApp()
{
	CAcModuleResourceOverride(ArxDbgApp::getApp()->dllInstance());

    m_cMenu = new CMenu;
	/*16-4-15 20:17
  m_pDemoMenu= new CMenu;                          // 创建一个菜单对象
	*****YLH*****/
    BOOL res = m_cMenu->LoadMenu(ARXDBG_MNU_APP);/*m_pDemoMenu->LoadMenu(IDR_DEMO_DEFAULT_MENU);    // 使用创建的菜单对象加载在资源编辑器中编辑好的资源*/
    VERIFY(res);
    if (!res) {
        delete m_cMenu;
        m_cMenu = NULL;
    }
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::ArxDbgEdUiContextApp
**
**  **jma
**
*************************************/

ArxDbgEdUiContextApp::~ArxDbgEdUiContextApp()
{
    if (m_cMenu) 
        delete m_cMenu;
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::getMenuContext
**
**  **jma
**
*************************************/

void* 
ArxDbgEdUiContextApp::getMenuContext(const AcRxClass* classtype, const AcDbObjectIdArray& selectedObjs)/*AutoCAD系统获取快捷菜单句柄函数
virtual void *　getMenuContext(const AcRxClass * unnamed,const AcDbObjectIdArray& unnamed) = 0;
其中，第一个参数unnamed是当前所选择的实体的对象句柄，第二个参数unnamed是所选实体的实体ID数组。这两个参数只有在实体对象上下文菜单中有效。*/
{
    m_hMenu = m_cMenu->GetSubMenu(0)->GetSafeHmenu();
    return &m_hMenu;
	/* －－在getMenuContext函数中添加显示我们自己菜单项的代码
	m_hDemoMenu= m_pDemoMenu->GetSubMenu(0)->GetSafeHmenu(); // 这里我们就显示已经加载的菜单(m_pDemoMenu)中的第一个子菜单吧！
	return &m_hDemoMenu; // 返回子菜单对象的句柄*/
}

/**************************************************************************
**
**  ArxDbgEdUiContextApp::onCommand
**`
**  **jma
**
*************************************/

void  
ArxDbgEdUiContextApp::onCommand(Adesk::UInt32 cmdId)/*（2）菜单项命令事件响应函数
													virtual void onCommand(Adesk::UInt32 unnamed) = 0;
													其中，unnamed是相应菜单项的菜单ID。此函数在用户选择执行快捷菜单中的某个菜单项时被调用。*/
{
	LPCTSTR cmdStr = NULL;
	CString str;

	if (cmdId == ARXDBG_APPCMD_EDITOR_INFO)
		cmdStr = _T("ArxDbgSnoopEd");
	else if (cmdId == ARXDBG_APPCMD_DB_INFO)
		cmdStr = _T("ArxDbgSnoopDb");
	else if (cmdId == ARXDBG_APPCMD_ENT_INFO)
		cmdStr = _T("ArxDbgSnoopEnts");
	else if (cmdId == ARXDBG_APPCMD_NESTEDENT_INFO)
		cmdStr = _T("ArxDbgSnoopNents");
	else if (cmdId == ARXDBG_APPCMD_SERVICES_INFO)
		cmdStr = _T("ArxDbgSnoopServices");
	else if (cmdId == ARXDBG_APPCMD_REGISTRY_INFO)
		cmdStr = _T("ArxDbgSnoopSysRegistry");
	else if (cmdId == ARXDBG_APPCMD_REACTOR_INFO)
		cmdStr = _T("ArxDbgReactors");
	else if (cmdId == ARXDBG_APPCMD_OBJ_STATE)
		cmdStr = _T("ArxDbgTestState");
	else if (cmdId == ARXDBG_APPCMD_DWG_FILER)
		cmdStr = _T("ArxDbgTestDwgFiler");
	else if (cmdId == ARXDBG_APPCMD_TEST_TRANSDB_CLONES)
		cmdStr = _T("ArxDbgTestTransDbClones");
	else if (cmdId == ARXDBG_APPCMD_TEST_WORLD_DRAW)
		cmdStr = _T("ArxDbgTestWorldDraw");
	else if (cmdId == ARXDBG_APPCMD_TEST_CURVES)
		cmdStr = _T("ArxDbgTestCurve");
	else if (cmdId == ARXDBG_APPCMD_TEST_SELSET)
		cmdStr = _T("ArxDbgTestSelSet");
	else if (cmdId == ARXDBG_APPCMD_TEST_XDATA)
		cmdStr = _T("ArxDbgTestXdata");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTENTS)
		cmdStr = _T("ArxDbgTestExtents");
	else if (cmdId == ARXDBG_APPCMD_TEST_INTERSECT)
		cmdStr = _T("ArxDbgTestIntersect");
	else if (cmdId == ARXDBG_APPCMD_TEST_GRIPPTS)
		cmdStr = _T("ArxDbgTestGetGripPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_STRETCHPTS)
		cmdStr = _T("ArxDbgTestGetStretchPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_OSNAP)
		cmdStr = _T("ArxDbgTestGetOsnapPoints");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTDICTADD)
		cmdStr = _T("ArxDbgTestExtDictAdd");
	else if (cmdId == ARXDBG_APPCMD_TEST_EXTDICT_REMOVE)
		cmdStr = _T("ArxDbgTestExtDictRemove");
	else if (cmdId == ARXDBG_APPCMD_TEST_COLOR)
		cmdStr = _T("ArxDbgTestColor");
	else if (cmdId == ARXDBG_APPCMD_TEST_PURGE)
		cmdStr = _T("ArxDbgTestPruge");
	else if (cmdId == ARXDBG_APPCMD_TEST_COUNTREFS)
		cmdStr = _T("ArxDbgTestCountHardRefs");
	else if (cmdId == ARXDBG_APPCMD_TEST_ENTMAKE)
		cmdStr = _T("ArxDbgTestEntMake");
	else if (cmdId == ARXDBG_APPCMD_TEST_TBLMAKE)
		cmdStr = _T("ArxDbgTestTblMake");
	else if (cmdId == ARXDBG_APPCMD_TEST_XFORM)
		cmdStr = _T("ArxDbgTestXform");
	else if (cmdId == ARXDBG_APPCMD_LOGO_ADD)
		cmdStr = _T("ArxDbgAdeskLogoAdd");
	else if (cmdId == ARXDBG_APPCMD_LOGO_MODIFY)
		cmdStr = _T("ArxDbgAdeskLogoModify");
	else if (cmdId == ARXDBG_APPCMD_LOGO_HARDWIRE1)
		cmdStr = _T("ArxDbgAdeskLogoHardwire1");
	else if (cmdId == ARXDBG_APPCMD_LOGO_HARDWIRE2)
		cmdStr = _T("ArxDbgAdeskLogoHardwire2");
	else if (cmdId == ARXDBG_APPCMD_LOGO_ADD_STYLE)
		cmdStr = _T("ArxDbgAdeskLogoStyleAdd");
	else if (cmdId == ARXDBG_APPCMD_LOGO_MOD_STYLE)
		cmdStr = _T("ArxDbgAdeskLogoStyleModify");
	else if (cmdId == ARXDBG_APPCMD_ABOUT)
		cmdStr = _T("ArxDbgAbout");

	if (cmdStr != NULL) {
		str.Format(_T("%s\n"), cmdStr);/*16-4-15 20:20

									   acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
									   *****YLH*****/
	    acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
	}
}

