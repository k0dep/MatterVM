#include <stdexcept>

#include <mtr/VMachine.h>
#include <mtr/ModuleLoader.h>
#include <mtr/VModuleBase.h>
#include <mtr/Commands.h>

using namespace mtr;
using namespace std;

shared_ptr<u8> VMachine::ret_bytecode = shared_ptr<u8>(new u8[1]{ CMD_RET });

mtr::VMachine::VMachine()
{
	ICommand::init();
}

mtr::VMachine::~VMachine()
{
}

void VMachine::init(std::shared_ptr<VModuleBase> module)
{
	for each (auto item in ICommand::global_commands)
		register_command(item);

	__main_module = module;

	load_recursive_modules(module);
	_init(module, 0);
}

void VMachine::_init(shared_ptr<VModuleBase> module, u16 index)
{
	if (_module_map.find(index) != _module_map.end()) return;

	auto required = module->require_modules();
	map<u16, u16> map_to_module;

	for each (auto item in required)
	{
		_init(ModuleLoader::load_moodule(string(item.first)), _module_name_map[item.first]);
		map_to_module[item.second] = _module_name_map[item.first];

	}
	_module_map[index] = map_to_module;
}

void VMachine::load_recursive_modules(shared_ptr<VModuleBase> module)
{
	if (_module_name_map.find(module->get_name()) != _module_name_map.end())
		return;

	_module_name_map[module->get_name()] = (u16)_modules.size();
	_modules.push_back(module);

	auto required = module->require_modules();
	for each (auto item in required)
		load_recursive_modules(ModuleLoader::load_moodule(item.first));
}

u8 VMachine::_keep_byte_by_ip()
{
	return (_bytecode.get())[ip++];
}

void VMachine::steep()
{
	auto icode = _keep_byte_by_ip();
	operands = std::stack<u8>();
	auto concrete_cmd = _commands[icode];
	std::stack<u8> ops;
	for (u8 i = 0; i < concrete_cmd->operand_count(); i++)
		ops.push(_keep_byte_by_ip());
	while (ops.size() > 0)
	{
		operands.push(ops.top());
		ops.pop();
	}
	concrete_cmd->execute(this);
}

void VMachine::run(u32 function)
{
	_stoped = false;
	current_module = __main_module;

	_bytecode = current_module->get_function(function, this);

	_bytecode_call_stack = std::stack<shared_ptr<u8>>();
	_ip_call_stack = std::stack<u32>();
	_module_call_stack = std::stack<u16>();
	_function_call_stack = std::stack<u32>();

	current_module_id = 0;
	current_function_id = function;
	ip = 0;

	operands = std::stack<u8>();

	stack = VStack();

	while (!_stoped)
	{
		steep();
	}
}

void VMachine::register_command(shared_ptr<ICommand> cmd)
{
	auto isExist = _commands.find(cmd->code());
	if (isExist != _commands.end())
		throw invalid_argument("command alredy registred");

	_commands[cmd->code()] = cmd;
}

void VMachine::call_function(u16 module, u32 function)
{
	_bytecode_call_stack.push(_bytecode);
	_ip_call_stack.push(ip);
	_module_call_stack.push(current_module_id);
	_function_call_stack.push(current_function_id);

	current_module = _modules[module];
	current_module_id = module;
	current_function_id = function;
	ip = 0;

	_bytecode = current_module->get_function(function, this);
}

void VMachine::ret_function()
{
	if (_ip_call_stack.size() == 0)
	{
		_stoped = true;
		return;
	}

	ip = _ip_call_stack.top();
	_ip_call_stack.pop();

	current_module_id = _module_call_stack.top();
	_module_call_stack.pop();
	current_module = _modules[current_module_id];

	current_function_id = _function_call_stack.top();
	_function_call_stack.pop();

	_bytecode = _bytecode_call_stack.top();
	_bytecode_call_stack.pop();
}

void VMachine::do_goto(u32 addr)
{
	ip = addr;
}
