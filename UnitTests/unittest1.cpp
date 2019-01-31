#include "stdafx.h"
#include "CppUnitTest.h"
#include "Problem15.cpp"
#include "Problem2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_Problem15)
		{
            Assert::AreEqual(6, (int) Problem15::num_paths(2, 2));
            Assert::AreEqual(20, (int) Problem15::num_paths(3, 3));
		}

        TEST_METHOD(Test_Problem2)
		{
            //Sums Fibonnacci nums less than param. Initial values: 1 , 2
            // Param = 10. Fib. nums = 1, 2, 3, 5, 8. Therefore result = 2 + 8 = 10
		    Assert::AreEqual(10, (int)Problem2::SumOfFibonnaciNumsLessThan(10));

            //Param = 0. Sum = 0
            Assert::AreEqual(0, (int)Problem2::SumOfFibonnaciNumsLessThan(0));


		}

	};
}