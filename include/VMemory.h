#pragma once

#include <memory>
#include "DataStructures.h"

namespace mtr
{
	class VMemory
	{
	public:
		VMemory();

		bool init(std::shared_ptr<DataTypes::SFileStructure> file);

		u8 byte(u32 index) const;
		void byte(u32 index, u8 new_val);


		u16 word(u32 index) const;
		void word(u32 index, u8 new_val);


		u32 qword(u32 index) const;
		void qword(u32 index, u8 new_val);

	protected:
		std::shared_ptr<DataTypes::SFileStructure> _file;
	};

}