#include "VMachine.h"
#include "ModuleLoader.h"
#include "VModule.h"
#include <stdexcept>
using namespace mtr;

mtr::VMachine::VMachine()
{
}

mtr::VMachine::~VMachine()
{
}

void mtr::VMachine::init(std::shared_ptr<VModule> module)
{
	_current_module = module;
	
	_bytecode_call_stack = std::stack<std::shared_ptr<u8>>();
	_ip_call_stack = std::stack<u32>();
	_module_call_stack = std::stack<u16>();
	_function_call_stack = std::stack<u32>();

	_current_module_id = 0;
	_current_function_id = 0;
	_ip = 0;

	_operands = std::vector<u8>();

	load_recursive_modules(module);
	init(module, 0);
}

void mtr::VMachine::init(std::shared_ptr<VModule> module, u16 index)
{
	if (_module_map.find(index) != _module_map.end()) return;

	auto required = module->require_modules();
	std::map<u16, u16> map_to_module;

	for each (auto var in required)
	{
		init(ModuleLoader::load_moodule(var.first), _module_name_map[var.first]);
		map_to_module[var.second] = _module_name_map[var.first];
	}
	_module_map[index] = map_to_module;
}

void mtr::VMachine::load_recursive_modules(std::shared_ptr<VModule> module)
{
	if (_module_name_map.find(module->get_name()) == _module_name_map.end())
		return;

	_module_name_map[module->get_name()] = (u16)_modules.size();
	_modules.push_back(module);

	auto required = module->require_modules();

	for each (auto var in required)	
		load_recursive_modules(ModuleLoader::load_moodule(var.first));
}

void mtr::VMachine::steep()
{
}

void mtr::VMachine::run(u32 function)
{
}

void mtr::VMachine::register_command(std::shared_ptr<ICommand> cmd)
{
	auto isExist = _commands.find(cmd->code());
	if (isExist == _commands.end())
		throw std::invalid_argument("command alredy registred");

	_commands[cmd->code()] = cmd;
}

void mtr::VMachine::call_function(u16 module, u32 function)
{
	_bytecode_call_stack.push(_bytecode);
	_ip_call_stack.push(_ip);
	_module_call_stack.push(_current_module_id);
	_function_call_stack.push(_current_function_id);

	_current_module = _modules[module];
	_current_function_id = function;

	auto called_func = _current_module->get_function(function);
	_bytecode = called_func.first;
	((_current_module.get())->*(called_func.second))(this);
}

void mtr::VMachine::ret_function()
{
}

void mtr::VMachine::do_goto(u32 addr)
{
}
