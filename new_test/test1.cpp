#include "blockchain.cpp"

void test_Blockchain()
{
     cout << "Testing Blockchain()" << endl;
     cout << "Creating a new Blockchain" << endl;
     Blockchain myBlockchain = Blockchain();
     cout << "The length of my blockchain is:" << myBlockchain.length << endl;

     Block first = (*myBlockchain.head).block;
     cout << "The first Block of my blockchain has:"
          << "index: " << first.index
          << ", hash: " << first.hash
          << ", previousHash: " << first.previousHash
          << ", timestamp: " << first.timestamp
          << ", data: " << first.data
          << ", difficulty: " << first.difficulty
          << ", minterBalance: " << first.minterBalance
          << ", minterAddress: " << first.minterAddress << endl;

     Block last = (*myBlockchain.tail).block;
     cout << "The last Block of my blockchain has:"
          << "index: " << last.index
          << ", hash: " << last.hash
          << ", previousHash: " << last.previousHash
          << ", timestamp: " << last.timestamp
          << ", data: " << last.data
          << ", difficulty: " << last.difficulty
          << ", minterBalance: " << last.minterBalance
          << ", minterAddress: " << last.minterAddress << endl;
}