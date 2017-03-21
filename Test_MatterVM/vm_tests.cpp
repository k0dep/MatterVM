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
	TEST_CLASS(BasicVMTest)
	{
	public:
		TEST_CLASS_INITIALIZE(WriteEntryPointBytecode)
		{
			char basic_program_arifm[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(3),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(10),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/

				// func 0
				MAKE_ARR_DWORD(30), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_LOAD, MAKE_ARR_DWORD(3),
				CMD_LOAD, MAKE_ARR_DWORD(2),
				CMD_LOAD, MAKE_ARR_DWORD(1),
				CMD_LOAD, MAKE_ARR_DWORD(0),

				CMD_ADD,
				CMD_SUB,
				CMD_MUL,
				CMD_DIV,

				CMD_RET,
				// end func 0

				// func 1
				MAKE_ARR_DWORD(30), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(4),
				CMD_LOAD, MAKE_ARR_DWORD(7),
				CMD_LOAD, MAKE_ARR_DWORD(6),
				CMD_LOAD, MAKE_ARR_DWORD(5),
				CMD_LOAD, MAKE_ARR_DWORD(4),

				CMD_ADDF,
				CMD_SUBF,
				CMD_MULF,
				CMD_DIVF,

				CMD_RET,
				//end func 1

				// func 1
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(8),
				CMD_LOAD, MAKE_ARR_DWORD(9),

				CMD_MOD,

				CMD_RET,
				//end func 1
				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				MAKE_ARR_DWORD(2),
				MAKE_ARR_DWORD(3),
				MAKE_ARR_DWORD(7),
				MAKE_ARR_DWORD(-4),

				MAKE_ARR_F_DWORD(2.0f),
				MAKE_ARR_F_DWORD(3.0f),
				MAKE_ARR_F_DWORD(7.0f),
				MAKE_ARR_F_DWORD(-4.0f),

				MAKE_ARR_DWORD(5),
				MAKE_ARR_DWORD(7),
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/
			};

			char basic_program[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x1,			// import count
				0x0, 0x0, 0x0, 0x1,	// function count
				0x0, 0x0, 0x0, 0x0, // cnt byte
				0x0, 0x0, 0x0, 0x0, // cnt word
				0x0, 0x0, 0x0, 0x2, // cnt qword
				0x0, 0x0, 0x0, 0x0, // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				0x2,				// name len
				0x0, 0x1,			// index
				'm', '1',	// name arra
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/

				// code:
				// -------   ---
				// store $0	 5
				// store $1  5
				// add		 1
				// ret		 1
				// -------	 12

				0x0, 0x0, 0x0, 19,	// bytecode len
				// array:
				CMD_LOAD,				// store 1b code
				0x0, 0x0, 0x0, 0x0,	// byte address 0 cell

				CMD_LOAD,				// store 1b code
				0x0, 0x0, 0x0, 0x1,	// byte address 0 cell

				CMD_ADD,				// add 1b command

				CMD_CALL,
				0x0, 0x1,
				0x0, 0x0, 0x0, 0x1,

				CMD_RET,				// ret code
				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				0x0, 0x0, 0x0, 0x1, // qword cell 0
				0x0, 0x0, 0x0, 0x2, // qword cell 1
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/
			};

			char logic[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(6),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(6),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/

				// func 0 not
				MAKE_ARR_DWORD(7), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0),

				CMD_NOT,

				CMD_RET,
				// end func 0

				// func 1 shift 24
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(1),
				CMD_LOAD, MAKE_ARR_DWORD(2),

				CMD_SHIFT,

				CMD_RET,
				//end func 1

				// func 2 shift -8
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(1),
				CMD_LOAD, MAKE_ARR_DWORD(3),

				CMD_SHIFT,

				CMD_RET,
				//end func 2

				// func 3 and
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(4),
				CMD_LOAD, MAKE_ARR_DWORD(5),

				CMD_AND,

				CMD_RET,
				//end func 3


				// func 4 or
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(4),
				CMD_LOAD, MAKE_ARR_DWORD(5),

				CMD_OR,

				CMD_RET,
				//end func 4

				// func 4 or
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(4),
				CMD_LOAD, MAKE_ARR_DWORD(5),

				CMD_XOR,

				CMD_RET,
				//end func 4

				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				MAKE_ARR_DWORD(0xFFFFFFFF),
				MAKE_ARR_DWORD(0xFA000000),
				MAKE_ARR_DWORD(24),
				MAKE_ARR_DWORD(-4),

				MAKE_ARR_DWORD(0xFFAB0000),
				MAKE_ARR_DWORD(0x000B0CAF),
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/

			};

			char jumping[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(5),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(5),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/

				// func 0
				MAKE_ARR_DWORD(16), // bytecode len

				CMD_GOTO, MAKE_ARR_DWORD(10),
				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_LOAD, MAKE_ARR_DWORD(1),

				CMD_RET,
				// end func 0


				// func 1 NGOTO
				MAKE_ARR_DWORD(31), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0), //5

				CMD_NGOTO, MAKE_ARR_DWORD(15), //10
				CMD_LOAD, MAKE_ARR_DWORD(0),  //15

				CMD_LOAD, MAKE_ARR_DWORD(2),  //20

				CMD_NGOTO, MAKE_ARR_DWORD(30), //25

				CMD_LOAD, MAKE_ARR_DWORD(1), //30

				CMD_RET,
				// end func 1



				// func 2 NGOTOF
				MAKE_ARR_DWORD(31), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(4), //5

				CMD_NGOTOF, MAKE_ARR_DWORD(15), //10
				CMD_LOAD, MAKE_ARR_DWORD(0),  //15

				CMD_LOAD, MAKE_ARR_DWORD(3),  //20

				CMD_NGOTOF, MAKE_ARR_DWORD(30), //25

				CMD_LOAD, MAKE_ARR_DWORD(1), //30

				CMD_RET,
				// end func 2




				// func 3 ZGOTO
				MAKE_ARR_DWORD(31), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(2), //5

				CMD_ZGOTO, MAKE_ARR_DWORD(15), //10
				CMD_LOAD, MAKE_ARR_DWORD(0),  //15

				CMD_LOAD, MAKE_ARR_DWORD(0),  //20

				CMD_ZGOTO, MAKE_ARR_DWORD(30), //25

				CMD_LOAD, MAKE_ARR_DWORD(1), //30

				CMD_RET,
				// end func 3



				// func 4 ZGOTOF
				MAKE_ARR_DWORD(31), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(3), //5

				CMD_ZGOTO, MAKE_ARR_DWORD(15), //10
				CMD_LOAD, MAKE_ARR_DWORD(0),  //15

				CMD_LOAD, MAKE_ARR_DWORD(4),  //20

				CMD_ZGOTO, MAKE_ARR_DWORD(30), //25

				CMD_LOAD, MAKE_ARR_DWORD(1), //30

				CMD_RET,
				// end func 4

				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				MAKE_ARR_DWORD(11),
				MAKE_ARR_DWORD(0xFF),
				MAKE_ARR_DWORD(0),
				MAKE_ARR_F_DWORD(0.0f),
				MAKE_ARR_F_DWORD(1.0f),
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/

			};
			
			char casting[] = {
				/*====== HEADER ======*/
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(2),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(2),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				/*====== HEADER ======*/


				/*====== IMPORTS ======*/
				/*====== IMPORTS ======*/


				/*====== FUNCTIONS ======*/

				// func 0
				MAKE_ARR_DWORD(7), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_ITOF,

				CMD_RET,
				// end func 0


				// func 0
				MAKE_ARR_DWORD(7), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(1),
				CMD_FTOI,

				CMD_RET,
				// end func 0

				/*====== FUNCTIONS ======*/


				/*====== VALUES ======*/
				MAKE_ARR_DWORD(12),
				MAKE_ARR_F_DWORD(-3.56f),
				/*====== VALUES ======*/


				/*====== CUSTOM VALUES ======*/
				/*====== CUSTOM VALUES ======*/

			};
			
			char func[] = {
				//====== HEADER ======
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(3),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(3),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				//====== HEADER ======


				//====== IMPORTS ======
				//====== IMPORTS ======


				//====== FUNCTIONS ======

				// func 0
				MAKE_ARR_DWORD(13), // bytecode len
				CMD_CALL, 0x0, 0x0, MAKE_ARR_DWORD(1),
				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_RET,
				// end func 0

				// func 1
				MAKE_ARR_DWORD(17), // bytecode len
				CMD_LOAD, MAKE_ARR_DWORD(2),
				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_CALLS,
				CMD_LOAD, MAKE_ARR_DWORD(1),
				CMD_RET,
				// end func 1

				// func 2
				MAKE_ARR_DWORD(6), // bytecode len
				CMD_LOAD, MAKE_ARR_DWORD(2),
				CMD_RET,
				// end func 2

				//====== FUNCTIONS ======


				//====== VALUES ======
				MAKE_ARR_DWORD(0),
				MAKE_ARR_DWORD(1),
				MAKE_ARR_DWORD(2),				
				//====== VALUES ======


				//====== CUSTOM VALUES ======
				//====== CUSTOM VALUES ======

			};	

			char load[] = {
				//====== HEADER ======
				0x4d, 0x2d,			// magic number
				0x0, 0x0,			// import count
				MAKE_ARR_DWORD(4),	// function count
				MAKE_ARR_DWORD(0),	// cnt byte
				MAKE_ARR_DWORD(0),	// cnt word
				MAKE_ARR_DWORD(4),	// cnt qword
				MAKE_ARR_DWORD(0), // cnt cust
				//====== HEADER ======


				//====== IMPORTS ======
				//====== IMPORTS ======


				//====== FUNCTIONS ======

				// func 0
				MAKE_ARR_DWORD(7), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_LDA,
				CMD_RET,
				// end func 0


				// func 1
				MAKE_ARR_DWORD(16), // bytecode len
				
				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_STORE, MAKE_ARR_DWORD(3),
				CMD_LOAD, MAKE_ARR_DWORD(3),
				CMD_RET,
				// end func 1


				// func 2
				MAKE_ARR_DWORD(17), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(2),
				CMD_LOAD, MAKE_ARR_DWORD(2),
				CMD_STA,
				CMD_LOAD, MAKE_ARR_DWORD(3),
				CMD_RET,
				// end func 2

				// func 3
				MAKE_ARR_DWORD(12), // bytecode len

				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_LOAD, MAKE_ARR_DWORD(0),
				CMD_PEEK,
				CMD_RET,
				// end func 3

				//====== FUNCTIONS ======


				//====== VALUES ======
				MAKE_ARR_DWORD(1),
				MAKE_ARR_DWORD(2),
				MAKE_ARR_DWORD(3),
				MAKE_ARR_DWORD(0),
				//====== VALUES ======


				//====== CUSTOM VALUES ======
				//====== CUSTOM VALUES ======

			};



			WRITE_BYTECODE("entry", basic_program);
			WRITE_BYTECODE("arifm", basic_program_arifm);
			WRITE_BYTECODE("logic", logic);
			WRITE_BYTECODE("jumping", jumping);
			WRITE_BYTECODE("casting", casting);
			WRITE_BYTECODE("func", func);
			WRITE_BYTECODE("load", load);

			ModuleLoader::path = string(TEST_CASE_DIRECTORY) + "test_env\\";
		}



		TEST_METHOD(InitVM)
		{
			ModuleLoader::path = string(TEST_CASE_DIRECTORY) + "test_env\\";
			auto entryModule = ModuleLoader::load_moodule("entry");
			VMachine vm;
			vm.init(entryModule);
		}




		TEST_METHOD(RunVM)
		{
			auto entryModule = ModuleLoader::load_moodule("entry");
			VMachine vm;
			vm.init(entryModule);

			vm.run(0);
			Assert::AreEqual(vm.stack.pop_32(), (u32)3);
		}




		TEST_METHOD(ComplexArifm)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("arifm"));

			vm.run(0);
			Assert::AreEqual((u32)4, vm.stack.pop_32(), L"integer bad");

			vm.run(1);
			Assert::AreEqual(4.0f, vm.stack.pop_f(), L"float bad");

			vm.run(2);
			Assert::AreEqual((u32)2, vm.stack.pop_32(), L"`MOD` bad");
		}




		TEST_METHOD(ComplexLogic)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("logic"));

			//not
			vm.run(0);
			Assert::AreEqual((u32)0, vm.stack.pop_32(), L"`NOT` bad");

			//shift 24
			vm.run(1);
			Assert::AreEqual((u32)0xFA, vm.stack.pop_32(), L"`SHIFT` 24 bad");

			//shift -8
			vm.run(2);
			Assert::AreEqual((u32)0xA0000000, vm.stack.pop_32(), L"`SHIFT` -8 bad");

			//and
			vm.run(3);
			Assert::AreEqual((u32)0xB0000, vm.stack.pop_32(), L"`AND` bad");

			//or
			vm.run(4);
			Assert::AreEqual((u32)0xFFAB0CAF, vm.stack.pop_32(), L"`OR` bad");

			//xor
			vm.run(5);
			Assert::AreEqual((u32)0xFFA00CAF, vm.stack.pop_32(), L"`XOR` bad");
		}




		TEST_METHOD(ComplexJump)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("jumping"));

			//goto
			vm.run(0);
			Assert::AreEqual((u32)4, vm.stack.size(), L"`GOTO` bad");

			//ngoto
			vm.run(1);
			Assert::AreEqual((u32)4, vm.stack.size(), L"`NGOTO` bad");

			//ngotof
			vm.run(2);
			Assert::AreEqual((u32)4, vm.stack.size(), L"`NGOTOF` bad");

			//zgoto
			vm.run(3);
			Assert::AreEqual((u32)4, vm.stack.size(), L"`ZGOTO` bad");

			//zgotof
			vm.run(4);
			Assert::AreEqual((u32)4, vm.stack.size(), L"`ZGOTOF` bad");
		}




		TEST_METHOD(CastingTest)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("casting"));

			vm.run(0);
			Assert::AreEqual((f)12.0f, vm.stack.pop_f(), L"`ITOF` bad");

			vm.run(1);
			Assert::AreEqual((u32)-3, vm.stack.pop_32(), L"`FTOI` bad");
		}




		TEST_METHOD(CallFunctionsTest)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("func"));

			vm.run(0);
			Assert::AreEqual((u32)12, vm.stack.size(), L"calling stack result bad");
			Assert::AreEqual((u32)0, vm.stack.pop_32(), L"1 res bad");
			Assert::AreEqual((u32)1, vm.stack.pop_32(), L"2 res bad");
			Assert::AreEqual((u32)2, vm.stack.pop_32(), L"3 res bad");
		}




		TEST_METHOD(MemoryTest)
		{
			VMachine vm;
			vm.init(ModuleLoader::load_moodule("load"));

			vm.run(0);
			Assert::AreEqual((u32)2, vm.stack.pop_32(), L"1 res bad");

			vm.run(1);
			Assert::AreEqual((u32)1, vm.stack.pop_32(), L"2 res bad");

			vm.run(2);
			Assert::AreEqual((u32)3, vm.stack.pop_32(), L"3 res bad");

			vm.run(3);
			Assert::AreEqual((u32)4, vm.stack.size(), L"peek bad");
		}




		TEST_METHOD(DWORDMacros)
		{
			u8 bytes[] = { MAKE_ARR_DWORD(-2) };
			Assert::AreEqual(bytes[0], (u8)0xFF);
			Assert::AreEqual(bytes[1], (u8)0xFF);
			Assert::AreEqual(bytes[2], (u8)0xFF);
			Assert::AreEqual(bytes[3], (u8)0xFE);

			u8 bytes_f[] = { MAKE_ARR_F_DWORD(12.7f) };
			Assert::AreEqual(bytes_f[0], (u8)0x41);
			Assert::AreEqual(bytes_f[1], (u8)0x4B);
			Assert::AreEqual(bytes_f[2], (u8)0x33);
			Assert::AreEqual(bytes_f[3], (u8)0x33);
		}
	};
}