#pragma once

#include "VMachine.h"
#include "VMemory.h"

namespace mtr
{
	class VMachine;
	class VModule;

	typedef void(VModule::* ExecutePtr)(VMachine * machine);

	class VModule
	{
	public:
		friend VMachine;

		virtual bool init() = 0;
		virtual bool init(std::shared_ptr<DataTypes::SFileStructure> file) = 0;

		virtual std::vector<std::pair<std::string, u16>> require_modules();

		u32 function_count() const;
		std::string get_name() const;

	protected:
		u32 register_function(ExecutePtr ptr);
		std::pair<std::shared_ptr<u8>, ExecutePtr> get_function(u32 index) const;

		std::vector<std::pair<std::shared_ptr<u8>, ExecutePtr>> _functions;
		std::shared_ptr<VMemory> _memory;
		std::shared_ptr<DataTypes::SFileStructure> _data;
		std::vector<std::pair<std::string, u16>> _required_modules;
		std::string _name;
	};
}