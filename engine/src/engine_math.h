#pragma once

#define PI 3.14159265359f

#include <DirectXMath.h>
#include <cmath>

namespace Math {

	struct Vector2 {
		Vector2(float x, float y);
		Vector2(float a);
		~Vector2();

		float x;
		float y;

		DirectX::XMVECTOR GetXMVector();

		bool operator==(Vector2 a);
		bool operator!=(Vector2 a);

		Vector2& operator=(float a);

		Vector2 operator+(Vector2 a);
		Vector2& operator+=(Vector2 a);

		Vector2 operator-(Vector2 a);
		Vector2 operator-();
		Vector2& operator-=(Vector2 a);

		Vector2 operator*(float a);
		Vector2& operator*=(float a);

		Vector2 operator/(float a);
		Vector2& operator/=(float a);
	};

	struct Vector3 {
		Vector3(float x, float y, float z);
		Vector3(float a);
		~Vector3();

		float x;
		float y;
		float z;

		DirectX::XMVECTOR GetXMVector();

		bool operator==(Vector3 a);
		bool operator!=(Vector3 a);

		Vector3& operator=(float a);

		Vector3 operator+(Vector3 a);
		Vector3& operator+=(Vector3 a);

		Vector3 operator-(Vector3 a);
		Vector3 operator-();
		Vector3& operator-=(Vector3 a);

		Vector3 operator*(float a);
		Vector3& operator*=(float a);

		Vector3 operator/(float a);
		Vector3& operator/=(float a);
	};

	struct Vector4 {
		Vector4(float x, float y, float z, float w);
		Vector4(float a);
		~Vector4();

		float x;
		float y;
		float z;
		float w;

		DirectX::XMVECTOR GetXMVector();

		bool operator==(Vector4 a);
		bool operator!=(Vector4 a);

		Vector4& operator=(float a);

		Vector4 operator+(Vector4 a);
		Vector4& operator+=(Vector4 a);

		Vector4 operator-(Vector4 a);
		Vector4 operator-();
		Vector4& operator-=(Vector4 a);

		Vector4 operator*(float a);
		Vector4& operator*=(float a);

		Vector4 operator/(float a);
		Vector4& operator/=(float a);
	};

	float Dot(Vector2 a, Vector2 b);
	float Dot(Vector3 a, Vector3 b);
	float Dot(Vector4 a, Vector4 b);

	Vector3 Cross(Vector3 a, Vector3 b);

	float Length(Vector2 v);
	float Length(Vector3 v);
	float Length(Vector4 v);

	Vector2 Normalize(Vector2 v);
	Vector3 Normalize(Vector3 v);
	Vector4 Normalize(Vector4 v);

	float Distance(Vector2 a, Vector2 b);
	float Distance(Vector3 a, Vector3 b);
	float Distance(Vector4 a, Vector4 b);

	Vector2 Reflect(Vector2 I, Vector2 normal);
	Vector3 Reflect(Vector3 I, Vector3 normal);
	Vector4 Reflect(Vector4 I, Vector4 normal);

	float Radians(float degrees);
	float Pi();
}