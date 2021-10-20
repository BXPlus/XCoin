#include "Blockchain.h";

const Block genesisBlock = Block(0, "0ee63a465f8cded3246596c920d7b673c4885b9d6e54ad1761da985e7219d9f2", "", 1465154705, "Genesis block");

Blockchain::Blockchain() {
	this->blocks = {genesisBlock};
}

std::vector<Block> Blockchain::GetBlocks() {
	return this->blocks;
}

void Blockchain::AppendBlock(Block block) {
	this->blocks.push_back(block);
}

bool isChainValid(std::vector<Block> blocks) {
	bool allValid = true;
	for (int i = 1; i < blocks.size(); i++) {
		if (!blocks[i].IsValidNewBlock(blocks[i - 1])) {
			allValid = false;
			break;
		}
	}
	return allValid;
}

bool Blockchain::isValidChain() {
	return this->blocks.front() == genesisBlock && isChainValid(this->blocks);
}

void Blockchain::ReplaceChain(std::vector<Block> blocks) {
	if (isChainValid(blocks) && blocks.size() > this->blocks.size()) {
		this->blocks = blocks;
	}
}