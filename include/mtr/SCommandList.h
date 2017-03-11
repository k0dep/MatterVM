#pragma once

#ifndef _SCOMMAND_LIST_H_
#define _SCOMMAND_LIST_H_


#include <vector>
#include <memory>
#include <mtr/ICommand.h>

namespace mtr
{
	class SCommandList
	{
	public:
		static std::vector<std::shared_ptr<ICommand>> command_list;

		static int registre_global_command(std::shared_ptr<ICommand> cmd);
	};
}

#endif // !_SCOMMAND_LIST_H_
