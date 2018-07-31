// witext.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <DbgEng.h>
#include <string>
#include <vector>

#include "windbgctrl.h"


HRESULT WINAPI ver(PDEBUG_CLIENT pDebugClient, PCSTR sArg) {

	wdbgctrl *dbgctrl = new wdbgctrl(pDebugClient);
	dbgctrl->pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "%s\n%s\n", "Author: kumaran kamalanathan.", "Version 1.1");
	return S_OK;
}



