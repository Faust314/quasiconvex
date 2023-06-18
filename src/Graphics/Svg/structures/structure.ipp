#include <cassert>

namespace graphics::svg::object::str {

template <class F>
void function(
	File::Layer & layer,
	F f,
	::graphics::svg::object::basic::Point origin,
	int n,
	int m,
	double delta,
	Stroke const & stroke
) {
	::graphics::svg::object::basic::Origin p(origin);
	assert(n < m);
	for (int x = n; x < m; x++) {
		layer.add_object(
			::graphics::svg::object::basic::line(
				p(x * delta, f(x)),
				p((x + 1) * delta, f(x + 1)),
				stroke
			)
		);
	}
}

} // namespace graphics::svg::object::str
