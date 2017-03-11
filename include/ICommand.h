#pragma once

#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include "VMachine.h"

namespace mtr
{
	class VMachine;

	class ICommand
	{
	public:
		virtual u8 code() const = 0;
		virtual u8 operand_count() const = 0;
		virtual bool execute(VMachine *vm) = 0;
	};

	namespace Commands
	{

#define CMD_CALL (u8)0x1	//
#define CMD_RET (u8)0x2		//
#define CMD_CALLS (u8)0x3	//

#define CMD_ADD (u8)0x4		//
#define CMD_ADDF (u8)0x5	//
#define CMD_SUB (u8)0x6		//
#define CMD_SUBF (u8)0x7	//
#define CMD_MUL (u8)0x8		//
#define CMD_MULF (u8)0x9	//
#define CMD_DIV (u8)0xA		//
#define CMD_DIVF (u8)0xB	//
#define CMD_MOD (u8)0xC		//

#define CMD_SHIFT (u8)0xD	//
#define CMD_AND (u8)0xE		//
#define CMD_OR (u8)0xF		//
#define CMD_XOR (u8)0x10	//
#define CMD_NOT (u8)0x11	//

#define CMD_LOAD (u8)0x12	//
#define CMD_STORE (u8)0x13	//
#define CMD_LDA (u8)0x14	//
#define CMD_STA (u8)0x15	//
#define CMD_PEEK (u8)0x16	//

#define CMD_ZGOTO (u8)0x17	//
#define CMD_ZGOTOF (u8)0x18	//
#define CMD_NGOTO (u8)0x19	//
#define CMD_NGOTOF (u8)0x1A	//
#define CMD_GOTO (u8)0x1B	//

#define CMD_ITOF (u8)0x1C	//
#define CMD_FTOI (u8)0x1D	//

	}

#define DECL_CMD(name) class Cmd##name : ICommand{		\
public:													\
	virtual u8 code() const override;					\
	virtual u8 operand_count() const override;			\
	virtual bool execute(VMachine * vm) override;		\
private:												\
	static int __code;									\
}


#define IMPL_CMD(name, op_cnt)													\
int mtr::Commands::Cmd##name ::__code =															\
SCommandList::registre_global_command(shared_ptr<ICommand>((ICommand*)new Cmd##name ()));	\
u8 mtr::Commands::Cmd##name ::code() const { return CMD_##name ; }								\
u8 mtr::Commands::Cmd##name ::operand_count() const { return (u8)(op_cnt); }					\
bool mtr::Commands::Cmd##name ::execute(VMachine * vm)


#define IMPL_CMD_ARIFM(name, op) IMPL_CMD(name, 0) {\
auto a = vm->_stack.pop_32();						\
auto b = vm->_stack.pop_32();						\
vm->_stack.push(a op b);							\
return true; }


#define IMPL_CMD_ARIFMF(name, op) IMPL_CMD(name, 0){	\
auto a_u = vm->_stack.pop_32();							\
auto b_u = vm->_stack.pop_32();							\
auto a = reinterpret_cast<float&>(a_u);					\
auto b = reinterpret_cast<float&>(b_u);					\
auto res = a op b;										\
vm->_stack.push(reinterpret_cast<u32&>(res));			\
return true; }

#define IMPL_CMD_ARIFM_PACK(name, op) IMPL_CMD_ARIFM(name, op) IMPL_CMD_ARIFMF(name##F, op)

}

#endif // !_ICOMMAND_H_