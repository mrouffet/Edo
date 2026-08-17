// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Vector4
{
	template <typename T>
	class Vector4Test : public testing::Test
	{
	};

	using TestTypes = ::testing::Types<float, double>;
	TYPED_TEST_SUITE(Vector4Test, TestTypes);

	TYPED_TEST(Vector4Test, Constructors)
	{
		// Default constructor.
		const Vec4T v0;
		EXPECT_EQ(v0.x, 0);
		EXPECT_EQ(v0.y, 0);
		EXPECT_EQ(v0.z, 0);
		EXPECT_EQ(v0.w, 0);


		// Value constructor.
		const TypeParam v1X = TypeParam{ 5.23 };
		const TypeParam v1Y = TypeParam{ 9.487 };
		const TypeParam v1Z = TypeParam{ 63.25 };
		const TypeParam v1W = TypeParam{ 99.21 };
		const Vec4T v1(v1X, v1Y, v1Z, v1W);

		EXPECT_EQ(v1.x, v1X);
		EXPECT_EQ(v1.y, v1Y);
		EXPECT_EQ(v1.z, v1Z);
		EXPECT_EQ(v1.w, v1W);


		// Scale constructor.
		const TypeParam v2S = TypeParam{ 31.285 };
		const Vec4T v2_scale(v2S);

		EXPECT_EQ(v2_scale.x, v2S);
		EXPECT_EQ(v2_scale.y, v2S);
		EXPECT_EQ(v2_scale.z, v2S);
		EXPECT_EQ(v2_scale.w, v2S);


		// Copy constructor.
		const Vec4T v3(v1);

		EXPECT_EQ(v3.x, v1.x);
		EXPECT_EQ(v3.y, v1.y);
		EXPECT_EQ(v3.z, v1.z);
		EXPECT_EQ(v3.w, v1.w);


		// Move constructor.
		Vec4T v4(v3);
		const Vec4T v4m(std::move(v4));

		EXPECT_EQ(v4m.x, v4.x);
		EXPECT_EQ(v4m.y, v4.y);
		EXPECT_EQ(v4m.z, v4.z);
		EXPECT_EQ(v4m.w, v4.w);


		// Value cast constructor.
		const int32_t v5X = 464;
		const int32_t v5Y = 92;
		const int32_t v5Z = 4;
		const int32_t v5W = 89;
		const Vec4T v5(Vec4i(v5X, v5Y, v5Z, v5W));

		EXPECT_EQ(v5.x, v5X);
		EXPECT_EQ(v5.y, v5Y);
		EXPECT_EQ(v5.z, v5Z);
		EXPECT_EQ(v5.w, v5W);


		// From Vec2.
		const Vec2<TypeParam> v6(TypeParam{ 12.48 }, TypeParam{ 1.2358 });

		const TypeParam v7Z = TypeParam{ 4.26 };
		const TypeParam v7W = TypeParam{ 6.324 };
		const Vec4T v7(v6, v7Z, v7W);
		EXPECT_EQ(v7.x, v6.x);
		EXPECT_EQ(v7.y, v6.y);
		EXPECT_EQ(v7.z, v7Z);
		EXPECT_EQ(v7.w, v7W);


		// From 2 Vec2.
		const Vec2<TypeParam> v8(TypeParam{ 3.221 }, TypeParam{ 896.3 });
		const Vec4T v9(v6, v8);
		EXPECT_EQ(v9.x, v6.x);
		EXPECT_EQ(v9.y, v6.y);
		EXPECT_EQ(v9.z, v8.x);
		EXPECT_EQ(v9.w, v8.y);


		// From Vec3.
		const Vec3<TypeParam> v10(TypeParam{ 996.32 }, TypeParam{ 23.21 }, TypeParam{ 1.236 });

		const TypeParam v10W = TypeParam{ 7.154 };
		const Vec4T v11(v10, v10W);
		EXPECT_EQ(v11.x, v10.x);
		EXPECT_EQ(v11.y, v10.y);
		EXPECT_EQ(v11.z, v10.z);
		EXPECT_EQ(v11.w, v10W);
	}

	TYPED_TEST(Vector4Test, Equals)
	{
		const Vec4T v1(TypeParam{ 56.351 }, TypeParam{ 45.398 }, TypeParam{ 99.25 }, TypeParam{ -63.14 });
		const Vec4T v2(TypeParam{ 145.87 }, TypeParam{ 51.32 }, TypeParam{ -48.2 }, TypeParam{ 10.32 });

		EXPECT_FALSE(v1.IsZero());
		EXPECT_TRUE(Vec4T().IsZero());
		//EXPECT_TRUE(Vec4f::Zero.IsZero());

		EXPECT_TRUE(v1.Equals(v1));
		EXPECT_FALSE(v1.Equals(v2));

		EXPECT_EQ(v1, v1);
		EXPECT_NE(v1, v2);
	}

	TYPED_TEST(Vector4Test, Accessors)
	{
		const Vec4T v1(TypeParam{ 92.25 }, TypeParam{ 7.26 }, TypeParam{ -66.31 }, TypeParam{ 3.21 });

		EXPECT_EQ(v1[0], v1.x);
		EXPECT_EQ(v1[1], v1.y);
		EXPECT_EQ(v1[2], v1.z);
		EXPECT_EQ(v1[3], v1.w);

		EXPECT_EQ(v1.Data(), &v1.x);
		EXPECT_EQ(const_cast<Vec4T&>(v1).Data(), &v1.x);
	}

	TYPED_TEST(Vector4Test, Operators)
	{
		const Vec4T v1(TypeParam{ 1.25 }, TypeParam{ 100.3 }, TypeParam{ -99.3 }, TypeParam{ 67.67 });

		const Vec4T mv1(-v1.x, -v1.y, -v1.z, -v1.w);
		EXPECT_EQ(-v1, mv1);

		// Scalar Scale.
		const TypeParam scale = TypeParam{ -45.264 };
		const Vec4T sv1(v1.x * scale, v1.y * scale, v1.z * scale, v1.w * scale);
		EXPECT_EQ(v1 * scale, sv1);
		EXPECT_EQ(scale * v1, sv1);

		const Vec4T usv1(v1.x / scale, v1.y / scale, v1.z / scale, v1.w / scale);
		const Vec4T susv1(scale / v1.x, scale / v1.y, scale / v1.z, scale / v1.w);
		EXPECT_EQ(v1 / scale, usv1);
		EXPECT_EQ(scale / v1, susv1);


		// Vec2 operators.
		const Vec4T v2(TypeParam{ 89.25 }, TypeParam{ -44.25 }, TypeParam{ 17.2 }, TypeParam{ 3.24 });

		const Vec4T v1pv2(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
		EXPECT_EQ(v1 + v2, v1pv2);

		const Vec4T v1mv2(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
		EXPECT_EQ(v1 - v2, v1mv2);

		const Vec4T v1mltv2(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
		EXPECT_EQ(v1 * v2, v1mltv2);

		const Vec4T v1dv2(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
		EXPECT_EQ(v1 / v2, v1dv2);


		// op *= scalar.
		Vec4T v3 = v1;
		v3 *= scale;
		EXPECT_EQ(v3, sv1);


		// op /= scalar.
		Vec4T v4 = v1;
		v4 /= scale;
		EXPECT_EQ(v4, usv1);


		// op += Vec2.
		Vec4T v5 = v1;
		v5 += v2;
		EXPECT_EQ(v5, v1pv2);

		// op -= Vec2.
		Vec4T v6 = v1;
		v6 -= v2;
		EXPECT_EQ(v6, v1mv2);


		// op *= Vec2.
		Vec4T v7 = v1;
		v7 *= v2;
		EXPECT_EQ(v7, v1mltv2);


		// op /= Vec2.
		Vec4T v8 = v1;
		v8 /= v2;
		EXPECT_EQ(v8, v1dv2);
	}
}
