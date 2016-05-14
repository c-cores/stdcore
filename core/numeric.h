#pragma once

namespace core
{

template <class value_type>
struct hex
{
	hex(value_type v)
	{
		value = v;
	}

	~hex() {}

	value_type value;
};

}

