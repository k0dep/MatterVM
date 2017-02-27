#pragma once

#include "VMachine.h"

namespace mtr
{
	class VMachine;

	class ICommand
	{
	public:
		virtual u8 code() const = 0;
		virtual u8 operand_count() const = 0;
		virtual u32 next_ip() const = 0;
		virtual bool execute(VMachine &vm) = 0;
	};
}