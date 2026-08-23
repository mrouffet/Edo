// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Equals
{
	template <typename T>
	class EqualsTest : public testing::Test
	{
	};

	using TestTypes = ::testing::Types<float, double, int32_t, uint32_t>;
	TYPED_TEST_SUITE(EqualsTest, TestTypes);

	TYPED_TEST(EqualsTest, Equals)
	{
		const TypeParam defaultVal = static_cast<TypeParam>(1.26);
		const TypeParam epsilon = std::numeric_limits<TypeParam>::epsilon();

		EXPECT_TRUE(edo::Equals(defaultVal, defaultVal));
		EXPECT_TRUE(edo::Equals(defaultVal, defaultVal + epsilon));

		// float / double test only.
		if constexpr (std::is_floating_point_v<TypeParam>)
		{
			EXPECT_FALSE(edo::Equals(defaultVal, defaultVal + 2 * epsilon));
		}
		
		EXPECT_TRUE(edo::Equals(defaultVal, defaultVal + 1, TypeParam{ 1 }));
		EXPECT_FALSE(edo::Equals(defaultVal, defaultVal + 1, epsilon));
	}
}
