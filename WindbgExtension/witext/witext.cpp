// witext.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <DbgEng.h>
#include <string>
#include <vector>

#include "windbgctrl.h"
#include "resource.h"


HRESULT WINAPI ver2(PDEBUG_CLIENT pDebugClient, PCSTR sArg) {

	wdbgctrl *dbgctrl = new wdbgctrl(pDebugClient);
	dbgctrl->pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "%s\n%s\n", "Author: kumaran kamalanathan.", "Version 1.1");
	return S_OK;
}



HRESULT WINAPI ver(PDEBUG_CLIENT pDebugClient, PCSTR sArg) {
	//https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/dbgeng/nn-dbgeng-idebugcontrol 
	IDebugControl *pDebugControl;
		

	// Initialize the Interface 
	if (pDebugClient->QueryInterface(__uuidof(IDebugControl), 
		(void**)&pDebugControl) != S_OK) {
		OutputDebugString(L"Failed to QueryInterface IDebugControl");
		return S_OK;
	}

	pDebugControl->Output(DEBUG_OUTPUT_NORMAL, 
		"%s\n%s\n", "Author: kumaran kamalanathan.", "Version 1.1");
	return S_OK;
}