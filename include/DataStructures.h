#pragma once

#include <iosfwd>

namespace mtr
{
	typedef unsigned char u8;
	typedef unsigned short int u16;
	typedef unsigned int u32;

	typedef char i8;
	typedef short int i16;
	typedef int i32;

	typedef float f;
}

namespace mtr::DataTypes
{
	#define	MAGIC_NUMBER (u16)0x4d2f;

	struct SHeader
	{
		u16 MagicNumber;
		u16 CountImports;
		u32 CountFunctions;
		u32 CountVarBytes;
		u32 CountVarWords;
		u32 CountVarQWords;
		u32 CountVarCustoms;

		static SHeader* read(std::istream &stream);
	};

	struct SFileStructure
	{
		SHeader* Head;
		SImportStructure** ArrImports;
		SFunctionStructure** ArrFunctions;
		u8* ArrValues;
		STypeStructure** ArrCustomValues;

		static SFileStructure* read(std::istream &stream);
	};


	struct SImportStructure
	{
		u32 NameLength;
		u16 Index;
		i8* Name;

		static SImportStructure* read(std::istream &stream);
	};


	struct SFunctionStructure
	{
		u32 BytecodeLength;
		i8* Bytecode;

		static SFunctionStructure* read(std::istream &stream);
	};

	struct STypeStructure
	{
		u8 Length;
		u8* Array;

		static STypeStructure* read(std::istream &stream);
	};
}