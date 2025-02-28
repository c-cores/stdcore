#pragma once

#include <typeinfo>
#include <cassert>
#include <functional>

// This header creates a Golang-style interface using C++ macros.
//
// Define your interface like so:
// INTERFACE(Person,
// 	(const char*, name, ()),
// 	(void, talk, (int lang))
// )
//
// Each function takes 3 arguments:
// 1. return type
// 2. name
// 3. argument declarations
//
// Then you can use your interface as you'd expect:
// void talkabout (Person t) {
// 	printf("%s says:\n", t.name());
// 	t.talk(0);
// }
//
// struct Foo {
// 	int x;
// 	const char* name() { return "Foo"; }
// 	void talk(int lang) { printf("I'm a Foo with a %d!\n", this->x); }
// };
//
// int main () {
// 	Foo x = {24};
// 	talkabout(x);
// 	return 0;
// }

// These macros extract the tuple elements.
#define DECL_MEMBER(method) DECL_MEMBER_ method
#define DECL_MEMBER_(ret, name, params) ret (T::*name) params;

#define DECL_METHOD(method) DECL_METHOD_ method
#define DECL_METHOD_(ret, name, params) template <typename... Args> inline ret name(Args&&... args) const { return (p->*(vt->name))(std::forward<Args>(args)...); }

#define INIT_METHOD(method) INIT_METHOD_ method
#define INIT_METHOD_(ret, name, params) &T::name,

// --- FOR_EACH machinery (supports up to 100 methods) ---
#define FOR_EACH_1(what, x) what(x)
#define FOR_EACH_2(what, x, ...) what(x) FOR_EACH_1(what, __VA_ARGS__)
#define FOR_EACH_3(what, x, ...) what(x) FOR_EACH_2(what, __VA_ARGS__)
#define FOR_EACH_4(what, x, ...) what(x) FOR_EACH_3(what, __VA_ARGS__)
#define FOR_EACH_5(what, x, ...) what(x) FOR_EACH_4(what, __VA_ARGS__)
#define FOR_EACH_6(what, x, ...) what(x) FOR_EACH_5(what, __VA_ARGS__)
#define FOR_EACH_7(what, x, ...) what(x) FOR_EACH_6(what, __VA_ARGS__)
#define FOR_EACH_8(what, x, ...) what(x) FOR_EACH_7(what, __VA_ARGS__)
#define FOR_EACH_9(what, x, ...) what(x) FOR_EACH_8(what, __VA_ARGS__)
#define FOR_EACH_10(what, x, ...) what(x) FOR_EACH_9(what, __VA_ARGS__)
#define FOR_EACH_11(what, x, ...) what(x) FOR_EACH_10(what, __VA_ARGS__)
#define FOR_EACH_12(what, x, ...) what(x) FOR_EACH_11(what, __VA_ARGS__)
#define FOR_EACH_13(what, x, ...) what(x) FOR_EACH_12(what, __VA_ARGS__)
#define FOR_EACH_14(what, x, ...) what(x) FOR_EACH_13(what, __VA_ARGS__)
#define FOR_EACH_15(what, x, ...) what(x) FOR_EACH_14(what, __VA_ARGS__)
#define FOR_EACH_16(what, x, ...) what(x) FOR_EACH_15(what, __VA_ARGS__)
#define FOR_EACH_17(what, x, ...) what(x) FOR_EACH_16(what, __VA_ARGS__)
#define FOR_EACH_18(what, x, ...) what(x) FOR_EACH_17(what, __VA_ARGS__)
#define FOR_EACH_19(what, x, ...) what(x) FOR_EACH_18(what, __VA_ARGS__)
#define FOR_EACH_20(what, x, ...) what(x) FOR_EACH_19(what, __VA_ARGS__)
#define FOR_EACH_21(what, x, ...) what(x) FOR_EACH_20(what, __VA_ARGS__)
#define FOR_EACH_22(what, x, ...) what(x) FOR_EACH_21(what, __VA_ARGS__)
#define FOR_EACH_23(what, x, ...) what(x) FOR_EACH_22(what, __VA_ARGS__)
#define FOR_EACH_24(what, x, ...) what(x) FOR_EACH_23(what, __VA_ARGS__)
#define FOR_EACH_25(what, x, ...) what(x) FOR_EACH_24(what, __VA_ARGS__)
#define FOR_EACH_26(what, x, ...) what(x) FOR_EACH_25(what, __VA_ARGS__)
#define FOR_EACH_27(what, x, ...) what(x) FOR_EACH_26(what, __VA_ARGS__)
#define FOR_EACH_28(what, x, ...) what(x) FOR_EACH_27(what, __VA_ARGS__)
#define FOR_EACH_29(what, x, ...) what(x) FOR_EACH_28(what, __VA_ARGS__)
#define FOR_EACH_30(what, x, ...) what(x) FOR_EACH_29(what, __VA_ARGS__)
#define FOR_EACH_31(what, x, ...) what(x) FOR_EACH_30(what, __VA_ARGS__)
#define FOR_EACH_32(what, x, ...) what(x) FOR_EACH_31(what, __VA_ARGS__)
#define FOR_EACH_33(what, x, ...) what(x) FOR_EACH_32(what, __VA_ARGS__)
#define FOR_EACH_34(what, x, ...) what(x) FOR_EACH_33(what, __VA_ARGS__)
#define FOR_EACH_35(what, x, ...) what(x) FOR_EACH_34(what, __VA_ARGS__)
#define FOR_EACH_36(what, x, ...) what(x) FOR_EACH_35(what, __VA_ARGS__)
#define FOR_EACH_37(what, x, ...) what(x) FOR_EACH_36(what, __VA_ARGS__)
#define FOR_EACH_38(what, x, ...) what(x) FOR_EACH_37(what, __VA_ARGS__)
#define FOR_EACH_39(what, x, ...) what(x) FOR_EACH_38(what, __VA_ARGS__)
#define FOR_EACH_40(what, x, ...) what(x) FOR_EACH_39(what, __VA_ARGS__)
#define FOR_EACH_41(what, x, ...) what(x) FOR_EACH_40(what, __VA_ARGS__)
#define FOR_EACH_42(what, x, ...) what(x) FOR_EACH_41(what, __VA_ARGS__)
#define FOR_EACH_43(what, x, ...) what(x) FOR_EACH_42(what, __VA_ARGS__)
#define FOR_EACH_44(what, x, ...) what(x) FOR_EACH_43(what, __VA_ARGS__)
#define FOR_EACH_45(what, x, ...) what(x) FOR_EACH_44(what, __VA_ARGS__)
#define FOR_EACH_46(what, x, ...) what(x) FOR_EACH_45(what, __VA_ARGS__)
#define FOR_EACH_47(what, x, ...) what(x) FOR_EACH_46(what, __VA_ARGS__)
#define FOR_EACH_48(what, x, ...) what(x) FOR_EACH_47(what, __VA_ARGS__)
#define FOR_EACH_49(what, x, ...) what(x) FOR_EACH_48(what, __VA_ARGS__)
#define FOR_EACH_50(what, x, ...) what(x) FOR_EACH_49(what, __VA_ARGS__)
#define FOR_EACH_51(what, x, ...) what(x) FOR_EACH_50(what, __VA_ARGS__)
#define FOR_EACH_52(what, x, ...) what(x) FOR_EACH_51(what, __VA_ARGS__)
#define FOR_EACH_53(what, x, ...) what(x) FOR_EACH_52(what, __VA_ARGS__)
#define FOR_EACH_54(what, x, ...) what(x) FOR_EACH_53(what, __VA_ARGS__)
#define FOR_EACH_55(what, x, ...) what(x) FOR_EACH_54(what, __VA_ARGS__)
#define FOR_EACH_56(what, x, ...) what(x) FOR_EACH_55(what, __VA_ARGS__)
#define FOR_EACH_57(what, x, ...) what(x) FOR_EACH_56(what, __VA_ARGS__)
#define FOR_EACH_58(what, x, ...) what(x) FOR_EACH_57(what, __VA_ARGS__)
#define FOR_EACH_59(what, x, ...) what(x) FOR_EACH_58(what, __VA_ARGS__)
#define FOR_EACH_60(what, x, ...) what(x) FOR_EACH_59(what, __VA_ARGS__)
#define FOR_EACH_61(what, x, ...) what(x) FOR_EACH_60(what, __VA_ARGS__)
#define FOR_EACH_62(what, x, ...) what(x) FOR_EACH_61(what, __VA_ARGS__)
#define FOR_EACH_63(what, x, ...) what(x) FOR_EACH_62(what, __VA_ARGS__)
#define FOR_EACH_64(what, x, ...) what(x) FOR_EACH_63(what, __VA_ARGS__)
#define FOR_EACH_65(what, x, ...) what(x) FOR_EACH_64(what, __VA_ARGS__)
#define FOR_EACH_66(what, x, ...) what(x) FOR_EACH_65(what, __VA_ARGS__)
#define FOR_EACH_67(what, x, ...) what(x) FOR_EACH_66(what, __VA_ARGS__)
#define FOR_EACH_68(what, x, ...) what(x) FOR_EACH_67(what, __VA_ARGS__)
#define FOR_EACH_69(what, x, ...) what(x) FOR_EACH_68(what, __VA_ARGS__)
#define FOR_EACH_70(what, x, ...) what(x) FOR_EACH_69(what, __VA_ARGS__)
#define FOR_EACH_71(what, x, ...) what(x) FOR_EACH_70(what, __VA_ARGS__)
#define FOR_EACH_72(what, x, ...) what(x) FOR_EACH_71(what, __VA_ARGS__)
#define FOR_EACH_73(what, x, ...) what(x) FOR_EACH_72(what, __VA_ARGS__)
#define FOR_EACH_74(what, x, ...) what(x) FOR_EACH_73(what, __VA_ARGS__)
#define FOR_EACH_75(what, x, ...) what(x) FOR_EACH_74(what, __VA_ARGS__)
#define FOR_EACH_76(what, x, ...) what(x) FOR_EACH_75(what, __VA_ARGS__)
#define FOR_EACH_77(what, x, ...) what(x) FOR_EACH_76(what, __VA_ARGS__)
#define FOR_EACH_78(what, x, ...) what(x) FOR_EACH_77(what, __VA_ARGS__)
#define FOR_EACH_79(what, x, ...) what(x) FOR_EACH_78(what, __VA_ARGS__)
#define FOR_EACH_80(what, x, ...) what(x) FOR_EACH_79(what, __VA_ARGS__)
#define FOR_EACH_81(what, x, ...) what(x) FOR_EACH_80(what, __VA_ARGS__)
#define FOR_EACH_82(what, x, ...) what(x) FOR_EACH_81(what, __VA_ARGS__)
#define FOR_EACH_83(what, x, ...) what(x) FOR_EACH_82(what, __VA_ARGS__)
#define FOR_EACH_84(what, x, ...) what(x) FOR_EACH_83(what, __VA_ARGS__)
#define FOR_EACH_85(what, x, ...) what(x) FOR_EACH_84(what, __VA_ARGS__)
#define FOR_EACH_86(what, x, ...) what(x) FOR_EACH_85(what, __VA_ARGS__)
#define FOR_EACH_87(what, x, ...) what(x) FOR_EACH_86(what, __VA_ARGS__)
#define FOR_EACH_88(what, x, ...) what(x) FOR_EACH_87(what, __VA_ARGS__)
#define FOR_EACH_89(what, x, ...) what(x) FOR_EACH_88(what, __VA_ARGS__)
#define FOR_EACH_90(what, x, ...) what(x) FOR_EACH_89(what, __VA_ARGS__)
#define FOR_EACH_91(what, x, ...) what(x) FOR_EACH_90(what, __VA_ARGS__)
#define FOR_EACH_92(what, x, ...) what(x) FOR_EACH_91(what, __VA_ARGS__)
#define FOR_EACH_93(what, x, ...) what(x) FOR_EACH_92(what, __VA_ARGS__)
#define FOR_EACH_94(what, x, ...) what(x) FOR_EACH_93(what, __VA_ARGS__)
#define FOR_EACH_95(what, x, ...) what(x) FOR_EACH_94(what, __VA_ARGS__)
#define FOR_EACH_96(what, x, ...) what(x) FOR_EACH_95(what, __VA_ARGS__)
#define FOR_EACH_97(what, x, ...) what(x) FOR_EACH_96(what, __VA_ARGS__)
#define FOR_EACH_98(what, x, ...) what(x) FOR_EACH_97(what, __VA_ARGS__)
#define FOR_EACH_99(what, x, ...) what(x) FOR_EACH_98(what, __VA_ARGS__)
#define FOR_EACH_100(what, x, ...) what(x) FOR_EACH_99(what, __VA_ARGS__)

#define GET_MACRO( \
         _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
        _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
        _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
        _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
        _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
        _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
        _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
        NAME, ...) NAME

#define FOR_EACH(action, ...) \
  GET_MACRO(__VA_ARGS__, \
    FOR_EACH_100, FOR_EACH_99, FOR_EACH_98, FOR_EACH_97, FOR_EACH_96, FOR_EACH_95, FOR_EACH_94, FOR_EACH_93, FOR_EACH_92, FOR_EACH_91, \
    FOR_EACH_90, FOR_EACH_89, FOR_EACH_88, FOR_EACH_87, FOR_EACH_86, FOR_EACH_85, FOR_EACH_84, FOR_EACH_83, FOR_EACH_82, FOR_EACH_81, \
    FOR_EACH_80, FOR_EACH_79, FOR_EACH_78, FOR_EACH_77, FOR_EACH_76, FOR_EACH_75, FOR_EACH_74, FOR_EACH_73, FOR_EACH_72, FOR_EACH_71, \
    FOR_EACH_70, FOR_EACH_69, FOR_EACH_68, FOR_EACH_67, FOR_EACH_66, FOR_EACH_65, FOR_EACH_64, FOR_EACH_63, FOR_EACH_62, FOR_EACH_61, \
    FOR_EACH_60, FOR_EACH_59, FOR_EACH_58, FOR_EACH_57, FOR_EACH_56, FOR_EACH_55, FOR_EACH_54, FOR_EACH_53, FOR_EACH_52, FOR_EACH_51, \
    FOR_EACH_50, FOR_EACH_49, FOR_EACH_48, FOR_EACH_47, FOR_EACH_46, FOR_EACH_45, FOR_EACH_44, FOR_EACH_43, FOR_EACH_42, FOR_EACH_41, \
    FOR_EACH_40, FOR_EACH_39, FOR_EACH_38, FOR_EACH_37, FOR_EACH_36, FOR_EACH_35, FOR_EACH_34, FOR_EACH_33, FOR_EACH_32, FOR_EACH_31, \
    FOR_EACH_30, FOR_EACH_29, FOR_EACH_28, FOR_EACH_27, FOR_EACH_26, FOR_EACH_25, FOR_EACH_24, FOR_EACH_23, FOR_EACH_22, FOR_EACH_21, \
    FOR_EACH_20, FOR_EACH_19, FOR_EACH_18, FOR_EACH_17, FOR_EACH_16, FOR_EACH_15, FOR_EACH_14, FOR_EACH_13, FOR_EACH_12, FOR_EACH_11, \
    FOR_EACH_10, FOR_EACH_9, FOR_EACH_8, FOR_EACH_7, FOR_EACH_6, FOR_EACH_5, FOR_EACH_4, FOR_EACH_3, FOR_EACH_2, FOR_EACH_1 \
  )(action, __VA_ARGS__)

#define INTERFACE(name, ...) \
class name { \
	template <class T> \
	struct implemented_by { \
		FOR_EACH(DECL_MEMBER, __VA_ARGS__) \
		static const implemented_by vtable; \
	}; \
	/* The interface “object” holds two pointers */ \
	const implemented_by<Unknown>* const vt; \
	Unknown* const p; \
	const std::type_info &info; \
	public: \
	FOR_EACH(DECL_METHOD, __VA_ARGS__) \
	name(const name &x) : vt(x.vt), p(x.p), info(x.info) {} \
	template <class T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, name>, int> = 0> \
	name(T &x) \
		: vt(reinterpret_cast<const implemented_by<Unknown>*>(&implemented_by<T>::vtable)), \
		p(reinterpret_cast<Unknown*>(&x)), info(typeid(T)) {} \
	template <class T> \
	operator T*() { assert(info == typeid(T)); return reinterpret_cast<T*>(p); } \
	template <class T> \
	operator T&() { assert(info == typeid(T)); return *reinterpret_cast<T*>(p); } \
}; \
template <class T> \
const name::implemented_by<T> name::implemented_by<T>::vtable = { \
	FOR_EACH(INIT_METHOD, __VA_ARGS__) \
};

#define CONST_INTERFACE(name, ...) \
class name { \
	template <class T> \
	struct implemented_by { \
		FOR_EACH(DECL_MEMBER, __VA_ARGS__) \
		static const implemented_by vtable; \
	}; \
	/* The interface “object” holds two pointers */ \
	const implemented_by<Unknown>* const vt; \
	const Unknown* const p; \
	const std::type_info &info; \
	public: \
	FOR_EACH(DECL_METHOD, __VA_ARGS__) \
	name(const name &x) : vt(x.vt), p(x.p), info(x.info) {} \
	template <class T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, name>, int> = 0> \
	name(T &x) \
		: vt(reinterpret_cast<const implemented_by<Unknown>*>(&implemented_by<T>::vtable)), \
		p(reinterpret_cast<const Unknown*>(&x)), info(typeid(T)) {} \
	template <class T> \
	operator const T*() { assert(info == typeid(T)); return reinterpret_cast<const T*>(p); } \
	template <class T> \
	operator const T&() { assert(info == typeid(T)); return *reinterpret_cast<const T*>(p); } \
}; \
template <class T> \
const name::implemented_by<T> name::implemented_by<T>::vtable = { \
	FOR_EACH(INIT_METHOD, __VA_ARGS__) \
};

struct Unknown { };
