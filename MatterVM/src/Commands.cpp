#include <memory>
#include <mtr/Commands.h>

using namespace std;
using namespace mtr;

vector<shared_ptr<ICommand>> ICommand::global_commands = vector<shared_ptr<ICommand>>();

void ICommand::init()
{
	ICommand::global_commands = vector<shared_ptr<ICommand>>();

	REG_CMD(CALL);
	REG_CMD(CALLS);
	REG_CMD(RET);

	REG_CMD(LDA);
	REG_CMD(LOAD);
	REG_CMD(PEEK);
	REG_CMD(STA);
	REG_CMD(STORE);

	REG_CMD(ZGOTO);
	REG_CMD(ZGOTOF);
	REG_CMD(NGOTO);
	REG_CMD(NGOTOF);
	REG_CMD(GOTO);

	REG_CMD(ITOF);
	REG_CMD(FTOI);

	REG_CMD(ADD);
	REG_CMD(ADDF);
	REG_CMD(SUB);
	REG_CMD(SUBF);
	REG_CMD(MUL);
	REG_CMD(MULF);
	REG_CMD(DIV);
	REG_CMD(DIVF);
	REG_CMD(MOD);

	REG_CMD(SHIFT);
	REG_CMD(AND);
	REG_CMD(OR);
	REG_CMD(XOR);
	REG_CMD(NOT);
}



IMPL_CMD(CALL, 6)
{
	u16 module_id = DataTypes::DataHelper::make_16(vm->operands);
	u32 func_id = DataTypes::DataHelper::make_32(vm->operands);
	vm->call_function(module_id, func_id);
	return true;
}

IMPL_CMD(CALLS, 0)
{
	u32 module_id = vm->stack.pop_32(); // должна быть u32
	u32 func_id = vm->stack.pop_32();
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
	auto addr = vm->stack.pop_32();
	auto value = vm->current_module->get_memory()->qword(addr);
	vm->stack.push(value);
	return true;
}

IMPL_CMD(LOAD, 4)
{
	auto wordAddr = DataTypes::DataHelper::make_32(vm->operands);
	auto res = vm->current_module->get_memory()->qword(wordAddr);
	vm->stack.push(res);
	return true;
}

IMPL_CMD(STORE, 4)
{
	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	auto value = vm->stack.pop_32();
	vm->current_module->get_memory()->qword(addr, value);
	return true;
}

IMPL_CMD(STA, 0)
{
	auto addr = vm->stack.pop_32();
	auto value = vm->stack.pop_32();
	vm->current_module->get_memory()->qword(addr, value);
	return true;
}

IMPL_CMD(PEEK, 0)
{
	vm->stack.pop_32();
	return true;
}





IMPL_CMD(GOTO, 4)
{
	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(NGOTO, 4)
{
	auto top = vm->stack.pop_32();
	if (top == 0) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(NGOTOF, 4)
{
	auto top = vm->stack.pop_f();
	if (top == 0.0f) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(ZGOTO, 4)
{
	auto top = vm->stack.pop_32();
	if (top != 0) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	vm->do_goto(addr);
	return true;
}

IMPL_CMD(ZGOTOF, 4)
{
	auto top = vm->stack.pop_f();
	if (top != 0.0f) return true;

	auto addr = DataTypes::DataHelper::make_32(vm->operands);
	vm->do_goto(addr);
	return true;
}





IMPL_CMD(ITOF, 0)
{
	auto top_f = (f)vm->stack.pop_32();
	vm->stack.push(top_f);
	return true;
}

IMPL_CMD(FTOI, 0)
{
	auto top_u32 = vm->stack.pop_32();
	auto res_f = reinterpret_cast<float&>(top_u32);
	auto res_u = (u32)res_f;
	vm->stack.push(res_u);
	return true;
}


IMPL_CMD_ARIFM_PACK(ADD, +)
IMPL_CMD_ARIFM_PACK(SUB, -)
IMPL_CMD_ARIFM_PACK(MUL, *)
IMPL_CMD_ARIFM_PACK(DIV, /)
IMPL_CMD_ARIFM(MOD, %)

IMPL_CMD(SHIFT, 0)
{
	auto shiftu = vm->stack.pop_32();
	auto shift = reinterpret_cast<i32&>(shiftu);
	auto value = vm->stack.pop_32();
	auto res = value >> shift;
	if (shift < 0)
		res = value << abs(shift);
	vm->stack.push(res);
	return true;
}

IMPL_CMD_ARIFM(AND, &)
IMPL_CMD_ARIFM(OR, |)
IMPL_CMD_ARIFM(XOR, ^)

IMPL_CMD(NOT, 0)
{
	auto value = vm->stack.pop_32();
	vm->stack.push(~value);
	return true;
}