//
// Created by Cyrus on 11/13/2021.
//

#ifndef XCOIN_INTERFACE_H
#define XCOIN_INTERFACE_H

#include "blockchain.pb.h"
#include "Blockchain.h"

/************************************************************************************
 *
 *  This Interface class handles the encoding/decoding of blocks to and from Protobuf format.
 *  This optimised format helps reduce transfer sizes during blockchain synchronisations.
 *  It provides a simple public interface to encode and decode blocks and chains directly to strings.
 *  The startup and shutdown methods should be called only once, and this class was made to be
 *  used statically since it doesn't have to store anything.
 *
 ************************************************************************************/

namespace XNode{
    class Interface {
    private:
        static xcoin::interchange::Block encodeBlock(Block block);
        static Block decodeBlock(const xcoin::interchange::Block& protoBlock);
        static xcoin::interchange::Blockchain encodeChain(const std::vector<Block>& chain);
        static std::vector<Block> decodeChain(const xcoin::interchange::Blockchain& protoChain);
        static xcoin::interchange::GetHeaders generateGetHeadersMessage(int hashCount, std::string stopHash, const std::vector<std::string>& blockHeaderHashes);
        static xcoin::interchange::Headers generateHeadersReplyMessage(const std::vector<Block>& chain);
    public:
        static std::string exportBlock(const Block& block);
        static Block importBlock(const std::string& blockData);
        static std::string exportChain(const std::vector<Block>& chain);
        static std::vector<Block> importChain(const std::string& chainData);
        static void shutdown();
        static bool startup();
    };
}


#endif //XCOIN_INTERFACE_H
