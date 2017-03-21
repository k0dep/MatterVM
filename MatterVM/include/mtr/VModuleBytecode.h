#pragma once

#ifndef _VMODULEBYTECODE_H_
#define _VMODULEBYTECODE_H_


#pragma once
#include <mtr/VModuleBase.h>
#include <string>

namespace mtr
{
	class VModuleBytecode : VModuleBase
	{
	public:
		VModuleBytecode(std::shared_ptr<DataTypes::SFileStructure> data, std::string name);

		// Унаследовано через VModuleBase
		virtual u32 function_count() const override;
		virtual std::string get_name() const override;
		virtual std::shared_ptr<u8> get_function(u32 index, VMachine * machine) const override;

	protected:
		std::shared_ptr<DataTypes::SFileStructure> _data;
	};
}

#endif // !_VMODULEBYTECODE_H_
