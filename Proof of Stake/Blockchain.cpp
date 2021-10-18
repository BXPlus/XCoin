#include "Blockchain.h";

const Block genesisBlock = Block(0, "0ee63a465f8cded3246596c920d7b673c4885b9d6e54ad1761da985e7219d9f2", "", 1465154705, "Genesis block");

Blockchain::Blockchain() {
	this->blocks = {genesisBlock};
}

void Blockchain::AppendBlock(Block block) {
	this->blocks.push_back(block);
}

bool Blockchain::isValidChain() {
	bool allValid = true;
	for (int i = 1; i < blocks.size(); i++){
		if (!blocks[i].IsValidNewBlock(blocks[i - 1])) {
			allValid = false;
			break;
		}
	}
	return this->blocks.front() == genesisBlock && allValid;
}