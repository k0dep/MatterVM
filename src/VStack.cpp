#include "VStack.h"
using namespace mtr;

void mtr::VStack::init(u32 max_length)
{
}

void mtr::VStack::push(u8 val)
{
	_stack.push(val);
}

void mtr::VStack::push(u16 val)
{
	_stack.push((u8)(val & 0xFF));
	_stack.push((u8)((val >> 8) & 0xFF));
}

void mtr::VStack::push(u32 val)
{
	_stack.push((u8)(val & 0xFF));
	_stack.push((u8)((val >> 8) & 0xFF));
	_stack.push((u8)((val >> 16) & 0xFF));
	_stack.push((u8)((val >> 24) & 0xFF));
}

u8 mtr::VStack::pop_8()
{
	u8 res = _stack.top();
	_stack.pop();
	return res;
}

u16 mtr::VStack::pop_16()
{
	u16 res = 0x0;
	
	res |= _stack.top();
	_stack.pop();
	res = res << 8;

	res |= _stack.top();
	_stack.pop();

	return res;
}

u32 mtr::VStack::pop_32()
{
	u32 res = 0x0;

	res |= _stack.top();
	_stack.pop();
	res = res << 8;

	res |= _stack.top();
	_stack.pop();
	res = res << 8;

	res |= _stack.top();
	_stack.pop();
	res = res << 8;

	res |= _stack.top();
	_stack.pop();

	return res;
}
