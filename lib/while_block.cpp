//
// Created by SasakiKai on 2018/02/13.
//

#include "while_block.h"

llvm::BasicBlock* WhileBlock::getCondBlock() const
{
    return this->condBlock;
}

llvm::BasicBlock* WhileBlock::getBodyBlock() const
{
    return this->bodyBlock;
}

llvm::BasicBlock* WhileBlock::getEndBlock() const
{
    return this->endBlock;
}

void WhileBlock::setCondBlock(llvm::BasicBlock *block)
{
    this->condBlock = block;
}

void WhileBlock::setBodyBlock(llvm::BasicBlock *block)
{
    this->bodyBlock = block;
}

void WhileBlock::setEndBlock(llvm::BasicBlock *block)
{
    this->endBlock = block;
}