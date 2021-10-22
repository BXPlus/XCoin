#include "pch.h"
#include "CppUnitTest.h"
#include "../Proof of Stake v_0/blockchain.h";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace XCoinTests
{
	TEST_CLASS(XBlockchainTests)
	{
	public:
		
		TEST_METHOD(BlockchainInit)
		{
			Blockchain chain = Blockchain();
			Assert::IsNotNull(&chain);
		}
	};
}
