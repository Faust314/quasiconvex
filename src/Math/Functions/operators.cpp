#include "operators.hpp"

#include <cassert>
#include <cmath>

namespace func::oper {

double const eps = 1e-9;



double minus (std::span<double> values) {
	assert(values.size() == 1);
	return - values[0];
}



double sum (std::span<double> values) {
	assert(values.size() == 2);
	return values[0] + values[1];
}

double diff (std::span<double> values) {
	assert(values.size() == 2);
	return values[0] - values[1];
}

double div (std::span<double> values) {
	assert(values.size() == 2);
	return values[0] / values[1];
}

double mult (std::span<double> values) {
	assert(values.size() == 2);
	return values[0] * values[1];
}



double pow (std::span<double> values) {
	assert(values.size() == 2);
	return std::pow(values[0], values[1]);
}



double eq (std::span<double> values) {
	assert(values.size() == 2);
	return (std::abs(values[0] - values[1]) < eps) ? 1 : -1;
}

double less (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] <= values[1] - eps) ? 1 : -1;
}

double less_or_eq (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] < values[1] + eps) ? 1 : -1;
}

double greater (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] - eps >= values[1]) ? 1 : -1;
}

double greater_or_eq (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] + eps > values[1]) ? 1 : -1;
}

double not_oper (std::span<double> values) {
	assert(values.size() == 1);
	return - values[0];
}

double and_oper (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] > 0 && values[1] > 0) ? 1 : -1;
}

double or_oper (std::span<double> values) {
	assert(values.size() == 2);
	return (values[0] > 0 || values[1] > 0) ? 1 : -1;
}



double sqrt (std::span<double> values) {
	assert(values.size() == 1);
	return std::sqrt(values[0]);
}

double log (std::span<double> values) {
	assert(values.size() == 1);
	return std::log(values[0]);
}

double exp (std::span<double> values) {
	assert(values.size() == 1);
	return std::exp(values[0]);
}



double sin (std::span<double> values) {
	assert(values.size() == 1);
	return std::sin(values[0]);
}

double cos (std::span<double> values) {
	assert(values.size() == 1);
	return std::cos(values[0]);
}

double tan (std::span<double> values) {
	assert(values.size() == 1);
	return std::tan(values[0]);
}

double arcsin (std::span<double> values) {
	assert(values.size() == 1);
	return std::asin(values[0]);
}

double arccos (std::span<double> values) {
	assert(values.size() == 1);
	return std::acos(values[0]);
}

double arctan (std::span<double> values) {
	assert(values.size() == 1);
	return std::atan(values[0]);
}



double abs (std::span<double> values) {
	assert(values.size() == 1);
	return std::abs(values[0]);
}

double min (std::span<double> values) {
	assert(values.size() > 0);
	auto it = values.begin();
	double a = * it;
	for (; it < values.end(); it++) {
		a = std::min(a, * it);
	}
	return a;
}

double max (std::span<double> values) {
	assert(values.size() > 0);
	auto it = values.begin();
	double a = * it;
	for (; it < values.end(); it++) {
		a = std::max(a, * it);
	}
	return a;
}



double cond (std::span<double> values) {
	assert(values.size() == 3);
	return (values[0] > 0) ? values[1] : values[2];
}

} // namespace func::oper
