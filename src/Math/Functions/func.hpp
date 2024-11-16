#pragma once

#include <string>
#include <stack>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <span>

namespace func {

class Func {
public:
	enum class token_kind_t {left_brace, right_brace, comma, variable, value, oper, function};
	typedef int16_t token_id_t;
	
	struct Sign {
		double (* oper) (std::span<double> values) = nullptr;
		token_id_t priority = 0;
		std::string name;
	};
	
	struct Operator {
		token_kind_t token_kind = token_kind_t::variable;
		Sign sign = Sign();
		token_id_t number = 0;
		double value = 0;
	};
	
public:
	Func () = default;
	void init (std::string const & formula, std::vector<std::string> const & variables);
	Func (std::string const & formula, std::vector<std::string> const & variables);
	
	double operator() (std::vector<double> const & values) const;
	
private:
	static std::string const left_brace;
	static std::string const right_brace;
	static std::string const comma;
	
	static std::unordered_map<std::string, double> const constants;
	static std::unordered_map<std::string, Sign> const functions;
	static std::unordered_map<std::string, Sign> const unary;
	static std::unordered_map<std::string, Sign> const binary;
	static std::unordered_map<std::string, Sign> const ternary_first;
	static std::unordered_map<std::string, Sign> const ternary_second;
	
	static std::vector<std::string> const special;
	
	std::unordered_map<std::string, token_id_t> var_ids;
	
	std::stack<Operator> tokens_stack;
	std::vector<Operator> tokens;
	
	static std::vector<std::string> split_formula (std::string const & formula);
	
	void add_left_brace ();
	void add_right_brace ();
	void add_comma ();
	void add_variable (token_id_t var_id);
	void add_value (double value);
	void add_function (Sign const & sign);
	void add_oper (Sign const & sign, token_id_t args_number);
};

} // namespace func

