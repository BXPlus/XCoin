#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace XCoinTests
{
	TEST_CLASS(XBlockchainTests)
	{
	public:
		
		TEST_METHOD(BlockchainInit)
		{
			int i = 0;
			Assert::AreEqual(i, 0);
		}
	};
}
