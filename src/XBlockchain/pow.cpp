#include 'pow.h'

powblock::powblock(int index, std::string timestamp, int data, std::string prevHash){
    this -> index = index;
    this ->prevHash = prevHash;
    this->timestamp =timestamp;
    this->data=data;
    this -> hash='';
}

//std::string powblock::CH(int index, std::string prevHash, std::string timestamp, int data)
//{
//    std::stringstream ss;
//    ss << index << previousHash << timestamp << data << difficulty;
//    return sha256(ss.str());
//}

//std::string powblock::calcHash()
//{
//    return CH(index, previousHash, timestamp, data, difficulty, minterBalance, minterAddress);
//}

std::string powblock::calcHash(){
    return SHA256(this.index + this.prevHash + this.timestamp + this.data)).to String();
}

powblock::powblock mineblock(int difficulty){
    while(this.hash.substring(0, difficulty)!== Array(difficulty + 1).join('0')){
        this -> hash= this.calcHash()
        this.i++
    }
}

powchain::powchain(){
    this ->chain=[this -> genesisblock()];
    this ->difficulty=1
}

powblock powchain::genesisblock(){
    return powblock(0,'10/10/2021','Gen Block', 0)
}

powblock powchain::lastblock(){
    return this.chain[this.chain.length -1]
}

powblock powchain::add(powblock newpowblock, int difficulty){
    newpowblock.prevHash=this.lastblock().hash;
    newpowblock.mineBlock(difficulty);
    this.chain.push (newpowblock);
}

bool powchain::validchain{
    for (let i=1; i<this.chain.length; i++){
        const block = this.chain[i];
        const prevblock = this.chain [i-1];
        if (block.hash == block.calcHash()){
            return true
        }
        if(block.prevHash == prevblock.hash){
            return true
        }
    }
    return false
}





