#pragma once

template<class T>
inline void Reset(T*& p, const size_t& index = 1) {
	if (index == 1) {
		delete p;
		p = new T;
	}
	else {
		delete[] p;
		p = new T[index];
	}
}