// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <cstring>

#include <gtest/gtest.h>

#include <edo_event.hpp>

namespace edo::UT::EventTest
{
//{ Variables

	int gFoo = 0;

	int RFoo(int i)
	{
		return gFoo += i;
	}


	void Foo(int i)
	{
		RFoo(i);
	}


	struct A
	{
		static int sBar;

		static int RBar(int i)
		{
			return sBar += 2 * i;
		}
		static void Bar(int i)
		{
			RBar(i);
		}
	};

	int A::sBar = 0;


	struct B
	{
		int pim = 0;

		int RPim(int i)
		{
			return pim += i;
		}
		void Pim(int i)
		{
			RPim(i);
		}
	};


	int gLambda = 0;
	auto rlambda = [](int _i) { return gLambda += 3 * _i; };
	auto lambda = [](int _i) { rlambda(_i); };

//}

	TEST(EventTests, Empty)
	{
		Event<void(int)> e;

		EXPECT_TRUE(e.IsEmpty());

		e += Foo;
		EXPECT_FALSE(e.IsEmpty());

		e -= Foo;
		EXPECT_TRUE(e.IsEmpty());

		e.Add(Foo);
		EXPECT_FALSE(e.IsEmpty());

		e.Remove(Foo);
		EXPECT_TRUE(e.IsEmpty());

		e.Add(Foo);
		e.RRemove(Foo);
		EXPECT_TRUE(e.IsEmpty());
	}

	TEST(EventTests, Clear)
	{
		Event<void(int)> e;

		e.Clear();

		EXPECT_TRUE(e.IsEmpty());

		e += Foo;

		e.Clear();
		EXPECT_TRUE(e.IsEmpty());

		B b;
		e.Add(&b, &B::Pim);

		e.Clear();
		EXPECT_TRUE(e.IsEmpty());

		e += Foo;
		e.Add(&b, &B::Pim);

		e.Clear();
		EXPECT_TRUE(e.IsEmpty());
	}

	TEST(EventTests, Execute)
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		Event<void(int)> e;

		e += Foo;
		e += &A::Bar;
		e += lambda;

		e.Execute(4);

		EXPECT_EQ(gFoo, 4);
		EXPECT_EQ(A::sBar, 8);
		EXPECT_EQ(gLambda, 12);


		e += Foo;
		e -= lambda;

		B b1;
		e.Add(&b1, &B::Pim);

		e(7);
		EXPECT_EQ(gFoo, 18);
		EXPECT_EQ(A::sBar, 22);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);


		EXPECT_TRUE(e.RRemove(Foo));
		EXPECT_TRUE(e.Remove(&b1, &B::Pim));

		e(2);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		EXPECT_TRUE(e.RRemove(Foo));
		EXPECT_TRUE(e.RRemove(A::Bar));
		EXPECT_FALSE(e.Remove(Foo));
		EXPECT_FALSE(e.Remove(A::Bar));

		e(1);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);

		e += Foo;
		e.Clear();
		EXPECT_EQ(gFoo, 20);
	}

	TEST(EventTests, ExecuteR)
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		Event<int(int)> e;
		std::vector<int> res;

		e += RFoo;
		e += &A::RBar;
		e += rlambda;

		e.Execute(res, 4);

		EXPECT_EQ(gFoo, 4);
		EXPECT_EQ(A::sBar, 8);
		EXPECT_EQ(gLambda, 12);

		int exp_res1[]{ 4, 8, 12 };
		EXPECT_TRUE(std::memcmp(res.data(), exp_res1, sizeof(exp_res1)) == 0);



		e += RFoo;
		e -= rlambda;

		B b1;
		e.Add(&b1, &B::RPim);

		e(res, 7);
		EXPECT_EQ(gFoo, 18);
		EXPECT_EQ(A::sBar, 22);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		int exp_res2[]{ 4, 8, 12, 11, 22, 18, 7 }; // Append result at the end.
		EXPECT_TRUE(std::memcmp(res.data(), exp_res2, sizeof(exp_res2)) == 0);

		EXPECT_TRUE(e.RRemove(RFoo));
		EXPECT_TRUE(e.Remove(&b1, &B::RPim));

		e.Execute(2);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		EXPECT_TRUE(e.RRemove(RFoo));
		EXPECT_TRUE(e.RRemove(A::RBar));
		EXPECT_FALSE(e.Remove(RFoo));
		EXPECT_FALSE(e.Remove(A::RBar));

		e(1);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);

		e += RFoo;
		e.Clear();
		EXPECT_EQ(gFoo, 20);
	}
}
