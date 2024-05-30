#pragma once

namespace aux::str {

template <typename T, int ID = 0>
class Pointer {
public:
	static bool is_nullptr ();
	static T * pointer ();
	static T & obj ();
	
	static void reset ();
	static void set_pointer (T & obj);
	
private:
	static T * _pointer;
};	
	
} // namespace aux::str