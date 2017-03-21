#pragma once

#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include <vector>
#include <mtr/VMachine.h>

namespace mtr
{
	class VMachine;

	class ICommand
	{
	public:
		virtual u8 code() const = 0;
		virtual u8 operand_count() const = 0;
		virtual bool execute(VMachine *vm) = 0;

		static void init();
		static std::vector<std::shared_ptr<ICommand>> global_commands;
	};

#define DECL_CMD(name) class Cmd##name : ICommand{		\
public:													\
	virtual u8 code() const override;					\
	virtual u8 operand_count() const override;			\
	virtual bool execute(VMachine * vm) override;		\
}


#define IMPL_CMD(name, op_cnt)													\
u8 mtr::Commands::Cmd##name ::code() const { return CMD_##name ; }				\
u8 mtr::Commands::Cmd##name ::operand_count() const { return (u8)(op_cnt); }	\
bool mtr::Commands::Cmd##name ::execute(VMachine * vm)


#define IMPL_CMD_ARIFM_TEMPLATE(name, op, func) IMPL_CMD(name, 0) {\
auto a = vm->stack.pop_##func();						\
auto b = vm->stack.pop_##func();						\
vm->stack.push(a op b);							\
return true; }

#define IMPL_CMD_ARIFM(name, op) IMPL_CMD_ARIFM_TEMPLATE(name, op, 32)
#define IMPL_CMD_ARIFM_F(name, op) IMPL_CMD_ARIFM_TEMPLATE(name, op, f)

#define REG_CMD(name) mtr::ICommand::global_commands.push_back(std::shared_ptr<mtr::ICommand>((ICommand*)new mtr::Commands::Cmd##name ()));

#define IMPL_CMD_ARIFM_PACK(name, op) IMPL_CMD_ARIFM(name, op) IMPL_CMD_ARIFM_F(name##F, op)

}

#endif // !_ICOMMAND_H_