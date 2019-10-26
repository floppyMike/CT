#include <iostream>

#include <CustomLibrary/Traits.h>

template<template<typename> class... Func>
class Foo : public Func<Foo<Func...>>...
{
public:
	Foo() = default;

	template<template<typename> class... Func>
	Foo(const Foo<Func...>& o)
		: m_a(o.get())
	{
	}

	auto get() const { return m_a; }
	void set(int a) { m_a = a; }

private:
	int m_a = 0;
};


template<typename T>
class Incre10 : public ctl::crtp<T, Incre10>
{
public:
	void increment()
	{
		this->_().set(this->_().get() + 10);
	}
};


template<typename T>
class Incre20 : public ctl::crtp<T, Incre20>
{
public:
	void incrementBy20()
	{
		this->_().set(this->_().get() + 20);
	}
};


int main()
{
	Foo<> a;
	Foo<Incre10> b;
	b.increment();

	Foo<Incre10, Incre20> c;
	c.increment();

	b = a;

	std::cout << b.get() << '\n';

	return 0;
}