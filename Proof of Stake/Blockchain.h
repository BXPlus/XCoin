#pragma once

#include "Block.h"
#include <vector>

class Blockchain {
private:
	std::vector<Block> blocks;
public:
	Blockchain();
	std::vector<Block> GetBlocks();
	void AppendBlock(Block block);
	bool isValidChain();
	void ReplaceChain(std::vector<Block> blocks);
};