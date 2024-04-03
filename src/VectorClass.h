#pragma once
#include <numbers>
#include <cmath>

struct Vector3
{
	// constructor
	Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	// operator overloads
	const Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	const Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}

	const Vector3 operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor, y / factor, z / factor };
	}

	const Vector3 operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor, y * factor, z * factor };
	}

	const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	// struct data
	float x, y, z;
};

struct Vector2
{
	// constructor
	Vector2(
		const float x = 0.f,
		const float y = 0.f) noexcept :
		x(x), y(y) { }

	// operator overloads
	const Vector2 operator-(const Vector2& other) const noexcept
	{
		return Vector2{ x - other.x, y - other.y};
	}

	const Vector2 operator+(const Vector2& other) const noexcept
	{
		return Vector2{ x + other.x, y + other.y};
	}

	const Vector2 operator/(const float factor) const noexcept
	{
		return Vector2{ x / factor, y / factor};
	}

	const Vector2 operator*(const float factor) const noexcept
	{
		return Vector2{ x * factor, y * factor};
	}

	const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f;
	}

	// struct data
	float x, y;
};