#include "func.hpp"

#include "../../../Array/Basic/basic.tpp"
#include "../../../Math/Geometry/Stereometry/threedim_point.tpp"

namespace graphics::threedim::str {


bool Func::FuncPoint::is_empty () const {
	return _value == _empty;
}

void Func::FuncPoint::clear () {
	_value = _empty;
}

color::RGB & Func::FuncPoint::color () {
	return _color;
}

coord_t & Func::FuncPoint::value () {
	return _value;
}



void Func::init (Func::ArrayPoint const & a, Func::ArrayPoint const & b) {
	_func_points.init(a, b);
}

Func::Func (Func::ArrayPoint const & a, Func::ArrayPoint const & b) :
	_func_points(a, b)
{}

array::Basic<Func::FuncPoint, 2> & Func::func_points () {
	return _func_points;
}

void Func::output (Model & model, math::geom::multi::Point<coord_t, 2> a, math::geom::multi::Point<coord_t, 2> b) {
	// TODO сделать вывод более оптимальным
	coord_t x_k = (b[0] - a[0]) / (_func_points.b()[0] - _func_points.a()[0]);
	coord_t x_0 = -_func_points.a()[0] * x_k + a[0];
	coord_t y_k = (b[1] - a[1]) / (_func_points.b()[1] - _func_points.a()[1]);
	coord_t y_0 = -_func_points.a()[1] * y_k + a[1];
	
	coord_t V[3][3];
	coord_t X[3];
	coord_t Y[3];
	
	for (array_coord_t x = _func_points.a()[0]; x < _func_points.b()[0]; x++) {
		for (array_coord_t y = _func_points.a()[1]; y < _func_points.b()[1]; y++) {
			if (
				_func_points({x    , y    }).is_empty() ||
				_func_points({x + 1, y    }).is_empty() ||
				_func_points({x    , y + 1}).is_empty() ||
				_func_points({x + 1, y + 1}).is_empty()
			) {
				continue;
			}
			
			V[0][0] = _func_points({x, y}).value();
			V[0][2] = _func_points({x + 1, y}).value();
			V[2][0] = _func_points({x, y + 1}).value();
			V[2][2] = _func_points({x + 1, y + 1}).value();
			
			V[0][1] = (V[0][0] + V[0][2]) / 2;
			V[2][1] = (V[2][0] + V[2][2]) / 2;
			V[1][0] = (V[0][0] + V[2][0]) / 2;
			V[1][2] = (V[0][2] + V[2][2]) / 2;
			
			V[1][1] = (V[0][1] + V[2][1]) / 2;
			
			X[0] = x_0 + x_k * x;
			X[1] = x_0 + x_k * (x + 0.5);
			X[2] = x_0 + x_k * (x + 1);
			
			Y[0] = y_0 + y_k * y;
			Y[1] = y_0 + y_k * (y + 0.5);
			Y[2] = y_0 + y_k * (y + 1);
			
			model.add_color(_func_points({x, y}).color());
			model.add_face({
				{X[0], Y[0], V[0][0]},
				{X[1], Y[0], V[0][1]},
				{X[1], Y[1], V[1][1]},
				{X[0], Y[1], V[1][0]}
			});
			model.add_color(_func_points({x + 1, y}).color());
			model.add_face({
				{X[1], Y[0], V[0][1]},
				{X[2], Y[0], V[0][2]},
				{X[2], Y[1], V[1][2]},
				{X[1], Y[1], V[1][1]}
			});
			model.add_color(_func_points({x, y + 1}).color());
			model.add_face({
				{X[0], Y[1], V[1][0]},
				{X[1], Y[1], V[1][1]},
				{X[1], Y[2], V[2][1]},
				{X[0], Y[2], V[2][0]}
			});
			model.add_color(_func_points({x + 1, y + 1}).color());
			model.add_face({
				{X[1], Y[1], V[1][1]},
				{X[2], Y[1], V[1][2]},
				{X[2], Y[2], V[2][2]},
				{X[1], Y[2], V[2][1]}
			});
		}
	}
}

} // namespace graphics::threedim::str
