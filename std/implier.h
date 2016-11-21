#pragma once

namespace core
{

template <class ktype, class vtype>
struct implier
{
	implier() {}
	implier(ktype k, vtype v)
	{
		key = k;
		value = v;
	}
	~implier() {}

	ktype key;
	vtype value;
};

template <class ktype, class vtype>
bool operator<(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key < i1.key);
}

template <class ktype, class vtype>
bool operator>(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key > i1.key);
}

template <class ktype, class vtype>
bool operator<=(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key <= i1.key);
}

template <class ktype, class vtype>
bool operator>=(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key >= i1.key);
}

template <class ktype, class vtype>
bool operator==(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key == i1.key);
}

template <class ktype, class vtype>
bool operator!=(implier<ktype, vtype> i0, implier<ktype, vtype> i1)
{
	return (i0.key != i1.key);
}

template <class ktype, class vtype>
bool operator<(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key < i1);
}

template <class ktype, class vtype>
bool operator>(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key > i1);
}

template <class ktype, class vtype>
bool operator<=(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key <= i1);
}

template <class ktype, class vtype>
bool operator>=(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key >= i1);
}

template <class ktype, class vtype>
bool operator==(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key == i1);
}

template <class ktype, class vtype>
bool operator!=(implier<ktype, vtype> i0, ktype i1)
{
	return (i0.key != i1);
}

template <class ktype, class vtype>
bool operator<(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 < i1.key);
}

template <class ktype, class vtype>
bool operator>(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 > i1.key);
}

template <class ktype, class vtype>
bool operator<=(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 <= i1.key);
}

template <class ktype, class vtype>
bool operator>=(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 >= i1.key);
}

template <class ktype, class vtype>
bool operator==(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 == i1.key);
}

template <class ktype, class vtype>
bool operator!=(ktype i0, implier<ktype, vtype> i1)
{
	return (i0 != i1.key);
}

}

