#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <set>
#include <cassert>
#include <functional>
#include <list>
#include <memory>
#include <algorithm>

namespace lunatic {
	class RuntimException : public std::runtime_error {
	public:
		using std::runtime_error::runtime_error;
	};

	template<class T>
	struct ScopedAssigenment {
		ScopedAssigenment(T& value) :backup(value), ptr(&value) {	}
		~ScopedAssigenment() {
			*ptr = backup;
		}
	private:
		T* ptr;
		T backup;
	};
}