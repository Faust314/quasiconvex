#include "func.hpp"

#include "operators.hpp"
#include "../../Utils/Basic/type_utils.hpp"

#include <vector>
#include <numbers>
#include <cassert>

namespace func {

void Func::init (std::string const & formula, std::vector<std::string> const & variables) {
	for (token_id_t var_id = 0; var_id < variables.size(); var_id++) {
		var_ids[variables[var_id]] = var_id;
	}
	
	std::vector<std::string> items = split_formula(formula);
	for (token_id_t token_id = 0; token_id < items.size(); token_id++) {
		if (
			items[token_id] == "-" &&
			(token_id == 0 || items[token_id - 1] == "(")
		) {
			items[token_id] = "_";
		}
	}
	
	for (const auto & item : items) {
		if (item == left_brace) {
			add_left_brace();
		} else if (item == right_brace) {
			add_right_brace();
		} else if (item == comma) {
			add_comma();
		} else if (var_ids.contains(item)) {
			add_variable(var_ids[item]);
		} else if (constants.contains(item)) {
			add_value(constants.find(item)->second);
		} else if (functions.contains(item)) {
			add_function(functions.find(item)->second);
		} else if (unary.contains(item)) {
			add_oper(unary.find(item)->second, 1);
		} else if (binary.contains(item)) {
			add_oper(binary.find(item)->second, 2);
		} else if (ternary_first.contains(item)) {
			add_oper(ternary_first.find(item)->second, -1);
		} else if (ternary_second.contains(item)) {
			add_oper(ternary_second.find(item)->second, 3);
		} else {
			assert(aux::types::is_real(item));
			add_value(std::stod(item));
		}
	}
	
	while (! tokens_stack.empty()) {
		assert(
			tokens_stack.top().token_kind != token_kind_t::left_brace &&
			tokens_stack.top().token_kind != token_kind_t::right_brace &&
			tokens_stack.top().token_kind != token_kind_t::comma
		);
		tokens.push_back(tokens_stack.top());
		tokens_stack.pop();
	}
	
	std::vector<Operator> new_tokens;
	
	token_id_t commas = 0;
	for (auto & token : tokens) {
		if (token.token_kind == token_kind_t::comma) {
			commas++;
		} else if (token.token_kind == token_kind_t::oper && token.number == -1) {
			continue;
		} else if (token.token_kind != token_kind_t::function) {
			new_tokens.push_back(token);
		} else {
			new_tokens.emplace_back(
				token_kind_t::oper,
				token.sign,
				commas + 1
			);
			commas = 0;
		}
	}
	tokens = std::move(new_tokens);
}

Func::Func (std::string const & formula, std::vector<std::string> const & variables) {
	init (formula, variables);
}



double Func::operator() (std::vector<double> const & values) const {
	std::vector<double> items;
	for (const auto & token : tokens) {
		switch (token.token_kind) {
			case token_kind_t::value:
				items.push_back(token.value);
				break;
			case token_kind_t::variable:
				items.push_back(values[token.number]);
				break;
			default:
				assert(items.size() >= token.number);
				double res = token.sign.oper({items.end() - token.number, items.end()});
				items.resize(items.size() + 1 - token.number);
				items.back() = res;
		}
	}
	assert(items.size() == 1);
	return items.back();
}



std::vector<std::string> Func::split_formula (std::string const & formula) {
	std::vector<std::string> items(1);
	bool add_special;
	for (token_id_t i = 0; i < formula.size();) {
		if (formula[i] == ' ' || formula[i] == '\n') {
			if (! items.back().empty()) {
				items.emplace_back();
			}
			i++;
			continue;
		}
		add_special = false;
		for (std::string const & s : special) {
			if (
				i + s.size() <= formula.size() &&
				formula.substr(i, s.size()) == s
			) {
				if (items.back().empty()) {
					items.back() = s;
				} else {
					items.push_back(s);
				}
				items.emplace_back();
				i += s.size();
				add_special = true;
				break;
			}
		}
		if (add_special) {
			continue;
		}
		items.back().push_back(formula[i]);
		i++;
	}
	if (items.back().empty()) {
		items.pop_back();
	}
	
	return items;
}



void Func::add_left_brace () {
	tokens_stack.emplace(
		token_kind_t::left_brace
	);
}

void Func::add_right_brace () {
	assert(! tokens_stack.empty());
	while (
		tokens_stack.top().token_kind != token_kind_t::left_brace
	) {
		tokens.push_back(tokens_stack.top());
		tokens_stack.pop();
		assert(! tokens_stack.empty());
	}
	tokens_stack.pop();
}

void Func::add_comma () {
	assert(! tokens_stack.empty());
	while (
		tokens_stack.top().token_kind != token_kind_t::left_brace
	) {
		tokens.push_back(tokens_stack.top());
		tokens_stack.pop();
		assert(! tokens_stack.empty());
	}
	tokens.emplace_back(
		token_kind_t::comma,
		Sign()
	);
}

void Func::add_variable (token_id_t var_id) {
	tokens.emplace_back(
		token_kind_t::variable,
		Sign(),
		var_id
	);
}

void Func::add_value (double value) {
	tokens.emplace_back(
		token_kind_t::value,
		Sign(),
		0,
		value
	);
}

void Func::add_function (Func::Sign const & sign) {
	tokens_stack.emplace(
		token_kind_t::function,
		sign
	);
}

void Func::add_oper (Sign const & sign, token_id_t args_number) {
	while (
		! tokens_stack.empty() &&
		tokens_stack.top().token_kind != token_kind_t::left_brace &&
		tokens_stack.top().sign.priority <= sign.priority
	) {
		tokens.push_back(tokens_stack.top());
		tokens_stack.pop();
	}
	tokens_stack.emplace(
		token_kind_t::oper,
		sign,
		args_number
	);
}
	
} // namespace func
