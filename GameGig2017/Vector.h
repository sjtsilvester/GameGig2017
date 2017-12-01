//sfml's vector class, but with typical vector functions (dot product, roation, etc)

#pragma once

#include <SFML/System/Vector2.hpp>
#include "maths.h"
#include <math.h>

namespace sfld {
	template<typename T>
	class Vector2 : public sf::Vector2<T> {
	public:
		Vector2();
		Vector2(T X, T Y);
		Vector2(const sf::Vector2<T>& vector); //intentional implicit conversion
		Vector2<T> rotate(float degrees);
		Vector2<T> rotate(float degrees, const Vector2<T>& origin);
		float dot(const Vector2<T>& other) const;
		Vector2<T> normalise() const;
		float length() const;
		Vector2<T> perpendicular() const;
		Vector2<T> lerp(const Vector2<T>& start, const Vector2<T>& end, float percent) const;
		Vector2<T> negate() const;
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;

	template<typename T>
	Vector2<T>::Vector2() {
		this->x = 0;
		this->y = 0;
	}

	template<typename T>
	Vector2<T>::Vector2(T X, T Y) {
		this->x = X;
		this->y = Y;
	}

	template<typename T>
	Vector2<T>::Vector2(const sf::Vector2<T>& vector) {
		this->x = vector.x;
		this->y = vector.y;
	}

	template<typename T>
	Vector2<T> Vector2<T>::rotate(float degrees) {
		float radians = maths::toRadians(degrees);
		Vector2<T> rotated;
		rotated.x = this->x * cos(radians) + this->y * sin(radians);
		rotated.y = -this->x * sin(radians) + this->y * cos(radians);
		return rotated;
	}

	template<typename T>
	Vector2<T> Vector2<T>::rotate(float degrees, const Vector2<T>& origin) {
		float radians = maths::toRadians(degrees);
		Vector2<T> difference = *this - origin;
		Vector2<T> rotated;
		rotated.x = difference.x * cos(radians) + difference.y * sin(radians);
		rotated.y = -difference.x * sin(radians) + difference.y * cos(radians);
		return rotated;
	}

	template<typename T>
	float Vector2<T>::dot(const Vector2<T>& other) const {
		return (this->x * other.x) + (this->y * other.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::normalise() const {
		float len = length();
		if (len == 0) return Vector2<T>(0, 0);
		return Vector2<T>(this->x / len, this->y / len);
	}

	template<typename T>
	float Vector2<T>::length() const {
		return sqrt(this->x*this->x + this->y*this->y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::perpendicular() const {
		return Vector2<T>(-this->y, this->x);
	}

	template<typename T>
	Vector2<T> Vector2<T>::lerp(const Vector2<T>& start, const Vector2<T>& end, float percent) const {
		return start + percent*(end - start);
	}

	template<typename T>
	Vector2<T> Vector2<T>::negate() const {
		return Vector2<T>(-this->x, -this->y);
	}
}