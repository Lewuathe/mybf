//
// Created by SasakiKai on 2018/02/10.
//

#include "compiler.h"

using namespace llvm;

Compiler::Compiler()
{
    initModule();
}

Compiler::~Compiler()
{
//    if (module != nullptr) free(module);
}

void Compiler::initModule()
{
    module = new llvm::Module("mybf", TheContext);
}

void Compiler::compile(std::vector<Token> tokens)
{
    addBrainF(tokens);

    addMain();

    module->print(llvm::outs(), nullptr);
}

void Compiler::addBrainF(std::vector<Token> tokens)
{
    getChar = cast<Function>(module->getOrInsertFunction(
            "getchar",
            IntegerType::getInt32Ty(TheContext)));

    putChar = cast<Function>(module->getOrInsertFunction(
            "putchar",
            IntegerType::getInt32Ty(TheContext),
            IntegerType::getInt32Ty(TheContext)
    ));

    brainF = cast<Function>(module->getOrInsertFunction(
            "brainf",
            Type::getVoidTy(TheContext)));

    builder = new IRBuilder<>(BasicBlock::Create(TheContext, "brainf.0", brainF));
    BasicBlock *bb = builder->GetInsertBlock();

    data = builder->CreateAlloca(builder->getInt8PtrTy(), nullptr, "data");
    ptr = builder->CreateAlloca(builder->getInt8PtrTy(), nullptr, "ptr");

    Function* funcCalloc = cast<Function>(module->getOrInsertFunction(
            "calloc",
            builder->getInt8PtrTy(),
            builder->getInt64Ty(), builder->getInt64Ty()
    ));

    Value* dataPtr = builder->CreateCall(
            funcCalloc,
            {builder->getInt64(3000), builder->getInt64(1)});


    builder->CreateStore(dataPtr, data);
    builder->CreateStore(dataPtr, ptr);

    int whileIndex = 0;
    whilePtr = whileBlocks;

    for (auto t : tokens) {
        switch (t) {
            case Token::tok_inc_pointer:
                emitIncPtr();
                break;
            case Token::tok_dec_pointer:
                emitDecPtr();
                break;
            case Token::tok_inc:
                emitInc();
                break;
            case Token::tok_dec:
                emitDec();
                break;
            case Token::tok_while_start:
                emitWhileStart(whileIndex);
                whileIndex++;
                whilePtr++;
                break;
            case Token::tok_while_end:
                if (--whileIndex < 0) {
                    std::cerr << "Unmatching while clause" << std::endl;
                }
                whilePtr--;
                emitWhileEnd(whileIndex);
                break;
            case Token::tok_put:
                emitPut();
                break;
            case Token::tok_get:
                emitGet();
                break;
            default:
                break;
        }
    }


    // put new line
    builder->CreateCall(putChar, builder->getInt32(10));
    builder->CreateRetVoid();

}

void Compiler::emitIncPtr()
{
    builder->CreateStore(
            builder->CreateInBoundsGEP(
                    builder->getInt8Ty(),
                    builder->CreateLoad(ptr),
                    builder->getInt32(1)),
            ptr);
}

void Compiler::emitDecPtr()
{
    builder->CreateStore(
            builder->CreateInBoundsGEP(
                    builder->getInt8Ty(),
                    builder->CreateLoad(ptr),
                    builder->getInt32(-1)),
            ptr);
}

void Compiler::emitInc()
{
    Value *tmp = builder->CreateLoad(ptr);
    builder->CreateStore(
            builder->CreateAdd(
                    builder->CreateLoad(tmp),
                    builder->getInt8(1)),
            tmp
    );
}

void Compiler::emitDec()
{
    Value *tmp = builder->CreateLoad(ptr);
    builder->CreateStore(
            builder->CreateAdd(
                    builder->CreateLoad(tmp),
                    builder->getInt8(-1)),
            tmp
    );
}

void Compiler::emitWhileStart(int index)
{
    WhileBlock* whileBlock = whilePtr;
    whileBlock->condBlock =
            BasicBlock::Create(TheContext, "while_cond" + std::to_string(index), brainF);
    whileBlock->bodyBlock =
            BasicBlock::Create(TheContext, "while_body" + std::to_string(index), brainF);
    whileBlock->endBlock =
            BasicBlock::Create(TheContext, "while_end" + std::to_string(index), brainF);
    builder->CreateBr(whileBlock->getCondBlock());
    builder->SetInsertPoint(whileBlock->getCondBlock());
    builder->CreateCondBr(
            builder->CreateICmpNE(
                    builder->CreateLoad(builder->CreateLoad(ptr)),
                    builder->getInt8(0)),
            whileBlock->getBodyBlock(),
            whileBlock->getEndBlock()
    );
    builder->SetInsertPoint(whileBlock->getBodyBlock());
}

void Compiler::emitWhileEnd(int index)
{
    WhileBlock* whileBlock = whilePtr;
    builder->CreateBr(whileBlock->getCondBlock());
    builder->SetInsertPoint(whileBlock->getEndBlock());
}

void Compiler::emitPut()
{
    builder->CreateCall(
            putChar,
            builder->CreateSExt(
                builder->CreateLoad(builder->CreateLoad(ptr)),
                builder->getInt32Ty()
            )
    );
}

void Compiler::emitGet()
{
    builder->CreateStore(
            builder->CreateTrunc(
                    builder->CreateCall(getChar),
                    builder->getInt8Ty()),
            builder->CreateLoad(ptr));
}

void Compiler::addMain()
{

    Function *mainFunc = cast<Function>(module->getOrInsertFunction(
            "main",
            IntegerType::getInt32Ty(TheContext),
            IntegerType::getInt32Ty(TheContext),
            PointerType::getUnqual(PointerType::getUnqual(
                    IntegerType::getInt8Ty(TheContext)
            ))
    ));

    Function::arg_iterator args = mainFunc->arg_begin();
    Value *arg_0 = &*args++;
    arg_0->setName("argc");
    Value *arg_1 = &*args++;
    arg_1->setName("argv");

    BasicBlock *bb = BasicBlock::Create(TheContext, "main.0", mainFunc);

    CallInst *brainFCall = CallInst::Create(module->getFunction("brainf"), "", bb);
    brainFCall->setTailCall(false);

    ReturnInst::Create(
            module->getContext(),
            ConstantInt::get(module->getContext(), APInt(32, 42)),
            bb
    );
}

