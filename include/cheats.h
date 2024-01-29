#ifndef CHEATS_H
#define CHEATS_H

// some nastly bypasses to get around numworks linker

#include <cmath>

void _kill_r() {
}

void abort() {
}

void _getpid_r() {
}


namespace __cxxabiv1 {
	class __class_type_info {
	public:
		virtual ~__class_type_info();
	};
	__class_type_info::~__class_type_info() {}
}

namespace std {
	void __throw_out_of_range_fmt(char const*, ...) {
	}

    void __throw_length_error(char const*) {
    }

	void __throw_bad_alloc() {
	}

	void __throw_logic_error(char const*) {
	}
}

void operator delete(void* ptr, unsigned int size) {
	free(ptr);
}

void* operator new(size_t size) {
	return malloc(size);
}
void* operator new[](size_t size) {
	return malloc(size);
}
void operator delete(void* ptr) {
	free(ptr);
}
void operator delete[](void* ptr) {
	free(ptr);
}

#endif