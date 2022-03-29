#pragma once

#include <SFML/Graphics.hpp>

/**
*This template class is a wrapper for the sf::Vector2.
*
*This class extends sf::Vector2's functionality
*by implementing typical vector operations such as
*vector sums, multiplying vector by scalar, normalization of vector,
vector dot product or limiting a vector to some max magnitude.
*/
template <class T>
class Vector : public sf::Vector2<T>
{

public:
	
	Vector<T>() {
		this->x = 0;
		this->y = 0;
	}

	Vector<T>(T x, T y) {
		this->x = x;
		this->y = y;
	}

	Vector<T>(sf::Vector2<T> copy) {
		this->x = copy.x;
		this->y = copy.y;
	}

	template <typename T>
	Vector<T>& operator =(const Vector<T>& right) {
		this->x = right.x;
		this->y = right.y;

		return *this;
	}

	Vector<T>& operator =(const sf::Vector2<T>& right) {
		this->x = right.x;
		this->y = right.y;

		return *this;
	}
	
	template <typename T>
	Vector<T>& operator +=(const Vector<T>& right) {
		this->x += right.x;
		this->y += right.y;

		return *this;
	}

	template <typename T>
	Vector<T>& operator -=(const Vector<T>& right) {
		this->x += right.x;
		this->y -= right.y;

		return *this;
	}

	template <typename T>
	Vector<T> operator +(const Vector<T>& right) {
		return Vector<T>(this.x + right.x, this.y + right.y);
	}
	
	template <typename T>
	Vector<T> operator -(const Vector<T>& right) {
		return Vector<T>(this->x - right.x, this->y - right.y);
	}

	
	template <typename T>
	Vector<T> operator *(T right) {
		return Vector<T>(this->x * right, this->y * right);
	}

	
	template <typename T>
	Vector<T>& operator *=(T right) {
		this->x *= right;
		this->y *= right;

		return *this;
	}

	
	template <typename T>
	Vector<T> operator /(T right) {
		return Vector<T>(this->x / right, this->y / right);
	}

	
	template <typename T>
	Vector<T>& operator /=(T right) {
		this->x /= right;
		this->y /= right;
		
		return *this;
	}

	
	template <typename T>
	bool operator ==(const Vector<T>& right) {
		return (this->x == right.x) && (this->y == right.y);
	}

	
	template <typename T>
	bool operator !=(const Vector<T>& right) {
		return (this->x != right.x) || (this->y != right.y);
	}
	
	float GetMagnitude() {
		return std::sqrtf(std::powf(this->x, 2) + std::powf(this->y, 2));
	}

	Vector<T> GetNormalized() {
		float mag = this->GetMagnitude();
		return mag == 0 ? Vector<T>(0, 0) : *this / mag;
	}

	void Normalize() {
		float mag = this->GetMagnitude();
		*this = mag == 0 ? Vector<T>(0, 0) : *this / mag;
	}

	void Limit(T maxMagnitude) {
		if (this->GetMagnitude() > maxMagnitude)
			*this = this->GetNormalized() * maxMagnitude;
	}

	float Dot(const Vector& vec2) const {
		return this->x * vec2.x + this->y * vec2.y;
	}

};