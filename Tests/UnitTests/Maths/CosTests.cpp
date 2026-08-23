// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

namespace edo::UT::Cos
{
	TEST(Cosinus, CosinusFloat)
	{
		EXPECT_EQ(edo::Cos(0.0_rad), 1.0f);

		EXPECT_EQ(edo::Cos<float>(edo::Pi<float>), -1.0f);
		
		//EXPECT_FLOAT_EQ(edo::Cos<float>(edo::PiOv2<float>), 0.0);
		EXPECT_NEAR(edo::Cos<float>(edo::PiOv2<float>), 0.0f, std::numeric_limits<float>::epsilon());

		EXPECT_EQ(edo::Cos<float>(Degf{ 40 }), float{ 0.76604444311897801 });
		EXPECT_EQ(edo::Cos<float>(0.69813170079773179_rad), float{ 0.76604444311897801 });

		EXPECT_EQ(edo::ACos(float{ 0.76604444311897801 }), Radf(0.69813170079773179_rad));
	}

	TEST(Cosinus, CosinusDouble)
	{
		EXPECT_EQ(edo::Cos(0.0_rad), 1.0);

		//EXPECT_EQ(edo::Cos<double>(edo::Pi<double>), -1.0);
		EXPECT_NEAR(edo::Cos<double>(edo::PiOv2<double>), 0.0, std::numeric_limits<double>::epsilon());

		EXPECT_DOUBLE_EQ(edo::Cos<double>(Degd{ 40 }), 0.76604444311897801);
		EXPECT_DOUBLE_EQ(edo::Cos<double>(0.69813170079773179_rad), 0.76604444311897801);
		
		EXPECT_EQ(edo::ACos(0.76604444311897801), 0.69813170079773179_rad);
	}
}
