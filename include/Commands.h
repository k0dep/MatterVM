#pragma once

#ifndef _COMMANDS_H_

#include "VMachine.h"

namespace mtr
{
	namespace Commands
	{
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
	}
}



#endif // !_COMMANDS_H_