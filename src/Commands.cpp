#include "Commands.h"
#include "SCommandList.h"
#include <memory>

using namespace std;
using namespace mtr;



IMPL_CMD(CALL, 6)
{
	u16 module_id = DataTypes::DataHelper::make_16(vm->_operands);
	u32 func_id = DataTypes::DataHelper::make_32(vm->_operands);
	vm->call_function(module_id, func_id);
	return true;
}

IMPL_CMD(CALLS, 0)
{
	u16 module_id = vm->_stack.pop_16();
	u32 func_id = vm->_stack.pop_32();
	vm->call_function(module_id, func_id);
	return true;
}

IMPL_CMD(RET, 0)
{
	vm->ret_function();
	return true;
}






IMPL_CMD(LDA, 0)
{
	auto addr = vm->_stack.pop_32();
	auto value = vm->_current_module->get_memory()->qword(addr);
	vm->_stack.push(value);
	return true;
}

IMPL_CMD(LOAD, 4)
{
	auto wordAddr = DataTypes::DataHelper::make_32(vm->_operands);
	auto res = vm->_current_module->get_memory()->qword(wordAddr);
	vm->_stack.push(res);
	return true;
}

IMPL_CMD(STORE, 4)
{
	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	auto value = vm->_stack.pop_32();
	vm->_current_module->get_memory()->qword(addr, value);
	return true;
}

IMPL_CMD(STA, 0)
{
	auto addr = vm->_stack.pop_32();
	auto value = vm->_stack.pop_32();
	vm->_current_module->get_memory()->qword(addr, value);
	return true;
}

IMPL_CMD(PEEK, 0)
{
	vm->_stack.pop_32();
	return true;
}





IMPL_CMD(GOTO, 4)
{
	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(NGOTO, 4)
{
	auto top = vm->_stack.pop_32();
	if (top == 0) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(NGOTOF, 4)
{
	auto top_u32 = vm->_stack.pop_32();
	auto top = reinterpret_cast<float&>(top_u32);
	if (top == 0.0f) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(ZGOTO, 4)
{
	auto top = vm->_stack.pop_32();
	if (top != 0) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(ZGOTOF, 4)
{
	auto top_u32 = vm->_stack.pop_32();
	auto top = reinterpret_cast<float&>(top_u32);
	if (top != 0.0f) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->_operands);
	vm->do_goto(addr);
	return true;
}





IMPL_CMD(ITOF, 0)
{
	auto top_f = (f)vm->_stack.pop_32();
	auto res_u = reinterpret_cast<u32&>(top_f);
	vm->_stack.push(res_u);
	return true;
}

IMPL_CMD(FTOI, 0)
{
	auto top_u32 = vm->_stack.pop_32();
	auto res_f = reinterpret_cast<float&>(top_u32);
	auto res_u = (u32)res_f;
	vm->_stack.push(res_u);
	return true;
}






IMPL_CMD(ADD, 0)
{
	auto a = vm->_stack.pop_32();
	auto b = vm->_stack.pop_32();
	vm->_stack.push(a + b);
	return true;
}

IMPL_CMD(ADDF, 0)
{
	auto a_u = vm->_stack.pop_32();
	auto b_u = vm->_stack.pop_32();

	auto a = reinterpret_cast<float&>(a_u);
	auto b = reinterpret_cast<float&>(b_u);
	auto res = a + b;
	vm->_stack.push(reinterpret_cast<u32&>(res));
	return true;
}