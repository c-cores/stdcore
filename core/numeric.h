#pragma once

namespace core
{

template <class value_type>
struct hex
{
	hex(const value_type &v)
	{
		value = &v;
	}

	~hex() {}

	const value_type *value;
};

template <class value_type>
struct bin
{
	bin(const value_type &v)
	{
		value = &v;
	}

	~bin() {}

	const value_type *value;
};

}

