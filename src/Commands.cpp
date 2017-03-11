#include <memory>
#include <mtr/Commands.h>
#include <mtr/SCommandList.h>

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



IMPL_CMD_ARIFM_PACK(ADD, +)
IMPL_CMD_ARIFM_PACK(SUB, -)
IMPL_CMD_ARIFM_PACK(MUL, *)
IMPL_CMD_ARIFM_PACK(DIV, /)

IMPL_CMD(MOD, 0)
{
	auto a = vm->_stack.pop_32();
	auto b = vm->_stack.pop_32();
	auto res = a % b;
	vm->_stack.push(res);
	return true;
}

IMPL_CMD(SHIFT, 0)
{
	auto shiftu = vm->_stack.pop_32();
	auto shift = reinterpret_cast<i32&>(shiftu);
	auto value = vm->_stack.pop_32();
	auto res = value >> shift;
	if (shift < 0)
		res = value << abs(shift);
	vm->_stack.push(res);
	return true;
}

IMPL_CMD_ARIFM(AND, &)
IMPL_CMD_ARIFM(OR, |)
IMPL_CMD_ARIFM(XOR, ^)

IMPL_CMD(NOT, 0)
{
	auto value = vm->_stack.pop_32();
	vm->_stack.push(~value);
	return true;
}