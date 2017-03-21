#include "stdafx.h"
#include <stdio.h>

#include <mtr/DataStructures.h>
#include <mtr/ModuleLoader.h>
#include <mtr/Commands.h>

#include <memory>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace mtr;
using namespace mtr::DataTypes;

namespace MatterVMTest
{
	TEST_CLASS(MemoryTest)
	{
	public:
		TEST_CLASS_INITIALIZE(MemoryTestInit)
		{
			char basic_prog[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(0),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(5),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/
				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				MAKE_ARR_DWORD(2),
				MAKE_ARR_DWORD(-4),
				MAKE_ARR_F_DWORD(2.0f),
				MAKE_ARR_F_DWORD(-4.0f),
				MAKE_ARR_DWORD(0xAABBCCDD),
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/
			};

			WRITE_BYTECODE("memtest", basic_prog);
		}


		TEST_METHOD(MemReadTest)
		{
			ModuleLoader::path = string(TEST_CASE_DIRECTORY) + "test_env\\";
			auto entryModule = ModuleLoader::load_moodule("memtest");

			Assert::AreEqual((u32)0xAABBCCDD, entryModule->get_memory()->qword(4));

			Assert::AreEqual((u32)2, entryModule->get_memory()->qword(0), L"int 1 bad");
			Assert::AreEqual(-4, (int)entryModule->get_memory()->qword(1), L"int 2 bad");
			Assert::AreEqual((f)2.0f, DataHelper::utof(entryModule->get_memory()->qword(2)), L"float 1 bad");
			Assert::AreEqual((f)-4.0f, DataHelper::utof(entryModule->get_memory()->qword(3)), L"Float 2 bad");
		}
	};
}