#pragma once

#include "pointer.hpp"

namespace aux::str {

template <typename T, int ID>
T * Pointer<T, ID>::_pointer = nullptr;

template <typename T, int ID>
bool Pointer<T, ID>::is_nullptr () {
	return _pointer = nullptr;
}

template <typename T, int ID>
T * Pointer<T, ID>::pointer () {
	return _pointer;
}

template <typename T, int ID>
T & Pointer<T, ID>::obj () {
	return * _pointer;
}

template <typename T, int ID>
void Pointer<T, ID>::reset () {
	_pointer = nullptr;
}

template <typename T, int ID>
void Pointer<T, ID>::set_pointer (T & obj) {
	_pointer = & obj;
}

} // namespace aux::str
