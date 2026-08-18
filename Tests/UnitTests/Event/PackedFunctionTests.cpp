// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <gtest/gtest.h>

#include <edo_event.hpp>

namespace edo::UT::PackedFunctionTest
{
//{ Variables

	int Foo(int _i, int _j)
	{
		return _i * 2 + _j;
	}

	class A
	{
	public:
		int Bar(int _i, int _j)
		{
			return _i * 3 + _j;
		}
	};

//}

	TEST(PackedFunctionTests, ValueConstructors)
	{
		PackedFunction<int(int)> f1;
		EXPECT_TRUE(f1.IsEmpty());

		PackedFunction f2(Foo, 2, 3);
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(), 7);

		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		EXPECT_FALSE(f3.IsEmpty());
		EXPECT_EQ(f3(), 8);
	}

	TEST(PackedFunctionTests, MoveConstructors)
	{
		// Static function move.
		PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2 = std::move(f1);
		EXPECT_TRUE(f1.IsEmpty());
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(), 7);

		// Member function move.
		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		const PackedFunction f4 = std::move(f3);
		EXPECT_TRUE(f3.IsEmpty());
		EXPECT_FALSE(f4.IsEmpty());
		EXPECT_EQ(f4(), 8);
	}

	TEST(PackedFunctionTests, CopyConstructors)
	{
		// Static function copy.
		const PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2 = f1;
		EXPECT_FALSE(f1.IsEmpty());
		EXPECT_EQ(f2(), 7);

		// Member function copy.
		A a;
		const PackedFunction f3(&a, &A::Bar, 2, 2);
		const PackedFunction f4 = f3;
		EXPECT_FALSE(f3.IsEmpty());
		EXPECT_EQ(f4(), 8);
	}

	TEST(PackedFunctionTests, Equals)
	{
		A a;
		const PackedFunction f1(Foo, 2, 3);
		const PackedFunction f2(&a, &A::Bar, 2, 2);

		EXPECT_TRUE(f1.Equals(f1));
		EXPECT_FALSE(f1.Equals(f2));

		EXPECT_EQ(f1, f1);
		EXPECT_FALSE(f1 == f2);

		EXPECT_NE(f1, f2);
		EXPECT_FALSE(f1 != f1);


		PackedFunction f3(Foo, 2, 3);
		EXPECT_FALSE(f3.IsEmpty());

		f3.Clear();
		EXPECT_TRUE(f3.IsEmpty());
	}

	TEST(PackedFunctionTests, Set)
	{
		PackedFunction<int(int, int)> f1;
		f1.Set(Foo, 2, 3);
		EXPECT_EQ(f1(), 7);

		A a;
		f1.Set(&a, &A::Bar, 2, 2);
		EXPECT_EQ(f1(), 8);
	}

	TEST(PackedFunctionTests, MoveOperators)
	{
		// Static function move.
		PackedFunction f1(Foo, 2, 3);
		PackedFunction<int(int, int)> f2;
		f2 = std::move(f1);
		EXPECT_TRUE(f1.IsEmpty());
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(), 7);

		// Member function move.
		A a;
		PackedFunction f3(&a, &A::Bar, 2, 2);
		PackedFunction<int(int, int)> f4;
		f4 = std::move(f3);
		EXPECT_TRUE(f3.IsEmpty());
		EXPECT_FALSE(f4.IsEmpty());
		EXPECT_EQ(f4(), 8);
	}

	TEST(PackedFunctionTests, CopyOperators)
	{
		// Static function copy.
		const PackedFunction f1(Foo, 2, 3);
		PackedFunction<int(int, int)> f2;
		f2 = f1;
		EXPECT_FALSE(f1.IsEmpty());
		EXPECT_EQ(f2(), 7);

		// Member function copy.
		A a;
		const PackedFunction f3(&a, &A::Bar, 2, 2);
		PackedFunction<int(int, int)> f4;
		f4 = f3;
		EXPECT_FALSE(f3.IsEmpty());
		EXPECT_EQ(f4(), 8);
	}
}
