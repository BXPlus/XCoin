//
// Created by Cyrus on 11/13/2021.
// Handles encoding/decoding of blockchain into transferable & storable protobuf data
//

#ifndef XCOIN_INTERFACE_H
#define XCOIN_INTERFACE_H

#include "blockchain.pb.h"
#include "Blockchain.h"

class interface {
    string encodeBlock(Block block);
    Block decodeProtobuf(xcoin::interchange::Block block);
    bool startup();
    void shutdown();
};


#endif //XCOIN_INTERFACE_H
