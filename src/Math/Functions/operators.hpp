#pragma once

#include <span>

namespace func::oper {

extern double const eps;

double minus (std::span<double> values);

double sum (std::span<double> values);
double diff (std::span<double> values);
double div (std::span<double> values);
double mult (std::span<double> values);

double pow (std::span<double> values);

double eq (std::span<double> values);
double less (std::span<double> values);
double less_or_eq (std::span<double> values);
double greater (std::span<double> values);
double greater_or_eq (std::span<double> values);
double not_oper (std::span<double> values);
double and_oper (std::span<double> values);
double or_oper (std::span<double> values);

double sqrt (std::span<double> values);
double log (std::span<double> values);
double exp (std::span<double> values);

double sin (std::span<double> values);
double cos (std::span<double> values);
double tan (std::span<double> values);
double arcsin (std::span<double> values);
double arccos (std::span<double> values);
double arctan (std::span<double> values);

double abs (std::span<double> values);
double min (std::span<double> values);
double max (std::span<double> values);

double cond (std::span<double> values);

} // namespace func::oper