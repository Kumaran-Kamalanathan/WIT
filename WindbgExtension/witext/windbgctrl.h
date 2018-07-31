#pragma once
#include <DbgEng.h>
#include <DbgHelp.h>
#include <exception>


#pragma warning(disable:4552)
#pragma warning(disable:4091)

#define WDBGCTRL_RESULT(x)\
if ((x) != S_OK)return E_FAIL;\



typedef struct wdbgctrl {

	wdbgctrl() {
		pDebugClient = NULL;
		pDebugControl = NULL;
		pDebugRegisters = NULL;
		pDebugDataSpaces = NULL;
	}

	wdbgctrl(PDEBUG_CLIENT pDbgClient) :wdbgctrl_initialized(FALSE), pDebugClient(NULL), pDebugControl(NULL), pDebugSymbols(NULL), pDebugRegisters(NULL) {
		pDebugClient = pDbgClient;
		if (pDbgClient != NULL) {
			wdbgctrl_initialized = (pDbgClient->QueryInterface(__uuidof(IDebugControl), (void**)&pDebugControl) == S_OK);
			wdbgctrl_initialized & (pDbgClient->QueryInterface(__uuidof(IDebugRegisters), (void**)&pDebugRegisters) == S_OK);
			wdbgctrl_initialized & (pDbgClient->QueryInterface(__uuidof(IDebugDataSpaces), (void**)&pDebugDataSpaces) == S_OK);
			wdbgctrl_initialized & (pDbgClient->QueryInterface(__uuidof(IDebugSymbols), (void**)&pDebugSymbols) == S_OK);
		}
		else {
			throw new std::exception("PDEBUG_CLIENT is NULL");
		}
	}

	virtual ~wdbgctrl() {
		if (pDebugClient != NULL) {
			pDebugClient->Release();
			pDebugClient = NULL;
		}
		if (pDebugControl != NULL) {
			pDebugControl->Release();
			pDebugControl = NULL;
		}
		if (pDebugRegisters != NULL) {
			pDebugRegisters->Release();
			pDebugRegisters = NULL;
		}
		if (pDebugDataSpaces != NULL) {
			pDebugDataSpaces->Release();
			pDebugDataSpaces = NULL;
		}
		if (pDebugSymbols != NULL) {
			pDebugSymbols->Release();
			pDebugSymbols = NULL;
		}
	}

	PDEBUG_CLIENT pDebugClient;
	PDEBUG_CONTROL pDebugControl;
	PDEBUG_REGISTERS pDebugRegisters;
	PDEBUG_DATA_SPACES pDebugDataSpaces;
	PDEBUG_SYMBOLS pDebugSymbols;
	BOOL wdbgctrl_initialized;
}*PWDBG_CTRL;