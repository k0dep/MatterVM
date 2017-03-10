#pragma once

#ifndef _VMACHINE_H_
#define _VMACHINE_H_

#include <stack>
#include <memory>
#include <map>
#include "DataStructures.h"
#include "ICommand.h"
#include "VModuleBase.h"
#include "VStack.h"

namespace mtr
{
	class VModuleBase;
	class ICommand;

	class VMachine
	{
	public:

		VMachine();
		~VMachine();

		void init(std::shared_ptr<VModuleBase> main_module);
		void steep();
		void run(u32 function);

	public:
		static std::shared_ptr<u8> ret_bytecode;

		void init(std::shared_ptr<VModuleBase> main_module, u16 index);
		void register_command(std::shared_ptr<ICommand> cmd);

		void call_function(u16 module, u32 function);
		void ret_function();
		void do_goto(u32 addr);

		void load_recursive_modules(std::shared_ptr<VModuleBase> module);


		VStack _stack;
		std::map<std::string, u16> _module_name_map;
		std::vector<std::shared_ptr<VModuleBase>> _modules;
		std::map<u16, std::map<u16, u16>> _module_map;
		std::map<u8, std::shared_ptr<ICommand>> _commands;

		std::stack<std::shared_ptr<u8>> _bytecode_call_stack;
		std::stack<u32> _ip_call_stack;
		std::stack<u16> _module_call_stack;
		std::stack<u32> _function_call_stack;

		std::shared_ptr<VModuleBase> _current_module;
		u16 _current_module_id;
		u32 _current_function_id;
		u32 _ip;

		std::shared_ptr<u8> _bytecode;

		std::stack<u8> _operands;

		u8 _keep_byte_by_ip();

		bool _stoped;
	};
}


#endif // !_VMACHINE_H_