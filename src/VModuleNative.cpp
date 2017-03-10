#include "VModuleNative.h"
#include <stdexcept>
using namespace mtr;
using namespace std;

VModuleNative::VModuleNative(HINSTANCE dll_instance, string name)
{
	_name = name;
	_dll_inst = dll_instance;
	_execute = (Modules::ExecuteFuncPtr)GetProcAddress(dll_instance, TEXT("execute_func"));
	_count = (Modules::FuncCountPtr)GetProcAddress(dll_instance, TEXT("function_count"));
	_required_modules = vector<pair<string, u16>>();

	if (_execute == nullptr || _count == nullptr)
		throw std::runtime_error("dll load module error.");
}

VModuleNative::~VModuleNative()
{
	FreeLibrary(_dll_inst);
}

u32 VModuleNative::function_count() const
{
	return _count();
}

shared_ptr<u8> VModuleNative::get_function(u32 index, VMachine * machine) const
{
	_execute(index, machine);
	return machine->ret_bytecode;
}
