//
// Created by Cyrus on 11/13/2021.
// Handles encoding/decoding of blockchain into transferable & storable protobuf data
//

#include "interface.h"

/**
* Internal function converting a block to a protobuf interchange block object.
* @param block is the block to convert
* @returns a protobuf interchange block object
*/
xcoin::interchange::Block XNode::Interface::encodeBlock(Block block) {
    xcoin::interchange::Block encodedBlock;
    encodedBlock.set_index(block.index);
    encodedBlock.set_hash(block.hash);
    encodedBlock.set_previoushash(block.previousHash);
    encodedBlock.set_timestamp(block.timestamp);
    encodedBlock.set_data(block.data);
    encodedBlock.set_difficulty(block.difficulty);
    encodedBlock.set_nonce(block.nonce);
    encodedBlock.set_minterbalance(block.minterBalance);
    encodedBlock.set_minteraddress(block.minterAddress);
    return encodedBlock;
}

/**
* Internal function converting a protobuf interchange block object back to a block.
* @param protoBlock is a protobuf interchange block object
* @returns a block
*/
Block XNode::Interface::decodeBlock(const xcoin::interchange::Block& protoBlock) {
    return {static_cast<int>(protoBlock.index()), protoBlock.hash(), protoBlock.previoushash(), protoBlock.timestamp(), protoBlock.data(), static_cast<int>(protoBlock.difficulty()), static_cast<int>(protoBlock.minterbalance()), protoBlock.minteraddress()};
}

/**
* Internal function converting a list of blocks to a protobuf interchange blockchain object.
* @param chain is the list of blocks to convert
* @returns a protobuf interchange blockchain object
*/
xcoin::interchange::Blockchain XNode::Interface::encodeChain(const vector<Block>& chain) {
    xcoin::interchange::Blockchain encodedChain;
    for (const Block& block:chain) {
        xcoin::interchange::Block* encodedBlock = encodedChain.add_blocks();
        encodedBlock->CopyFrom(encodeBlock(block));
    }
    return encodedChain;
}

/**
* Internal function converting a protobuf interchange blockchain object back to a list of blocks.
* @param protoChain is a protobuf interchange blockchain object
* @returns a list of blocks
*/
vector<Block> XNode::Interface::decodeChain(const xcoin::interchange::Blockchain& protoChain) {
    vector<Block> decodedBlocks;
    for (const xcoin::interchange::Block& block:protoChain.blocks()) {
        decodedBlocks.push_back(decodeBlock(block));
    }
    return decodedBlocks;
}

/**
* Function serialising a block to a string
* @param block is the block to convert
* @returns a serialised string
*/
string XNode::Interface::exportBlock(const Block& block) {
    xcoin::interchange::Block encodedBlock = encodeBlock(block);
    return encodedBlock.SerializeAsString();
}

/**
* Function deserialising a string back to a block
* @param blockData is block data as a string
* @returns a block
*/
Block XNode::Interface::importBlock(const string& blockData) {
    xcoin::interchange::Block decodedBlock;
    decodedBlock.ParseFromString(blockData);
    return decodeBlock(decodedBlock);
}

/**
* Function serialising a list of blocks to a string
* @param chain is the list of blocks to convert
* @returns a serialised string
*/
string XNode::Interface::exportChain(const vector<Block>& chain) {
    xcoin::interchange::Blockchain encodedChain = encodeChain(chain);
    return encodedChain.SerializeAsString();
}

/**
* Function deserialising a string back to a list of blocks
* @param chainData is block list data as a string
* @returns a list of blocks
*/
vector<Block> XNode::Interface::importChain(const string& chainData) {
    xcoin::interchange::Blockchain encodedChain;
    encodedChain.ParseFromString(chainData);
    return decodeChain(encodedChain);
}

/**
* Function that frees all memory used up by Protobuf during use
*/
void XNode::Interface::shutdown() {
    google::protobuf::ShutdownProtobufLibrary();
}

/**
* Function that verifies that the Protobuf library is ready to start
*/
bool XNode::Interface::startup() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    return true;
}