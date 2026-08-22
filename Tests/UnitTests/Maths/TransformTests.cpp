// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include "CommonTest.hpp"

#undef Mat4T
#define Mat4T Mat4<TypeParam>

namespace edo::UT::Transform
{
	template <typename T>
	class TransformTest : public testing::Test
	{
	};

	using TestTypes = ::testing::Types<float, double>;
	TYPED_TEST_SUITE(TransformTest, TestTypes);

	TYPED_TEST(TransformTest, Constructor)
	{
		// Default constructor.
		const TrT tr0;

		EXPECT_EQ(tr0.position, Vec3T::Zero);
		EXPECT_EQ(tr0.rotation, QuatT::Identity);
		EXPECT_EQ(tr0.scale, Vec3T::One);


		// Value constructor.
		Vec3T tr1Pos = Vec3T(4.26f, 48.21f, 112.3f);
		QuatT tr1Rot = QuatT(32_deg, Vec3T::Up);
		Vec3T tr1Scale = Vec3T(10.0f, 6.2f, 98.2f);

		const TrT tr1{ tr1Pos, tr1Rot, tr1Scale };

		EXPECT_EQ(tr1.position, tr1Pos);
		EXPECT_EQ(tr1.rotation, tr1Rot);
		EXPECT_EQ(tr1.scale, tr1Scale);


		// Copy constructor.
		const TrT tr2 = tr1;

		EXPECT_EQ(tr2.position, tr1.position);
		EXPECT_EQ(tr2.rotation, tr1.rotation);
		EXPECT_EQ(tr2.scale, tr1.scale);
	}


	TYPED_TEST(TransformTest, Equals)
	{
		const TrT tr0 { Vec3T::Zero, QuatT::Zero, Vec3T::Zero };

		const TrT tr1;

		const TrT tr2 {
			Vec3T(4.26f, 48.21f, 112.3f),
			QuatT(32_deg, Vec3T::Up),
			Vec3T(10.0f, 6.2f, 98.2f)
		};

		// Zero
		EXPECT_TRUE(tr0.IsZero());
		EXPECT_FALSE(tr1.IsZero());
		EXPECT_FALSE(tr2.IsZero());


		// Identity
		EXPECT_FALSE(tr0.IsIdentity());
		EXPECT_TRUE(tr1.IsIdentity());
		EXPECT_FALSE(tr2.IsIdentity());


		// Equals
		EXPECT_TRUE(tr0.Equals(tr0));
		EXPECT_FALSE(tr0.Equals(tr1));
		EXPECT_TRUE(tr1.Equals(tr1));
		EXPECT_FALSE(tr1.Equals(tr2));
		EXPECT_TRUE(tr2.Equals(tr2));

		EXPECT_EQ(tr0, tr0);
		EXPECT_NE(tr0, tr1);
		EXPECT_EQ(tr1, tr1);
		EXPECT_NE(tr1, tr2);
		EXPECT_EQ(tr2, tr2);
	}


	TYPED_TEST(TransformTest, TransformationAxis)
	{
		/** Values from QuaternionTests.cpp */

		const QuatT q1(
			TypeParam{ 0.65379899684951437 },
			TypeParam{ 0.49198400932684733 },
			TypeParam{ -0.57343602132006610 },
			TypeParam{ -0.040862400050191698 }
		);

		const Vec3T q1RightAxis(
			TypeParam{ 0.33900278742950163 },
			TypeParam{ -0.61767429804632101 },
			TypeParam{ 0.70961649617805012 }
		);

		const Vec3T q1UpAxis(
			TypeParam{ -0.51081111339960539 },
			TypeParam{ 0.51256399765763738 },
			TypeParam{ 0.69018124774053136 }
		);

		const Vec3T q1ForwardAxis(
			TypeParam{ -0.79003108580769366 },
			TypeParam{ -0.59645335931504828 },
			TypeParam{ -0.14175427196141333 }
		);

		const TrT trR = { Vec3T::Zero, q1, Vec3T::One };

		EXPECT_EQ(trR.Right(), q1RightAxis);
		EXPECT_EQ(trR.Up(), q1UpAxis);
		EXPECT_EQ(trR.Forward(), q1ForwardAxis);

		
		const TrT trPRS = {
			Vec3T(5.25f, 321.2f, 44.25f),
			q1,
			Vec3T(99.2f, 0.2f, 1.2f)
		};

		EXPECT_EQ(trPRS.Right(), q1RightAxis);
		EXPECT_EQ(trPRS.Up(), q1UpAxis);
		EXPECT_EQ(trPRS.Forward(), q1ForwardAxis);
	}

	TYPED_TEST(TransformTest, TransformationMatrix)
	{
		const Vec3T transl = Vec3T(5.25f, 321.2f, 44.25f);
		const QuatT rot = QuatT(46_deg, Vec3T(2.0f, 8.45f, 0.4f).Normalize());
		const Vec3T scale = Vec3(4.25f, 6.32f, 2.2f);

		const TrT trP { transl, QuatT::Identity, Vec3T::One };
		EXPECT_EQ(trP.Matrix(), (Mat4T::MakeTranslation(transl)));

		const TrT trR { Vec3T::Zero, rot, Vec3T::One };
		EXPECT_EQ(trR.Matrix(), (Mat4T::MakeRotation(rot)));

		const TrT trS { Vec3T::Zero, QuatT::Identity, scale };
		EXPECT_EQ(trS.Matrix(), (Mat4T::MakeScale(scale)));

		const TrT trPR { transl, rot, Vec3T::One };
		const Mat4T matPR = Mat4T::MakeTranslation(transl) * Mat4T::MakeRotation(rot);
		EXPECT_EQ(trPR.Matrix(), matPR);

		const TrT trPS { transl, QuatT::Identity, scale };
		const Mat4T matPS = Mat4T::MakeTranslation(transl) * Mat4T::MakeScale(scale);
		EXPECT_EQ(trPS.Matrix(), matPS);

		const TrT trPRS { transl, rot, scale };
		const Mat4T matPRS = Mat4T::MakeTranslation(transl) * Mat4T::MakeRotation(rot) * Mat4T::MakeScale(scale);
		EXPECT_EQ(trPRS.Matrix(), matPRS);
	}

	TYPED_TEST(TransformTest, Lerp)
	{
		/** Values from QuaternionTests.cpp */

		const QuatT q1(TypeParam{ 0.653799 }, TypeParam{ 0.491984 }, TypeParam{ -0.573436 }, TypeParam{ -0.0408624 });
		const QuatT q2(TypeParam{ 0.2845691 }, TypeParam{ 0.05528782 }, TypeParam{ -0.162611 }, TypeParam{ -0.9431444 });
		const QuatT slerp_res05(TypeParam{ 0.5721251 }, TypeParam{ 0.3336728 }, TypeParam{ -0.4487695 }, TypeParam{ -0.5999511 });


		/** Values from Vector3Tests.cpp */

		const Vec3T v1(TypeParam{ 2.0 }, TypeParam{ 2.0 }, TypeParam{ 0.0f });
		const Vec3T v2(TypeParam{ -2.0 }, TypeParam{ 4.0 }, TypeParam{ 8.0f });
		const Vec3T lerp_res05(TypeParam{ 0.0 }, TypeParam{ 3.0 }, TypeParam{ 4.0 });

		const TrT start{ v1, q1, v1 };
		const TrT end{ v2, q2, v2 };
		const TrT res{ lerp_res05, slerp_res05, lerp_res05 };

		EXPECT_TR_NEAR(TrT::Lerp(start, end, 0.5f), res, TypeParam{ 0.00001 });
		EXPECT_TR_NEAR(TrT::Lerp(start, end, 10.0f), end, TypeParam{ 0.00001 });
	}

	TYPED_TEST(TransformTest, Multiply)
	{
		const QuatT q1(90_deg, Vec3T::Right);
		const QuatT q2(90_deg, Vec3T::Up);


		// Translation
		{
			const TrT tr1{ Vec3T(1, 2, 3), QuatT::Identity, Vec3T::One };
			const TrT tr_res{ Vec3T(2, 4, 6), QuatT::Identity, Vec3T::One };

			EXPECT_EQ(tr1 * tr1, tr_res);
		}

		// Rotation
		{
			const TrT tr1{ Vec3T::Zero, q1, Vec3T::One };
			const TrT tr2{ Vec3T::Zero, q2, Vec3T::One };

			const TrT tr12_res{ Vec3T::Zero, q1 * q2, Vec3T::One };

			EXPECT_EQ(tr1 * tr2, tr12_res);
		}


		// Scale
		{
			const TrT tr1{ Vec3T::Zero, QuatT::Identity, Vec3T(3, 4, 7) };
			const TrT tr_res{ Vec3T::Zero, QuatT::Identity, Vec3T(9, 16, 49) };

			EXPECT_EQ(tr1 * tr1, tr_res);
		}


		// Translation Rotation
		{
			const TrT trParent{ Vec3T(1, 2, 3), q1, Vec3T::One };
			const TrT trChild{ Vec3T(4, 5, 9), q2, Vec3T::One };
			const TrT tr_res{ Vec3T(5, -7, 8), q1 * q2, Vec3T::One };

			EXPECT_TR_NEAR(trParent * trChild, tr_res, TypeParam{ 0.00001 });
		}


		// Translation Rotation Scale
		{
			const TrT trParent{ Vec3T(1, 2, 3), q1, Vec3T(4, 6, 7) };
			const TrT trChild{ Vec3T(4, 5, 9), q2, Vec3T(10, 20, 30) };
			const TrT tr_res{ Vec3T(5, -7, 8), q1 * q2, Vec3T(40, 120, 210) };

			EXPECT_TR_NEAR(trParent * trChild, tr_res, TypeParam{ 0.00001 });


			TrT trCopy = trParent;
			trCopy *= trChild;

			EXPECT_TR_NEAR(trCopy, tr_res, TypeParam{ 0.00001 });
		}
	}

	TYPED_TEST(TransformTest, Divide)
	{
		const QuatT q1(90_deg, Vec3T::Right);
		const QuatT q2(90_deg, Vec3T::Up);


		// Translation
		{
			const TrT tr1{ Vec3T(1, 2, 3), QuatT::Identity, Vec3T::One };
			const TrT tr2{ Vec3T(12, 1, 9), QuatT::Identity, Vec3T::One };
			const TrT tr_res{ Vec3T(-11, 1, -6), QuatT::Identity, Vec3T::One };

			EXPECT_EQ(tr1 / tr2, tr_res);
		}

		// Rotation
		{
			const TrT tr1{ Vec3T::Zero, q1, Vec3T::One };
			const TrT tr2{ Vec3T::Zero, q2, Vec3T::One };
			const TrT tr12_res{ Vec3T::Zero, q1 / q2, Vec3T::One };

			EXPECT_EQ(tr1 / tr2, tr12_res);
		}


		// Scale
		{
			const TrT tr1{ Vec3T::Zero, QuatT::Identity, Vec3T(3, 4, 7) };
			const TrT tr2{ Vec3T::Zero, QuatT::Identity, Vec3T(3, 8, 1) };
			const TrT tr_res{ Vec3T::Zero, QuatT::Identity, Vec3T(1, 0.5f, 7) };

			EXPECT_EQ(tr1 / tr2, tr_res);
		}


		// Translation Rotation
		{
			const TrT trParent{ Vec3T(1, 2, 3), q1, Vec3T::One };
			const TrT trChild{ Vec3T(4, 5, 9), q2, Vec3T::One };
			const TrT tr_res{ Vec3T(-3, 11, -2), q1 / q2, Vec3T::One };

			EXPECT_TR_NEAR(trParent / trChild, tr_res, TypeParam{ 0.00001 });
		}


		// Translation Rotation Scale
		{
			const TrT trParent{ Vec3T(1, 2, 3), q1, Vec3T(4, 6, 25) };
			const TrT trChild{ Vec3T(4, 5, 9), q2, Vec3T(10, 20, 5) };
			const TrT tr_res{ Vec3T(-3, 11, -2), q1 / q2, Vec3T(0.4f, 0.3f, 5) };

			EXPECT_TR_NEAR(trParent / trChild, tr_res, TypeParam{ 0.00001 });


			TrT trCopy = trParent;
			trCopy /= trChild;

			EXPECT_TR_NEAR(trCopy, tr_res, TypeParam{ 0.00001 });
		}
	}


	TYPED_TEST(TransformTest, ToString)
	{
		// Value constructor.
		Vec3T tr1Pos = Vec3T(4.26f, 48.21f, 112.3f);
		QuatT tr1Rot = QuatT(32_deg, Vec3T::Up);
		Vec3T tr1Scale = Vec3T(10.0f, 6.2f, 98.2f);
		const TrT tr1{ tr1Pos, tr1Rot, tr1Scale };

		EDO_LOG(tr1);
	}
}
