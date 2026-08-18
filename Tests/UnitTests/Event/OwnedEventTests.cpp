// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#include <cstring>

#include <gtest/gtest.h>

#include <edo_event.hpp>

namespace edo::UT::OwnedEventTest
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

	class EventOwner
	{
	public:
		OwnedEvent<EventOwner, void(int)> e;

		void Do(int _param)
		{
			e.Execute(_param);
		}

		void operator()(int _param)
		{
			e(_param);
		}
	};

	class EventOwnerR
	{
	public:
		OwnedEvent<EventOwnerR, int(int)> e;

		void Do(int _param)
		{
			e.Execute(_param);
		}

		void Do(std::vector<int>& _results, int _param)
		{
			e.Execute(_results, _param);
		}

		void operator()(int _param)
		{
			e.Execute(_param);
		}

		void operator()(std::vector<int>& _results, int _param)
		{
			e.Execute(_results, _param);
		}
	};

//}

	TEST(OwnedEventTests, Empty)
	{
		EventOwner owner;

		EXPECT_TRUE(owner.e.IsEmpty());

		owner.e += Foo;
		EXPECT_FALSE(owner.e.IsEmpty());

		owner.e -= Foo;
		EXPECT_TRUE(owner.e.IsEmpty());

		owner.e.Add(Foo);
		EXPECT_FALSE(owner.e.IsEmpty());

		owner.e.Remove(Foo);
		EXPECT_TRUE(owner.e.IsEmpty());

		owner.e.Add(Foo);
		owner.e.RRemove(Foo);
		EXPECT_TRUE(owner.e.IsEmpty());
	}

	TEST(OwnedEventTests, Clear)
	{
		EventOwner owner;

		owner.e.Clear();

		EXPECT_TRUE(owner.e.IsEmpty());

		owner.e += Foo;

		owner.e.Clear();
		EXPECT_TRUE(owner.e.IsEmpty());

		B b;
		owner.e.Add(&b, &B::Pim);

		owner.e.Clear();
		EXPECT_TRUE(owner.e.IsEmpty());

		owner.e += Foo;
		owner.e.Add(&b, &B::Pim);

		owner.e.Clear();
		EXPECT_TRUE(owner.e.IsEmpty());
	}

	TEST(OwnedEventTests, Execute)
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		EventOwner owner;
		// owner.e.Execute(1); // must not compile.
		// owner.e(1); // must not compile.

		owner.e += Foo;
		owner.e += &A::Bar;
		owner.e += lambda;

		owner.Do(4);

		EXPECT_EQ(gFoo, 4);
		EXPECT_EQ(A::sBar, 8);
		EXPECT_EQ(gLambda, 12);


		owner.e += Foo;
		owner.e -= lambda;

		B b1;
		owner.e.Add(&b1, &B::Pim);

		owner(7);
		EXPECT_EQ(gFoo, 18);
		EXPECT_EQ(A::sBar, 22);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);


		EXPECT_TRUE(owner.e.RRemove(Foo));
		EXPECT_TRUE(owner.e.Remove(&b1, &B::Pim));

		owner(2);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		EXPECT_TRUE(owner.e.RRemove(Foo));
		EXPECT_TRUE(owner.e.RRemove(A::Bar));
		EXPECT_FALSE(owner.e.Remove(Foo));
		EXPECT_FALSE(owner.e.Remove(A::Bar));

		owner(1);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);

		owner.e += Foo;
		owner.e.Clear();
		EXPECT_EQ(gFoo, 20);
	}

	TEST(OwnedEventTests, ExecuteR)
	{
		gFoo = 0;
		A::sBar = 0;
		gLambda = 0;

		EventOwnerR owner;
		std::vector<int> res;
		// owner.e.Execute(res, 1); // must not compile.
		// owner.e(res, 1); // must not compile.

		owner.e += RFoo;
		owner.e += &A::RBar;
		owner.e += rlambda;

		owner.Do(res, 4);

		EXPECT_EQ(gFoo, 4);
		EXPECT_EQ(A::sBar, 8);
		EXPECT_EQ(gLambda, 12);

		int exp_res1[]{ 4, 8, 12 };
		EXPECT_TRUE(std::memcmp(res.data(), exp_res1, sizeof(exp_res1)) == 0);



		owner.e += RFoo;
		owner.e -= rlambda;

		B b1;
		owner.e.Add(&b1, &B::RPim);

		owner(res, 7);
		EXPECT_EQ(gFoo, 18);
		EXPECT_EQ(A::sBar, 22);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		int exp_res2[]{ 4, 8, 12, 11, 22, 18, 7 }; // Append result at the end.
		EXPECT_TRUE(std::memcmp(res.data(), exp_res2, sizeof(exp_res2)) == 0);

		EXPECT_TRUE(owner.e.RRemove(RFoo));
		EXPECT_TRUE(owner.e.Remove(&b1, &B::RPim));

		owner.Do(2);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);
		EXPECT_EQ(gLambda, 12);
		EXPECT_EQ(b1.pim, 7);

		EXPECT_TRUE(owner.e.RRemove(RFoo));
		EXPECT_TRUE(owner.e.RRemove(A::RBar));
		EXPECT_FALSE(owner.e.Remove(RFoo));
		EXPECT_FALSE(owner.e.Remove(A::RBar));

		owner(1);
		EXPECT_EQ(gFoo, 20);
		EXPECT_EQ(A::sBar, 26);

		owner.e += RFoo;
		owner.e.Clear();
		EXPECT_EQ(gFoo, 20);
	}
}
