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

#ifndef APIENTRY
#define APIENTRY __stdcall
#endif // !APIENTRY

		extern "C" MODULEAPI void APIENTRY execute_func(u32 function_id, VMachine * machine);
		extern "C" MODULEAPI u32 APIENTRY function_count();

		typedef void (APIENTRY *ExecuteFuncPtr)(u32, VMachine*);
		typedef u32 (APIENTRY *FuncCountPtr)();
	}
}

#endif // !_IMODULE_H_