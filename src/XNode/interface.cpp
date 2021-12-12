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
    return {static_cast<int>(protoBlock.index()), protoBlock.hash(), protoBlock.previoushash(), protoBlock.headerhash(), protoBlock.previousheaderhash(), protoBlock.timestamp(), protoBlock.data(), static_cast<int>(protoBlock.difficulty()), static_cast<int>(protoBlock.minterbalance()), protoBlock.minteraddress()};
}

/**
* Internal function converting a list of blocks to a protobuf interchange blockchain object.
* @param chain is the list of blocks to convert
* @returns a protobuf interchange blockchain object
*/
xcoin::interchange::Blockchain XNode::Interface::encodeChain(const std::vector<Block>& chain) {
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
std::vector<Block> XNode::Interface::decodeChain(const xcoin::interchange::Blockchain& protoChain) {
    std::vector<Block> decodedBlocks;
    for (const xcoin::interchange::Block& block:protoChain.blocks()) {
        decodedBlocks.push_back(decodeBlock(block));
    }
    return decodedBlocks;
}

/**
* Internal function to construct a getHeaders request object for another node to sync headers
* @param hashCount is the number of hashes provided not including the stop hash (1 to 200)
* @param stopHash is the last header hash being requested, set "" for non-stop
* @param blockHeaderHashes is one or more header hashes in reverse order of block height.
* @returns a getHeaders internal protobuf interchange message object
*/
xcoin::interchange::GetHeaders XNode::Interface::generateGetHeadersMessage(int hashCount, std::string stopHash, const std::vector<std::string>& blockHeaderHashes) {
    xcoin::interchange::GetHeaders request;
    request.set_hashcount(hashCount);
    request.set_stophash(stopHash);
    for (const std::string& headerHash : blockHeaderHashes){
        request.add_blockheaderhashes(headerHash);
    }
    return request;
}

/**
* Internal function to construct a Headers reply object for another node to sync headers
* @param chain is the block chain to encode back to headers
* @returns a Headers internal protobuf interchange message object
*/
xcoin::interchange::Headers XNode::Interface::generateHeadersReplyMessage(const std::vector<Block> &chain) {
    xcoin::interchange::Headers reply;
    for (Block block: chain){
        xcoin::interchange::Header* header = reply.add_headers();
        header->set_blockheaderhash(block.headerHash);
        header->set_merkleroothash(block.merkle_root_hash);
        header->set_time(block.timestamp);
    }
    return reply;
}

/**
* Function serialising a block to a std::string
* @param block is the block to convert
* @returns a serialised std::string
*/
std::string XNode::Interface::exportBlock(const Block& block) {
    xcoin::interchange::Block encodedBlock = encodeBlock(block);
    return encodedBlock.SerializeAsString();
}

/**
* Function deserialising a std::string back to a block
* @param blockData is block data as a std::string
* @returns a block
*/
Block XNode::Interface::importBlock(const std::string& blockData) {
    xcoin::interchange::Block decodedBlock;
    decodedBlock.ParseFromString(blockData);
    return decodeBlock(decodedBlock);
}

/**
* Function serialising a list of blocks to a std::string
* @param chain is the list of blocks to convert
* @returns a serialised std::string
*/
std::string XNode::Interface::exportChain(const std::vector<Block>& chain) {
    xcoin::interchange::Blockchain encodedChain = encodeChain(chain);
    return encodedChain.SerializeAsString();
}

/**
* Function deserialising a std::string back to a list of blocks
* @param chainData is block list data as a std::string
* @returns a list of blocks
*/
std::vector<Block> XNode::Interface::importChain(const std::string& chainData) {
    xcoin::interchange::Blockchain encodedChain;
    encodedChain.ParseFromString(chainData);
    return decodeChain(encodedChain);
}

/**
* Function serialising a DNS map to a std::string
* @param dnsMap is map of ip/ports to public addresses
* @returns an encoded protobuf string
*/
std::string XNode::Interface::exportDNSHandshake(const std::map<std::string, std::string>& dnsMap) {
    xcoin::interchange::DNSHandshake *encodedHandshake;
    for (auto const& x : dnsMap){
        xcoin::interchange::DNSEntry *entry = encodedHandshake->add_entries();
        entry->set_ipport(x.first);
        entry->set_publickey(x.second);
    }
    xcoin::interchange::XNodeMessage encodedEnvelope;
    std::string payload = encodedHandshake->SerializeAsString();
    encodedEnvelope.set_startstring(payload.substr(0,5));
    encodedEnvelope.set_size(payload.size());
    encodedEnvelope.set_checksum(""); //TODO: Implement MD5 here
    encodedEnvelope.set_allocated_dnshandshakemessage(encodedHandshake);
    return encodedEnvelope.SerializeAsString();
}

/**
* Function deserialising a std::string back to a DNS handshake
* @param encodedHandshake is the encoded handshake
* @returns a tuple containing the DNS ip/port to public address map and a bool set to true if the peer expects a reply
*/
std::pair<std::map<std::string, std::string>, bool> XNode::Interface::decodeDNSHandshake(const std::string& encodedHandshake) {
    auto res = std::pair<std::map<std::string, std::string>, bool>();
    auto dnsl = std::map<std::string, std::string>();
    xcoin::interchange::DNSHandshake encodedObject;
    encodedObject.ParseFromString(encodedHandshake);
    for (xcoin::interchange::DNSEntry entry : encodedObject.entries()){
        dnsl[entry.ipport()] = entry.publickey();
    }
    res.first = dnsl;
    return res;
}

/**
* Function deserialising a generic XNode message envelope into specialised message types
* @param encodedEnvelope is the encoded envelope
* @returns idk yet
*/
XNode::XNodeMessageDecodingResult XNode::Interface::decodeXNodeMessageEnvelope(const std::string &encodedEnvelope) {
    xcoin::interchange::XNodeMessage decodedEnvelope;
    XNode::XNodeMessageDecodingResult res;
    res.messageType = -1;
    decodedEnvelope.ParseFromString(encodedEnvelope);
    if (decodedEnvelope.has_dnshandshakemessage()){
        std::string payloadString = res.dnsHandshake.SerializeAsString();
        if (decodedEnvelope.startstring() == payloadString.substr(0,5)){
            res.messageType = 0;
            res.dnsHandshake = decodedEnvelope.dnshandshakemessage();
        }
        //TODO: also check for MD5 hash
    }
    return res;
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