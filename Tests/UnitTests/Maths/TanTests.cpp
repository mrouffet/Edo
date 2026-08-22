// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Tan
{
	TEST(Tangent, TangentFloat)
	{
		//EXPECT_EQ(edo::Tan<float>(edo::Pi<float>), 0.0f);
		EXPECT_NEAR(edo::Tan<float>(edo::Pi<float>), 0.0f, std::numeric_limits<float>::epsilon());
		
		EXPECT_FLOAT_EQ(edo::Tan<float>(edo::PiOv3<float>), float{ 1.7320508075688767 });
		EXPECT_FLOAT_EQ(edo::Tan<float>(-edo::PiOv6<float>), float{ -0.57735026918962573 });
		EXPECT_FLOAT_EQ(edo::Tan<float>(40_deg), float{ 0.83909963117727993 });
		EXPECT_FLOAT_EQ(edo::Tan<float>(0.69813170079773179_rad), float{ 0.83909963117727993 });

		EXPECT_EQ(edo::ATan(float{ 0.83909963117727993 }), Radf(0.69813170079773179_rad));

		EXPECT_EQ(edo::ATan2(1.215f, 6.25f), float{ 0.19200519160533092 });
	}

	TEST(Tangent, TangentDouble)
	{
		//EXPECT_EQ(edo::Tan<double>(edo::Pi<double>), 0.0);
		EXPECT_NEAR(edo::Tan<double>(edo::Pi<double>), 0.0, std::numeric_limits<double>::epsilon());

		EXPECT_EQ(edo::Tan<double>(edo::PiOv3<double>), 1.7320508075688767);
		EXPECT_DOUBLE_EQ(edo::Tan<double>(-edo::PiOv6<double>), -0.57735026918962573);
		EXPECT_DOUBLE_EQ(edo::Tan<double>(40_deg), 0.83909963117727993);
		EXPECT_DOUBLE_EQ(edo::Tan<double>(0.69813170079773179_rad), 0.83909963117727993);
		
		EXPECT_EQ(edo::ATan(0.83909963117727993), 0.69813170079773179_rad);

		EXPECT_EQ(edo::ATan2(1.215, 6.25), 0.19200519160533092);
	}
}
