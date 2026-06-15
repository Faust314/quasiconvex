#include "func.hpp"

#include "operators.hpp"

#include <numbers>

namespace func {

std::string const Func::left_brace = "(";
std::string const Func::right_brace = ")";
std::string const Func::comma = ",";

std::unordered_map<std::string, double> const Func::constants = {
	{"e", std::numbers::e},
	{"pi", std::numbers::pi}
};
std::unordered_map<std::string, Func::Sign> const Func::functions = {
	{"sqrt", {oper::sqrt, 0, "sqrt"}},
	{"exp", {oper::exp, 0, "exp"}},
	{"log", {oper::log, 0, "log"}},
	{"sin", {oper::sin, 0, "sin"}},
	{"cos", {oper::cos, 0, "cos"}},
	{"tan", {oper::tan, 0, "tan"}},
	{"arcsin", {oper::arcsin, 0, "arcsin"}},
	{"arccos", {oper::arccos, 0, "arccos"}},
	{"arctan", {oper::arctan, 0, "arctan"}},
	{"abs", {oper::abs, 0, "abs"}},
	{"min", {oper::min, 0, "min"}},
	{"max", {oper::max, 0, "max"}}
};
std::unordered_map<std::string, Func::Sign> const Func::unary = {
	{"_", {oper::minus, 4, "_"}},
	{"not", {oper::diff, 6, "not"}},
};
std::unordered_map<std::string, Func::Sign> const Func::binary = {
	{"^", {oper::pow, 1, "^"}},
	{"*", {oper::mult, 2, "*"}},
	{"/", {oper::div, 2, "/"}},
	{"+", {oper::sum, 3, "+"}},
	{"-", {oper::diff, 3, "-"}},
	{"=", {oper::eq, 5, "="}},
	{"<", {oper::less, 5, "<"}},
	{"<=", {oper::less_or_eq, 5, "<="}},
	{">", {oper::greater, 5, ">"}},
	{">=", {oper::greater_or_eq, 5, ">="}},
	{"and", {oper::and_oper, 7, "and"}},
	{"or", {oper::or_oper, 7, "or"}}
};
std::unordered_map<std::string, Func::Sign> const Func::ternary_first = {
	{"?", {oper::cond, 8, "?"}}
};
std::unordered_map<std::string, Func::Sign> const Func::ternary_second = {
	{":", {oper::cond, 8, ":"}}
};

std::vector<std::string> const Func::special = {
	"(", ")", ",", "^", "*", "/", "+", "-", "=", "<=", "<", ">=", ">", "?", ":",
};

	
} // namespace func
