#pragma once

#ifndef _VMODULE_BASE_H_
#define _VMODULE_BASE_H_

#include "VMachine.h"
#include "VMemory.h"
#include "VModuleBase.h"

namespace mtr
{
	class VMachine;
	typedef void(*ExecutePtr)(VMachine* op);

	class VModuleBase
	{
	public:
		std::vector<std::pair<std::string, u16>> require_modules();

		virtual u32 function_count() const = 0;
		virtual std::string get_name() const = 0;
		virtual std::shared_ptr<VMemory> get_memory() const { return _memory; }
		virtual std::shared_ptr<u8> get_function(u32 index, VMachine * machine) const = 0;

	protected:
		std::shared_ptr<VMemory> _memory;
		std::string _name;
		std::vector<std::pair<std::string, u16>> _required_modules;
	};
}

#endif // !_VMODULE_BASE_H_