#pragma once

#ifndef _VSTACK_H_
#define _VSTACK_H_

#include <stack>
#include <mtr/DataStructures.h>

namespace mtr
{
	class VStack
	{
	public:
		void init(u32 max_length);

		void push(u8 val);
		void push(u16 val);
		void push(u32 val);

		u8 pop_8();
		u16 pop_16();
		u32 pop_32();


	protected:
		std::stack<u8> _stack;
	};
}

#endif // !_VSTACK_H_