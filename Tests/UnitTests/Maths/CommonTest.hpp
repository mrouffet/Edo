// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_MATHS_COMMON_TEST_GUARD
#define EDO_MATHS_COMMON_TEST_GUARD

#include <gtest/gtest.h>

#include <edo_maths.hpp>

/// Google Test typedef helper.
#define RadT Rad<TypeParam>
#define DegT Deg<TypeParam>
#define Vec2T Vec2<TypeParam>
#define Vec3T Vec3<TypeParam>
#define Vec4T Vec4<TypeParam>
#define QuatT Quat<TypeParam>
#define Mat3T Mat3<typename TypeParam::T, TypeParam::major>
#define Mat4T Mat4<typename TypeParam::T, TypeParam::major>

#define EXPECT_VEC2_NEAR(_v1, _v2, eps)\
{\
	auto v1V = (_v1);\
	auto v2V = (_v2);\
\
	EXPECT_NEAR(v1V.x, v2V.x, eps);\
	EXPECT_NEAR(v1V.y, v2V.y, eps);\
}

#define EXPECT_VEC3_NEAR(_v1, _v2, eps)\
{\
	auto v1V = (_v1);\
	auto v2V = (_v2);\
\
	EXPECT_NEAR(v1V.x, v2V.x, eps);\
	EXPECT_NEAR(v1V.y, v2V.y, eps);\
	EXPECT_NEAR(v1V.z, v2V.z, eps);\
}

#define EXPECT_VEC4_NEAR(_v1, _v2, eps)\
{\
	auto v1V = (_v1);\
	auto v2V = (_v2);\
\
	EXPECT_NEAR(v1V.x, v2V.x, eps);\
	EXPECT_NEAR(v1V.y, v2V.y, eps);\
	EXPECT_NEAR(v1V.z, v2V.z, eps);\
	EXPECT_NEAR(v1V.w, v2V.w, eps);\
}

#define EXPECT_QUAT_NEAR(_q1, _q2, eps)\
{\
	auto q1V = (_q1);\
	auto q2V = (_q2);\
\
	EXPECT_NEAR(q1V.w, q2V.w, eps);\
	EXPECT_NEAR(q1V.x, q2V.x, eps);\
	EXPECT_NEAR(q1V.y, q2V.y, eps);\
	EXPECT_NEAR(q1V.z, q2V.z, eps);\
}

#define EXPECT_MAT3_NEAR(_m1, _m2, eps)\
{\
	auto m1V = (_m1);\
	auto m2V = (_m2);\
\
	EXPECT_NEAR(m1V.e00, m2V.e00, eps);\
	EXPECT_NEAR(m1V.e01, m2V.e01, eps);\
	EXPECT_NEAR(m1V.e02, m2V.e02, eps);\
	EXPECT_NEAR(m1V.e10, m2V.e10, eps);\
	EXPECT_NEAR(m1V.e11, m2V.e11, eps);\
	EXPECT_NEAR(m1V.e12, m2V.e12, eps);\
	EXPECT_NEAR(m1V.e20, m2V.e20, eps);\
	EXPECT_NEAR(m1V.e21, m2V.e21, eps);\
	EXPECT_NEAR(m1V.e22, m2V.e22, eps);\
}

#define EXPECT_MAT4_NEAR(_m1, _m2, eps)\
{\
	auto m1V = (_m1);\
	auto m2V = (_m2);\
\
	EXPECT_NEAR(m1V.e00, m2V.e00, eps);\
	EXPECT_NEAR(m1V.e01, m2V.e01, eps);\
	EXPECT_NEAR(m1V.e02, m2V.e02, eps);\
	EXPECT_NEAR(m1V.e03, m2V.e03, eps);\
	EXPECT_NEAR(m1V.e10, m2V.e10, eps);\
	EXPECT_NEAR(m1V.e11, m2V.e11, eps);\
	EXPECT_NEAR(m1V.e12, m2V.e12, eps);\
	EXPECT_NEAR(m1V.e13, m2V.e13, eps);\
	EXPECT_NEAR(m1V.e20, m2V.e20, eps);\
	EXPECT_NEAR(m1V.e21, m2V.e21, eps);\
	EXPECT_NEAR(m1V.e22, m2V.e22, eps);\
	EXPECT_NEAR(m1V.e23, m2V.e23, eps);\
	EXPECT_NEAR(m1V.e30, m2V.e30, eps);\
	EXPECT_NEAR(m1V.e31, m2V.e31, eps);\
	EXPECT_NEAR(m1V.e32, m2V.e32, eps);\
	EXPECT_NEAR(m1V.e33, m2V.e33, eps);\
}

namespace edo
{
	/* Must be declared in edo:: */
	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Rad<T>& _r)
	{
		return _os << std::to_string(_r.Handle()) + "_rad";
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Deg<T>& _d)
	{
		return _os << std::to_string(_d.Handle()) + "_deg";
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Vec2<T>& _v)
	{
		return _os << "X: " + std::to_string(_v.x) +
			"\tY: " + std::to_string(_v.y);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Vec3<T>& _v)
	{
		return _os << "X: " + std::to_string(_v.x) +
			"\tY: " + std::to_string(_v.y) +
			"\tZ: " + std::to_string(_v.z);
	}
	
	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Vec4<T>& _v)
	{
		return _os << "X: " + std::to_string(_v.x) +
			"\tY: " + std::to_string(_v.y) +
			"\tZ: " + std::to_string(_v.z) +
			"\tW: " + std::to_string(_v.w);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& _os, const Quat<T>& _q)
	{
		return _os << "W: " + std::to_string(_q.w) +
			"\tX: " + std::to_string(_q.x) +
			"\tY: " + std::to_string(_q.y) +
			"\tZ: " + std::to_string(_q.z);
	}

	template <typename T, MatrixMajor major>
	std::ostream& operator<<(std::ostream& _os, const Mat3<T, major>& _m)
	{
		// Keep memory order (Raw / column major).
		const T* const data = _m.Data();

		return _os <<
			std::to_string(data[0]) + ", " +
			std::to_string(data[1]) + ", " +
			std::to_string(data[2]) + ",\n" +

			std::to_string(data[3]) + "," +
			std::to_string(data[4]) + ", " +
			std::to_string(data[5]) + ",\n" +

			std::to_string(data[6]) + ", " +
			std::to_string(data[7]) + "," +
			std::to_string(data[8]);
	}

	template <typename T, MatrixMajor major>
	std::ostream& operator<<(std::ostream& _os, const Mat4<T, major>& _m)
	{
		// Keep memory order (Raw / column major).
		const T* const data = _m.Data();

		return _os <<
			std::to_string(data[0]) + ", " +
			std::to_string(data[1]) + ", " +
			std::to_string(data[2]) + ", " +
			std::to_string(data[3]) + ",\n" +

			std::to_string(data[4]) + ", " +
			std::to_string(data[5]) + ", " +
			std::to_string(data[6]) + ", " +
			std::to_string(data[7]) + ",\n" +

			std::to_string(data[8]) + ", " +
			std::to_string(data[9]) + ", " +
			std::to_string(data[10]) + ", " +
			std::to_string(data[11]) + ",\n" +

			std::to_string(data[12]) + ", " +
			std::to_string(data[13]) + ", " +
			std::to_string(data[14]) + ", " +
			std::to_string(data[15]);
	}
}

#endif // EDO_MATHS_COMMON_TEST_GUARD
