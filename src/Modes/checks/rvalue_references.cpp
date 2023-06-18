#include "../check.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace modes::test {

class A {
public:
	std::string x;
	std::vector<std::string> lines;
	A() : x("1") {std::cout << "A()\n";}
	A(A const & a) : x("2") {std::cout << "A(A& a)\n";}
	A(A const && a) : x("3") {std::cout << "A(A&& a)\n";}
	
	A& operator= (const A& a) {
		x = a.x;
		lines = a.lines;
		std::cout << "= A&\n";
		return *this;
	}
	
	A& operator = (A&& a)  noexcept {
		x = a.x;
		lines = a.lines;
		std::cout << "= A&&\n";
		return *this;
	}
};

A f () {
	A a;
	return a;
}

struct B {
	std::vector<A> v;
	void insert (A && a) {
		v.push_back(std::move(a));
	}
};

void rvalue_references() {
	
	std::vector<A> v;
//	v.push_back(f());
	
	
	B b;
	b.insert(f());
	
}

} // namespace modes::test
