//
// Created by SasakiKai on 2018/02/10.
//

#ifndef MYBF_COMPILER_H
#define MYBF_COMPILER_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "lexer.h"
#include "while_block.h"


static llvm::LLVMContext TheContext;

class Compiler
{
public:
    explicit Compiler();

    void compile(std::vector<Token> tokens);

    ~Compiler();

private:
    int memtotal = 3000;
    llvm::Module* module;
    llvm::Function *brainF;
    llvm::Function *getChar;
    llvm::Function *putChar;
    llvm::IRBuilder<>* builder;
    llvm::Value* ptr;
    llvm::Value* data;

    WhileBlock* whilePtr;
    WhileBlock whileBlocks[1000];

    void initModule();
    void addBrainF(std::vector<Token> tokens);

    void emitIncPtr();
    void emitDecPtr();
    void emitInc();
    void emitDec();
    void emitWhileStart(int index);
    void emitWhileEnd(int index);
    void emitPut();
    void emitGet();
    void addMain();
};


#endif //MYBF_COMPILER_H
