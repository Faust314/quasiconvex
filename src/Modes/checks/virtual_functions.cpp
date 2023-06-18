#include "../check.hpp"

#include <iostream>

namespace modes::test::virtual_functions {

struct A {
	void f() { std::cout << "A::f"; }
	virtual void g();
};

struct B : public A {
	void g() { std::cout << "B::f"; }
};

void main() {
	B b;
	A* a = &b;
	a->g();
}

} // namespace modes::test
