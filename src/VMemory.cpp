#include <mtr/VMemory.h>
using namespace mtr;

bool mtr::VMemory::init(std::shared_ptr<DataTypes::SFileStructure> file)
{
	_file = file;
	return true;
}

u8 mtr::VMemory::byte(u32 index) const
{
	return _file->byteValue(index);
}

void mtr::VMemory::byte(u32 index, u8 new_val)
{
	_file->byteValue(index, new_val);
}

u16 mtr::VMemory::word(u32 index) const
{
	return _file->wordValue(index);
}

void mtr::VMemory::word(u32 index, u8 new_val)
{
	_file->wordValue(index, new_val);
}

u32 mtr::VMemory::qword(u32 index) const
{
	return _file->qwordValue(index);
}

void mtr::VMemory::qword(u32 index, u8 new_val)
{
	_file->wordValue(index, new_val);
}
