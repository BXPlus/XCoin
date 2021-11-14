//
// Created by Cyrus on 11/13/2021.
// Handles encoding/decoding of blockchain into transferable & storable protobuf data
//

#include "interface.h"

string interface::encodeBlock(Block block) {
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
    return encodedBlock.SerializeAsString();
}

Block interface::decodeProtobuf(xcoin::interchange::Block block) {
    return Block(block.index(), block.hash(), block.previoushash(), block.timestamp(), block.data(), block.difficulty(), block.minterbalance(), block.minteraddress());
}


bool interface::startup() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    return true;
}

void interface::shutdown() {
    google::protobuf::ShutdownProtobufLibrary();
}
