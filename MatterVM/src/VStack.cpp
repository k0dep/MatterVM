#include <mtr/VStack.h>
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
	union
	{
		u16 u;
		u8 ub[2];
	} res;

	res.u = val;

	_stack.push(res.ub[0]);
	_stack.push(res.ub[1]);
}

void mtr::VStack::push(u32 val)
{
	union
	{
		u32 u;
		u8 ub[4];
	} res;

	res.u = val;

	_stack.push(res.ub[0]);
	_stack.push(res.ub[1]);
	_stack.push(res.ub[2]);
	_stack.push(res.ub[3]);
}

void mtr::VStack::push(f val)
{
	union
	{
		float f_val;
		u32 u_val;
	} flb;

	flb.f_val = val;
	push(flb.u_val);
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
	union {
		u32 u;
		u8 ub[4];
	} res;

	res.ub[3] = _stack.top();
	_stack.pop();

	res.ub[2] = _stack.top();
	_stack.pop();

	res.ub[1] = _stack.top();
	_stack.pop();

	res.ub[0] = _stack.top();
	_stack.pop();

	return res.u;
}

f mtr::VStack::pop_f()
{
	union {
		f float_variable;
		u32 u_val;
	} u;

	u.u_val = pop_32();

	return u.float_variable;
}

u32 mtr::VStack::size()
{
	return _stack.size();
}
