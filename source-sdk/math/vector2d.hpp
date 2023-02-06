#pragma once

#include "vector3d.hpp"
class vec2_t {
public:
	float x, y;

	vec2_t() {
		x = 0; y = 0;
	};
	vec2_t(float _x, float _y) {
		x = _x; y = _y;
	};
	vec2_t(vec3_t vec) {
		x = vec.x; y = vec.y;
	}

	inline vec2_t operator*(const float n) const {
		return vec2_t(x * n, y * n);
	}
	inline vec2_t operator+(const vec2_t& v) const {
		return vec2_t(x + v.x, y + v.y);
	}
	inline vec2_t operator-(const vec2_t & v) const {
		return vec2_t(x - v.x, y - v.y);
	}
	inline void operator+=(const vec2_t & v) {
		x += v.x;
		y += v.y;
	}
	inline void operator-=(const vec2_t & v) {
		x -= v.x;
		y -= v.y;
	}

	bool operator==(const vec2_t & v) const {
		return (v.x == x && v.y == y);
	}
	bool operator!=(const vec2_t & v) const {
		return (v.x != x || v.y != y);
	}

	inline float length() {
		return sqrt((x * x) + (y * y));
	}
};
struct selections {
	const char* a; const char* b; const char* c; const char* d; const char* e; const char* f; const char* g;
	const char* deref(int pointer) {
		if (pointer == 0) {
			return a;
		}
		else if (pointer == 1) {
			return b;
		}
		else if (pointer == 2) {
			return c;
		}
		else if (pointer == 3) {
			return d;
		}
		else if (pointer == 4) {
			return e;
		}
		else if (pointer == 5) {
			return f;
		}
		else if (pointer == 6) {
			return g;
		}
	}
	bool valid(const char* c_arg) {
		if (c_arg == "x") {
			return false;
		}
		else {
			return true;
		}
	}
};
struct selected {
	bool a, b, c, d, e, f, g;
	void select(int pointer) {
		if (pointer == 0) {
			a = !a;
		}
		else if (pointer == 1) {
			b = !b;
		}
		else if (pointer == 2) {
			c = !c;
		}
		else if (pointer == 3) {
			d = !d;
		}
		else if (pointer == 4) {
			e = !e;
		}
		else if (pointer == 5) {
			f = !f;
		}
		else if (pointer == 6) {
			g = !g;
		}
	}
	bool deref(int pointer) {
		if (pointer == 0) {
			return a;
		}
		else if (pointer == 1) {
			return b;
		}
		else if (pointer == 2) {
			return c;
		}
		else if (pointer == 3) {
			return d;
		}
		else if (pointer == 4) {
			return e;
		}
		else if (pointer == 5) {
			return f;
		}
		else if (pointer == 6) {
			return g;
		}
	}
};