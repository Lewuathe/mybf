//
// Created by SasakiKai on 2018/02/13.
//

#ifndef MYBF_WHILE_BLOCK_H
#define MYBF_WHILE_BLOCK_H

#include "llvm/IR/BasicBlock.h"

class WhileBlock {
public:
    llvm::BasicBlock* getCondBlock() const;
    llvm::BasicBlock* getBodyBlock() const;
    llvm::BasicBlock* getEndBlock() const;

    void setCondBlock(llvm::BasicBlock* block);
    void setBodyBlock(llvm::BasicBlock* block);
    void setEndBlock(llvm::BasicBlock* block);

//    explicit WhileBlock(
//            llvm::BasicBlock* condBlock,
//            llvm::BasicBlock* bodyBlock,
//            llvm::BasicBlock* endBlock
//    ) : condBlock(condBlock), bodyBlock(bodyBlock), endBlock(endBlock) {}


    llvm::BasicBlock* condBlock;
    llvm::BasicBlock* bodyBlock;
    llvm::BasicBlock* endBlock;
};


#endif //MYBF_WHILE_BLOCK_H
