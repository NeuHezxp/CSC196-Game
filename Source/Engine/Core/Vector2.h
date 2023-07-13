#pragma once
#include <cmath>
#include <istream>
#include <sstream>

namespace kiko
{
	class Vector2
	{
	public:
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {}




		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }

		//for floats
		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }

		// ?= operators
		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); };
		float length() const { return std::sqrt(LengthSqr()); }

		float DistanceSqr(const Vector2& v) { return (v - *this).LengthSqr(); }
		float Distance(const Vector2& v) { return sqrt(LengthSqr()); }


		Vector2 Normalized()const {return *this / length(); } /// becomes 1.0 when normalized
		void Normalize() { *this /= length(); }

		float Angle() const { return std::atan2f(y, x); }
		Vector2 Rotate(float radians) const;

	private:
	};
	inline Vector2 Vector2::Rotate(float radians) const
	{
		float _x  = x * std::cos(radians) - y * std::sin(radians);
		float _y  = x * std::sin(radians) + y * std::cos(radians); //MATH!!
		return { _x,_y };
	}


	inline 	std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);
		// { ##, ## }
	//gets a substring for the numbers in-between the brackets for the numbers
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);
		return stream;
	}

	using vec2 = Vector2;
}
