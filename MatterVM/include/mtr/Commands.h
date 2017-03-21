#pragma once

#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <mtr/VMachine.h>



namespace mtr
{

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


		DECL_CMD(CALL);
		DECL_CMD(CALLS);
		DECL_CMD(RET);

		DECL_CMD(LDA);
		DECL_CMD(LOAD);
		DECL_CMD(PEEK);
		DECL_CMD(STA);
		DECL_CMD(STORE);

		DECL_CMD(ZGOTO);
		DECL_CMD(ZGOTOF);
		DECL_CMD(NGOTO);
		DECL_CMD(NGOTOF);
		DECL_CMD(GOTO);

		DECL_CMD(ITOF);
		DECL_CMD(FTOI);

		DECL_CMD(ADD);
		DECL_CMD(ADDF);
		DECL_CMD(SUB);
		DECL_CMD(SUBF);
		DECL_CMD(MUL);
		DECL_CMD(MULF);
		DECL_CMD(DIV);
		DECL_CMD(DIVF);
		DECL_CMD(MOD);

		DECL_CMD(SHIFT);
		DECL_CMD(AND);
		DECL_CMD(OR);
		DECL_CMD(XOR);
		DECL_CMD(NOT);
	}}



#endif // !_COMMANDS_H_