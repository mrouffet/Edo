// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Vector3
{
	template <typename T>
	class Vector3Test : public testing::Test
	{
	};

	using TestTypes = ::testing::Types<float, double>;
	TYPED_TEST_SUITE(Vector3Test, TestTypes);

	TYPED_TEST(Vector3Test, Constants)
	{
		EXPECT_EQ(Vec3T::Zero.x, 0);
		EXPECT_EQ(Vec3T::Zero.y, 0);
		EXPECT_EQ(Vec3T::Zero.z, 0);

		EXPECT_EQ(Vec3T::One.x, 1);
		EXPECT_EQ(Vec3T::One.y, 1);
		EXPECT_EQ(Vec3T::One.z, 1);

		// X Axis.
		EXPECT_EQ(Vec3T::Right.x, 1);
		EXPECT_EQ(Vec3T::Right.y, 0);
		EXPECT_EQ(Vec3T::Right.z, 0);

		EXPECT_EQ(Vec3T::Left.x, -1);
		EXPECT_EQ(Vec3T::Left.y, 0);
		EXPECT_EQ(Vec3T::Left.z, 0);


		// Y Axis.
		EXPECT_EQ(Vec3T::Up.x, 0);
		EXPECT_EQ(Vec3T::Up.y, 1);
		EXPECT_EQ(Vec3T::Up.z, 0);

		EXPECT_EQ(Vec3T::Down.x, 0);
		EXPECT_EQ(Vec3T::Down.y, -1);
		EXPECT_EQ(Vec3T::Down.z, 0);


		// Z Axis.
		EXPECT_EQ(Vec3T::Forward.x, 0);
		EXPECT_EQ(Vec3T::Forward.y, 0);
		EXPECT_EQ(Vec3T::Forward.z, 1);

		EXPECT_EQ(Vec3T::Backward.x, 0);
		EXPECT_EQ(Vec3T::Backward.y, 0);
		EXPECT_EQ(Vec3T::Backward.z, -1);
	}

	TYPED_TEST(Vector3Test, Constructors)
	{
		// Default constructor.
		const Vec3T v0;
		EXPECT_EQ(v0.x, 0);
		EXPECT_EQ(v0.y, 0);
		EXPECT_EQ(v0.z, 0);


		// Value constructor.
		const TypeParam v1X = TypeParam{ 5.23 };
		const TypeParam v1Y = TypeParam{ 9.487 };
		const TypeParam v1Z = TypeParam{ 63.25 };
		const Vec3T v1(v1X, v1Y, v1Z);

		EXPECT_EQ(v1.x, v1X);
		EXPECT_EQ(v1.y, v1Y);
		EXPECT_EQ(v1.z, v1Z);


		// Scale constructor.
		const TypeParam v2S = TypeParam{ 31.285 };
		const Vec3T v2_scale(v2S);

		EXPECT_EQ(v2_scale.x, v2S);
		EXPECT_EQ(v2_scale.y, v2S);
		EXPECT_EQ(v2_scale.z, v2S);


		// Copy constructor.
		const Vec3T v3(v1);

		EXPECT_EQ(v3.x, v1.x);
		EXPECT_EQ(v3.y, v1.y);
		EXPECT_EQ(v3.z, v1.z);


		// Move constructor.
		Vec3T v4(v3);
		const Vec3T v4m(std::move(v4));

		EXPECT_EQ(v4m.x, v4.x);
		EXPECT_EQ(v4m.y, v4.y);
		EXPECT_EQ(v4m.z, v4.z);


		// Value cast constructor.
		const int32_t v5X = 464;
		const int32_t v5Y = 92;
		const int32_t v5Z = 4;
		const Vec3T v5(Vec3i(v5X, v5Y, v5Z));

		EXPECT_EQ(v5.x, v5X);
		EXPECT_EQ(v5.y, v5Y);
		EXPECT_EQ(v5.z, v5Z);


		// From Vec2.
		const Vec2<TypeParam> v6(TypeParam{ 12.48 }, TypeParam{ 1.2358 });

		const TypeParam v7Z = TypeParam{ 4.26 };
		const Vec3T v7(v6, v7Z);
		EXPECT_EQ(v7.x, v6.x);
		EXPECT_EQ(v7.y, v6.y);
		EXPECT_EQ(v7.z, v7Z);


		// From Vec4.
		const Vec4<TypeParam> v8(TypeParam{ 36.25 }, TypeParam{ 7896.2 }, TypeParam{ 115.21 }, TypeParam{ 99.441 });

		const Vec3T v9(v8);
		EXPECT_EQ(v9.x, v8.x);
		EXPECT_EQ(v9.y, v8.y);
		EXPECT_EQ(v9.z, v8.z);
	}

	TYPED_TEST(Vector3Test, Equals)
	{
		const Vec3T v1(TypeParam{ 56.351 }, TypeParam{ 45.398 }, TypeParam{ 99.25 });
		const Vec3T v2(TypeParam{ 145.87 }, TypeParam{ 51.32 }, TypeParam{ -48.2 });

		EXPECT_FALSE(v1.IsZero());
		EXPECT_TRUE(Vec3T::Zero.IsZero());

		EXPECT_TRUE(v1.Equals(v1));
		EXPECT_FALSE(v1.Equals(v2));

		EXPECT_EQ(v1, v1);
		EXPECT_NE(v1, v2);
	}

	TYPED_TEST(Vector3Test, Accessors)
	{
		const Vec3T v1(TypeParam{ 92.25 }, TypeParam{ 7.26 }, TypeParam{ -66.31 });

		EXPECT_EQ(v1.Data(), &v1.x);
		EXPECT_EQ(const_cast<Vec3T&>(v1).Data(), &v1.x);

		EXPECT_EQ(v1[0], v1.x);
		EXPECT_EQ(v1[1], v1.y);
		EXPECT_EQ(v1[2], v1.z);
	}

	TYPED_TEST(Vector3Test, Length)
	{
		Vec3T v1(TypeParam{ 12.365 }, TypeParam{ 9.155 }, TypeParam{ 22.362 });

		const TypeParam vLenSqr = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
		const TypeParam vLen = std::sqrt(vLenSqr);

		EXPECT_EQ(v1.Length(), vLen);
		EXPECT_EQ(v1.SqrLength(), vLenSqr);

		const Vec3T nV1 = v1.GetNormalized();
		EXPECT_EQ(nV1.x, v1.x / vLen);
		EXPECT_EQ(nV1.y, v1.y / vLen);
		EXPECT_EQ(nV1.z, v1.z / vLen);

		EXPECT_TRUE(nV1.IsNormalized());
		EXPECT_FALSE(v1.IsNormalized());

		EXPECT_NEAR(nV1.Length(), 1.0, std::numeric_limits<TypeParam>::epsilon());

		v1.Normalize();
		EXPECT_EQ(v1, nV1);
	}

	TYPED_TEST(Vector3Test, Projection)
	{
		// Reflect
		const Vec3T v1(1.0f, 1.0f, 1.0f);
		const Vec3T norm(-1.0f, 0.0f, 0.0f);
		const Vec3T refl = Vec3f(-1.0f, 1.0f, 1.0f);
		EXPECT_EQ(v1.Reflect(norm), refl);


		// TODO: Projections.
	}

	TYPED_TEST(Vector3Test, Dot)
	{
		const Vec3T v1(TypeParam{ 5.23 }, TypeParam{ 12.36 }, TypeParam{ -96.31 });
		const Vec3T v2(TypeParam{ 88.25 }, TypeParam{ 94.01 }, TypeParam{ 1.265 });

		const TypeParam dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

		EXPECT_EQ(Vec3T::Dot(v1, v2), dot);
		EXPECT_EQ(v1 | v2, dot);
	}

	TYPED_TEST(Vector3Test, Cross)
	{
		const Vec3T v1(TypeParam{ 5.23 }, TypeParam{ 12.36 }, TypeParam{ -96.31 });
		const Vec3T v2(TypeParam{ 88.25 }, TypeParam{ 94.01 }, TypeParam{ 1.265 });

		const Vec3T vCross(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);

		EXPECT_EQ(Vec3T::Cross(v1, v2), vCross);
		EXPECT_EQ(v1 ^ v2, vCross);
	}

	TYPED_TEST(Vector3Test, Angle)
	{
		const Vec3T v1(TypeParam{ -2.0 }, TypeParam{ 1.0 }, TypeParam{ 0.0f });
		const Vec3T v2(TypeParam{ 1.0 }, TypeParam{ 2.0 }, TypeParam{ 0.0f });

		EXPECT_EQ(Vec3T::Angle(v1, v2, Vec3T::Forward), Deg<TypeParam>(-90.0));
		EXPECT_EQ(Vec3T::AngleUnsigned(v1, v2), Deg<TypeParam>(90.0));
	}

	TYPED_TEST(Vector3Test, Dist)
	{
		const Vec3T v1(TypeParam{ 45.21 }, TypeParam{ -98.25 }, TypeParam{ 22.36 });
		const Vec3T v2(TypeParam{ 9.25 }, TypeParam{ 1.265 }, TypeParam{ 9.265 });

		EXPECT_EQ(Vec3T::Dist(v1, v2), (v1 - v2).Length());
		EXPECT_EQ(Vec3T::SqrDist(v1, v2), (v1 - v2).SqrLength());
	}

	TYPED_TEST(Vector3Test, Dir)
	{
		const Vec3T v1(TypeParam{ -23.65 }, TypeParam{ -11.25 }, TypeParam{ 1.32 });
		const Vec3T v2(TypeParam{ 400.2 }, TypeParam{ -28.82 }, TypeParam{ 44.26 });
		const Vec3T vDir = v2 - v1;

		EXPECT_EQ(Vec3T::Dir(v1, v2), vDir);
		EXPECT_EQ(Vec3T::DirN(v1, v2), vDir.GetNormalized());
	}

	TYPED_TEST(Vector3Test, Lerp)
	{
		const Vec3T v1(TypeParam{ 2.0 }, TypeParam{ 2.0 }, TypeParam{ 0.0f });
		const Vec3T v2(TypeParam{ -2.0 }, TypeParam{ 4.0 }, TypeParam{ 8.0f });

		const Vec3T lerp_res05(TypeParam{ 0.0 }, TypeParam{ 3.0 }, TypeParam{ 4.0 });
		EXPECT_EQ(Vec3T::Lerp(v1, v2, 0.5f), lerp_res05);

		EXPECT_EQ(Vec3T::Lerp(v1, v2, 2.0f), v2);


		const Vec3T ulerp_res1(TypeParam{ 6.0 }, TypeParam{ 0.0 }, TypeParam{ -8.0 });
		EXPECT_EQ(Vec3T::LerpUnclamped(v1, v2, -1.0f), ulerp_res1);
	}

	TYPED_TEST(Vector3Test, SLerp)
	{
		const Vec3T v1(TypeParam{ 2.0 }, TypeParam{ 2.0 }, TypeParam{ 0.0 });
		const Vec3T v2(TypeParam{ -2.0 }, TypeParam{ 2.0 }, TypeParam{ 0.0 });

		const Vec3T slerp = Vec3T::SLerp(v1, v2, 0.5f);
		const Vec3T slerp_res05(TypeParam{ 0.0 }, v1.Length(), TypeParam{ 0.0 });
		
		EXPECT_VEC3_NEAR(slerp, slerp_res05, 0.000001);
	}

	TYPED_TEST(Vector3Test, Operators)
	{
		const Vec3T v1(TypeParam{ 1.25 }, TypeParam{ 100.3 }, TypeParam{ -99.3 });

		const Vec3T mv1(-v1.x, -v1.y, -v1.z);
		EXPECT_EQ(-v1, mv1);

		// Scalar Scale.
		const TypeParam scale = TypeParam{ -45.264 };
		const Vec3T sv1(v1.x * scale, v1.y * scale, v1.z * scale);
		EXPECT_EQ(v1 * scale, sv1);
		EXPECT_EQ(scale * v1, sv1);

		const Vec3T usv1(v1.x / scale, v1.y / scale, v1.z / scale);
		const Vec3T susv1(scale / v1.x, scale / v1.y, scale / v1.z);
		EXPECT_EQ(v1 / scale, usv1);
		EXPECT_EQ(scale / v1, susv1);


		// Vec2 operators.
		const Vec3T v2(TypeParam{ 89.25 }, TypeParam{ -44.25 }, TypeParam{ 17.2 });

		const Vec3T v1pv2(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		EXPECT_EQ(v1 + v2, v1pv2);

		const Vec3T v1mv2(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		EXPECT_EQ(v1 - v2, v1mv2);

		const Vec3T v1mltv2(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
		EXPECT_EQ(v1 * v2, v1mltv2);

		const Vec3T v1dv2(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
		EXPECT_EQ(v1 / v2, v1dv2);


		// op *= scalar.
		Vec3T v3 = v1;
		v3 *= scale;
		EXPECT_EQ(v3, sv1);


		// op /= scalar.
		Vec3T v4 = v1;
		v4 /= scale;
		EXPECT_EQ(v4, usv1);


		// op += Vec2.
		Vec3T v5 = v1;
		v5 += v2;
		EXPECT_EQ(v5, v1pv2);

		// op -= Vec2.
		Vec3T v6 = v1;
		v6 -= v2;
		EXPECT_EQ(v6, v1mv2);


		// op *= Vec2.
		Vec3T v7 = v1;
		v7 *= v2;
		EXPECT_EQ(v7, v1mltv2);


		// op /= Vec2.
		Vec3T v8 = v1;
		v8 /= v2;
		EXPECT_EQ(v8, v1dv2);
	}
}
