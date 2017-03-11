#include <stdexcept>

#include <mtr/VMachine.h>
#include <mtr/ModuleLoader.h>
#include <mtr/VModuleBase.h>
#include <mtr/SCommandList.h>

using namespace mtr;
using namespace std;

void mtr::VMachine::init(std::shared_ptr<VModuleBase> module)
{
	for each (auto item in SCommandList::command_list)
		register_command(item);

	_stoped = false;
	_current_module = module;
	
	_bytecode_call_stack = stack<shared_ptr<u8>>();
	_ip_call_stack = stack<u32>();
	_module_call_stack = stack<u16>();
	_function_call_stack = stack<u32>();

	_current_module_id = 0;
	_current_function_id = 0;
	_ip = 0;

	_operands = stack<u8>();

	load_recursive_modules(module);
	init(module, 0);
}

void VMachine::init(shared_ptr<VModuleBase> module, u16 index)
{
	if (_module_map.find(index) != _module_map.end()) return;

	auto required = module->require_modules();
	map<u16, u16> map_to_module;

	for each (auto item in required)
	{
		init(ModuleLoader::load_moodule(string(item.first)), _module_name_map[item.first]);
		map_to_module[item.second] = _module_name_map[item.first];

	}
	_module_map[index] = map_to_module;
}

void VMachine::load_recursive_modules(shared_ptr<VModuleBase> module)
{
	if (_module_name_map.find(module->get_name()) == _module_name_map.end())
		return;

	_module_name_map[module->get_name()] = (u16)_modules.size();
	_modules.push_back(module);

	auto required = module->require_modules();
	for each (auto item in required)
		load_recursive_modules(ModuleLoader::load_moodule(item.first));
}

u8 VMachine::_keep_byte_by_ip()
{
	return (_bytecode.get())[_ip++];
}

void VMachine::steep()
{
	auto icode = _keep_byte_by_ip();
	_operands = stack<u8>();
	auto concrete_cmd = _commands[icode];
	for (u8 i = 0; i < concrete_cmd->operand_count(); i++)
		_operands.push(_keep_byte_by_ip());
	concrete_cmd->execute(this);
}

void VMachine::run(u32 function)
{
	while (_stoped)
	{
		steep();
	}
}

void VMachine::register_command(shared_ptr<ICommand> cmd)
{
	auto isExist = _commands.find(cmd->code());
	if (isExist == _commands.end())
		throw invalid_argument("command alredy registred");

	_commands[cmd->code()] = cmd;
}

void VMachine::call_function(u16 module, u32 function)
{
	_bytecode_call_stack.push(_bytecode);
	_ip_call_stack.push(_ip);
	_module_call_stack.push(_current_module_id);
	_function_call_stack.push(_current_function_id);

	_current_module = _modules[module];
	_current_function_id = function;
	_ip = 0;

	_bytecode = _current_module->get_function(function, this);
}

void VMachine::ret_function()
{
	_ip = _ip_call_stack.top();
	_ip_call_stack.pop();

	_current_module_id = _module_call_stack.top();
	_module_call_stack.pop();
	_current_module = _modules[_current_function_id];	

	_current_function_id = _function_call_stack.top();
	_function_call_stack.pop();

	_bytecode = _bytecode_call_stack.top();
	_bytecode_call_stack.pop();
}

void VMachine::do_goto(u32 addr)
{
	_ip = addr;
}
