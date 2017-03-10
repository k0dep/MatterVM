#pragma once

#ifndef _VMODULENAIVE_H_
#define _VMODULENAIVE_H_

#include "VModuleBase.h"
#include <Windows.h>
#include "IModule.h"
#include <string>

namespace mtr
{
	class VModuleNative : VModuleBase
	{
	public:
		VModuleNative(HINSTANCE dll_instance, std::string name);
		~VModuleNative();

		// Унаследовано через VModuleBase
		virtual u32 function_count() const override;
		virtual std::string get_name() const override;
		virtual std::shared_ptr<u8> get_function(u32 index, VMachine * machine) const override;

	protected:
		mtr::Modules::ExecuteFuncPtr _execute;
		mtr::Modules::FuncCountPtr _count;
		HINSTANCE _dll_inst;
	};
}

#endif // !_VMODULENAIVE_H_