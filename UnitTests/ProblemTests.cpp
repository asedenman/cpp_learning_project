#include "stdafx.h"
#include "CppUnitTest.h"
#include "src/problems/Prob233.cpp"
#include "src/problems/Prob2.cpp"
#include "src/problems/Prob15.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(ProblemTests)
	{
	public:
		
		TEST_METHOD(Test_Problem15)
		{
            //Number of paths from (0,0) to (xDim, yDim) selecting segments from {(1,0), (0,1)}

            //straight line
            Assert::AreEqual(1, (int) Prob15::num_paths(0, 10));

            //square
            Assert::AreEqual(6, (int) Prob15::num_paths(2, 2));

            //invalid
            Assert::AreEqual(0, (int) Prob15::num_paths(-1, 3));
		}

        TEST_METHOD(Test_Problem2)
		{
            //Sums Fibonnacci nums less than param. Initial values: 1 , 2
            // Param = 10. Fib. nums = 1, 2, 3, 5, 8. Therefore result = 2 + 8 = 10
		    Assert::AreEqual(10, (int)Prob2::SumOfFibonnaciNumsLessThan(10));

            //Param = 0. Sum = 0
            Assert::AreEqual(0, (int)Prob2::SumOfFibonnaciNumsLessThan(0));

            //Param = -10. Invalid.
            Assert::AreEqual(0, (int)Prob2::SumOfFibonnaciNumsLessThan(-10));



		}


        TEST_METHOD(Test_Problem233)
		{
            //
		    Assert::AreEqual(36, Prob233::num_lattice_pnts_on_circle(10000));
		}

	};
}