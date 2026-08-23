// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Sin
{
	TEST(Sinus, SinusFloat)
	{
		EXPECT_EQ(edo::Sin(0.0_rad), 0.0f);

		//EXPET_FLOAT_EQ(edo::Sin<float>(edo::Pi<float>), 0.0f);
		EXPECT_NEAR(edo::Sin<float>(edo::Pi<float>), 0.0f, std::numeric_limits<float>::epsilon());

		EXPECT_EQ(edo::Sin<float>(edo::PiOv2<float>), 1.0f);
		EXPECT_EQ(edo::Sin<float>(-edo::PiOv2<float>), -1.0f);

		EXPECT_FLOAT_EQ(edo::Sin<float>(Degf{ 40 }), float{ 0.64278760968653925 });
		EXPECT_FLOAT_EQ(edo::Sin<float>(0.69813170079773179_rad), float{ 0.64278760968653925 });
		
		EXPECT_EQ(edo::ASin(float{ 0.64278760968653925 }), Radf(0.69813170079773179_rad));
	}

	TEST(Sinus, SinusDouble)
	{
		EXPECT_EQ(edo::Sin(0.0_rad), 0.0);

		//EXPECT_DOUBLE_EQ(edo::Sin<double>(edo::Pi<double>), 0.0);
		EXPECT_NEAR(edo::Sin<double>(edo::Pi<double>), 0.0, std::numeric_limits<double>::epsilon());

		EXPECT_EQ(edo::Sin<double>(edo::PiOv2<double>), 1.0);
		EXPECT_EQ(edo::Sin<double>(-edo::PiOv2<double>), -1.0);

		EXPECT_EQ(edo::Sin<double>(Degd{ 40 }), 0.64278760968653925);
		EXPECT_EQ(edo::Sin<double>(0.69813170079773179_rad), 0.64278760968653925);
		
		EXPECT_EQ(edo::ASin(0.64278760968653925), 0.69813170079773179_rad);
	}
}
