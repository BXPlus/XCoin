//
// Created by Cyrus Pellet on 25/10/2021.
//

#include "gtest/gtest.h"
#include "../Blockchain.h"
#include "../transaction.h"


class XBlockchainCoreTests: public ::testing::Test{
protected:
    Blockchain blockchain;
    void SetUp() override{
        blockchain = Blockchain();
    }
};

// Initialisation test: the blockchain is structured properly after being created
TEST_F(XBlockchainCoreTests, BlockchainInit) {
    EXPECT_EQ(blockchain.tail, blockchain.head);
    EXPECT_EQ(blockchain.getLatestBlock().index, 0);
    EXPECT_STREQ(blockchain.getLatestBlock().data.c_str(), blockchain.genesisBlock.data.c_str());
    EXPECT_EQ(blockchain.getLatestBlock().hash, blockchain.genesisBlock.hash);
    EXPECT_EQ(blockchain.isValidChain(), true);
}

// Generating the next block in the blockchain. Testing if all properties make sense with relation to previous block
TEST_F(XBlockchainCoreTests, BlockchainGenerateBlock){
    Block newBlock = blockchain.generateNextBlock("Second block!",1,100,"abc");
    EXPECT_EQ(newBlock.index,blockchain.getLatestBlock().index+1);
    EXPECT_GT(newBlock.timestamp, blockchain.getLatestBlock().timestamp);
    EXPECT_NE(newBlock.hash, blockchain.getLatestBlock().hash);
}

// Actually adding the new block in the blockchain, testing if it is still valid after
TEST_F(XBlockchainCoreTests, BlockchainAddBlock){
    Block newBlock = blockchain.generateNextBlock("Second block!",10,100,"abc");
    int oldLength = blockchain.length;
    blockchain.appendBlock(newBlock);
    EXPECT_NE(blockchain.getLatestBlock().hash, blockchain.genesisBlock.hash);
    EXPECT_EQ(blockchain.getLatestBlock().hash, newBlock.hash);
    EXPECT_EQ(blockchain.length, oldLength + 1);
    EXPECT_EQ(blockchain.difficulty , 0); // TODO: Make some more extensive tests for this when it works
}


class XTransactionTests: public ::testing::Test{
protected:
    Transaction transaction;
    UnspentTxOut unspenttxout;
    TxOut txout;
    void SetUp() override{
        transaction = Transaction();
        unspenttxout = UnspentTxOut("txOutId",
                                    1,
                                    "address",
                                    0);
        txout = TxOut("address", 0);
    }
};


// Initialisation test: UnspentTxOut has the right initialisation
TEST_F(XTransactionTests, UnspentTxOutInit){
    EXPECT_EQ(unspenttxout.txOutId, "txOutId");
    EXPECT_EQ(unspenttxout.txOutIndex, 1);
    EXPECT_EQ(unspenttxout.address, "address");
    EXPECT_EQ(unspenttxout.amount, 0);
}


// Initialisation test: TxOut has the right initialisation
TEST_F(XTransactionTests, TxOutInit){
    EXPECT_EQ(txout.address, "address");
    EXPECT_EQ(txout.amount, 0);
}


// Testing getTransactionId
TEST_F(XTransactionTests, testGetTransactionId){
    std::string ans = "";
    ans += "txIn11";
    TxIn txIn1("txIn1", 1, std::pair<uint8_t*, uint32_t>());
    ans += "txIn22";
    TxIn txIn2("txIn2", 2, std::pair<uint8_t*, uint32_t>());
    ans += "txOut13";
    TxOut txOut1("txOut1", 3);
    ans += "txOut24";
    TxOut txOut2("txOut2", 4);
    transaction.txIns = std::vector<TxIn>{txIn1, txIn2};
    transaction.txOuts = std::vector<TxOut>{txOut1, txOut2};
    transaction.id = transaction.getTransactionId();
    EXPECT_EQ(transaction.id, sha256(ans));
}


//testing findUnspentTxOut
TEST(findUnspentTxOut, handleFindUnspentTxOut) {
    std::string transactionId = "transactionId";
    int index = 123;
    UnspentTxOut UnspentTxOut1("0", index, "0", 0);
    UnspentTxOut UnspentTxOut2(transactionId, 1, "0", 0);
    UnspentTxOut UnspentTxOut3("0", 1, "0", 0);

    std::vector<UnspentTxOut> aUnspentTxOuts{UnspentTxOut1, UnspentTxOut2, UnspentTxOut3};
    EXPECT_EQ(findUnspentTxOut(transactionId, index, aUnspentTxOuts),
              std::make_pair(0, UnspentTxOut("", 0, "", 0)));

    UnspentTxOut UnspentTxOut4(transactionId, index, "0", 0);
    aUnspentTxOuts.push_back(UnspentTxOut4);
    EXPECT_EQ(findUnspentTxOut(transactionId, index, aUnspentTxOuts),
              std::make_pair(1, UnspentTxOut4));
}


// Testing isValidAddress, checking the length of address
TEST(isValidAddressTest, handleLength) {
    std::string validAddress = "04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a";
    EXPECT_EQ(isValidAddress(validAddress), 1);
    validAddress = validAddress.substr(0, 22);
    EXPECT_EQ(isValidAddress(validAddress), 0);
}


// Testing isValidAddress, checking the characters if it has only hex characters or not
TEST(isValidAddressTest, HandleCharacters) {
    std::string address = "04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a";
    address[2] = 'g';
    EXPECT_EQ(isValidAddress(address), 0);
    address[2] = 'a';
    EXPECT_EQ(isValidAddress(address), 1);
}


// Testing isValidAddress, checking if the string starts with "04"
TEST(isValidAddressTest, Handle04) {
    std::string address = "04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a";
    EXPECT_EQ(isValidAddress(address), 1);
    address[1] = '1';
    EXPECT_EQ(isValidAddress(address), 0);
}


//Testing getCoinbaseTransaction
TEST(getCoinbaseTransaction, handleCoinbaseTransaction) {
    std::string address = "04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a";
    int blockIndex = 0;
    Transaction t = getCoinbaseTransaction(address, blockIndex);
    std::string transactionId = "";

    EXPECT_EQ(t.txIns[0].txOutId, "");
    EXPECT_EQ(t.txIns[0].txOutIndex, blockIndex);
    transactionId += "0";
    EXPECT_EQ(t.txOuts[0].address, address);
    transactionId += address;
    EXPECT_EQ(t.txOuts[0].amount, 50);
    transactionId += "50";
    EXPECT_EQ(t.id, sha256(transactionId));
}


//Testing hasDuplicates
TEST(hasDuplicates, HandleDuplicate) {
    std::vector<TxIn> txIns;
    TxIn txIn1("txIn1", 1, std::pair<uint8_t*, uint32_t>());
    txIns.push_back(txIn1);
    TxIn txIn2("txIn2", 2, std::pair<uint8_t*, uint32_t>());
    txIns.push_back(txIn2);
    EXPECT_EQ(hasDuplicates(txIns), 1);
    //adding duplicates
    TxIn txIn3("txIn2", 2, std::pair<uint8_t*, uint32_t>());
    txIns.push_back(txIn3);
    EXPECT_EQ(hasDuplicates(txIns), 0);
}


//testing validateCoinbaseTx
TEST_F(XTransactionTests, ValidateCoinbaseTx) {
    std::string ans = "";
    int COINBASE_AMOUNT = 50;
    int blockIndex = 1;

    TxIn txIn("txIn", blockIndex, std::pair<uint8_t*, uint32_t>());
    TxOut txOut("txOut", COINBASE_AMOUNT);
    transaction.txIns = std::vector<TxIn>{txIn};
    transaction.txOuts = std::vector<TxOut>{txOut};
    transaction.id = transaction.getTransactionId();

    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 1);

    //invalid coinbase tx id
    std::string id = transaction.id;
    transaction.id[0] = '+';
    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 0);
    transaction.id = id;

    //multiple txIns
    transaction.txIns.push_back(txIn);
    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 0);
    transaction.txIns.pop_back();

    //invalid txIn Index
    transaction.txIns[0].txOutIndex = blockIndex - 1;
    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 0);
    transaction.txIns[0].txOutIndex = blockIndex;

    //multiple txOuts
    transaction.txOuts.push_back(txOut);
    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 0);
    transaction.txOuts.pop_back();

    //invalid coinbase amount
    transaction.txOuts[0].amount = COINBASE_AMOUNT - 1;
    EXPECT_EQ(transaction.validateCoinbaseTx(blockIndex), 0);
    transaction.txOuts[0].amount = COINBASE_AMOUNT;
}

/*

class XTransactionCoreTests: public ::testing::Test{
protected:
    Transaction transaction;
    TxIn txIn1;
    TxIn txIn2;
    TxOut txOut1;
    TxOut txOut2;
    void SetUp() override{

        txIn1 = TxIn();
        txIn1.txOutId = "firstTxOutId";
        txIn1.txOutIndex = 34;
        u_int8_t* x1;
        *x1 = 10;
        u_int32_t y1 = 52;
        std::pair<u_int8_t*, u_int32_t> signature1 = std::make_pair(x1, y1);
        txIn1.signature = signature1;

        txIn2 = TxIn();
        txIn2.txOutId = "secondTxOutId";
        txIn2.txOutIndex = 37;
        u_int8_t* x2;
        *x2 = 20;
        u_int32_t y2 = 154;
        std::pair<u_int8_t*, u_int32_t> signature2 = std::make_pair(x2, y2);
        txIn1.signature = signature2;

        txOut1 = TxOut("firstAddress", 1000);
        txOut2 = TxOut("secondAddress", 2000);

        std::vector<TxIn> txIns;
        txIns.push_back(txIn1);
        txIns.push_back(txIn2);
        std::vector<TxOut> txOuts;
        txOuts.push_back(txOut1);
        txOuts.push_back(txOut2);

        std::string txId = "myTransactionId";

        transaction = Transaction();
        transaction.id = txId;
        transaction.txIns = txIns;
        transaction.txOuts = txOuts;
    }
};

// Initialisation test: checking the transaction has the right structure when it is created
TEST_F(XTransactionCoreTests, ??) {
    EXPECT_STREQ(transaction.id, txId);
}

*/