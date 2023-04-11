#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests2
{
	TEST_CLASS(Tests2)
	{
	public:

		TEST_METHOD(TestMethod1)
		{

			string test1 = sknf("!(((!a)+(!b))*(!((!c)*(!b))))");
			string test2 = sdnf("!(((!a)+(!b))*(!((!c)*(!b))))");
			Assert::IsTrue(test1 == "!x1!x2!x3 V x1!x2!x3 V x1x2!x3 V x1x2x3" && test2 == "(x1 V x2 V !x3)(x1 V !x2 V x3)(x1 V !x2 V !x3)(!x1 V x2 V !x3)");

		}

		TEST_METHOD(TestMethod2)
		{
			string test1 = sknf("((a+b)+c)");
			string test2 = sdnf("((a+b)+c)");
			Assert::IsTrue(test1 == "!x1!x2x3 V !x1x2!x3 V !x1x2x3 V x1!x2!x3 V x1!x2x3 V x1x2!x3 V x1x2x3" && test2 == "(x1 V x2 V x3)");

		}
		TEST_METHOD(TestMethod3)
		{
			string test1 = sknf("((a+b)+(c+c))");
			string test2 = sdnf("((a+b)+(c+c))");
			Assert::IsTrue(test1 == "!x1!x2x3 V !x1x2!x3 V !x1x2x3 V x1!x2!x3 V x1!x2x3 V x1x2!x3 V x1x2x3" && test2 == "(x1 V x2 V x3)");

		}
		TEST_METHOD(TestMethod4)
		{
			string test1 = sknf("!((a+b)+!c)");
			string test2 = sdnf("!((a+b)+!c)");
			Assert::IsTrue(test1 == "!x1!x2x3" && test2 == "(x1 V x2 V x3)(x1 V !x2 V x3)(x1 V !x2 V !x3)(!x1 V x2 V x3)(!x1 V x2 V !x3)(!x1 V !x2 V x3)(!x1 V !x2 V !x3)");

		}
		TEST_METHOD(TestMethod5)
		{
			string test1 = sknf("!(((!a)+(!b))+!c)");
			string test2 = sdnf("!(((!a)+(!b))+!c)");
			Assert::IsTrue(test1 == "x1x2x3" && test2 == "(x1 V x2 V x3)(x1 V x2 V !x3)(x1 V !x2 V x3)(x1 V !x2 V !x3)(!x1 V x2 V x3)(!x1 V x2 V !x3)(!x1 V !x2 V x3)");

		}

	};
}