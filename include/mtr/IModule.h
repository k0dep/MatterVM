#pragma once

#ifndef _IMODULE_H_
#define _IMODULE_H_

#include <map>

#include <mtr/DataStructures.h>
#include <mtr/VMachine.h>

namespace mtr {
	namespace Modules
	{

#if defined(MODULE_IMPL) // внутри DLL
#   define MODULEAPI   __declspec(dllexport)
#else // вне DLL
#   define MODULEAPI   __declspec(dllimport)
#endif

#define API_MTR _cdecl

		extern "C" MODULEAPI void API_MTR execute_func(u32 function_id, VMachine * machine);
		extern "C" MODULEAPI u32 API_MTR function_count();

		typedef void (API_MTR *ExecuteFuncPtr)(u32, VMachine*);
		typedef u32 (API_MTR *FuncCountPtr)();
	}
}

#endif // !_IMODULE_H_