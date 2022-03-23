#include "ast.hpp"

#include <cassert>

void IndicesStackInvalidateIndex(IndicesStack* s, u8 idx) {
	for(u8 i = idx; i < s->top - 1; i++) {
		s->stack[i] = s->stack[i + 1];
	}
	
	s->top = s->top - 1;
}

void IndicesStackPush(IndicesStack* s, u8 v) {
	assert(s->top < s->capacity);
 
	s->stack[s->top++] = v;
}

u8 IndicesStackPop(IndicesStack* s) {
	assert(s->top > 0);

	return s->stack[--s->top];
}

void InitializeIndicesStack(IndicesStack *s) {
	s->top = 0;
}

void InitializeASTNodeBucket(ASTNodeBucket* t) {
	InitializeIndicesStack(&t->fragIndices);

	t->top  = 0;
}

void InitializeASTDataBucket(ASTDataBucket* t) {
	InitializeIndicesStack(&t->fragIndices);

	t->top  = 0;
}

void ASTAllocateNodeBucket(AST* a) {
	ASTNodeBucket* t = (ASTNodeBucket*)malloc(sizeof(ASTNodeBucket));

	InitializeASTNodeBucket(t);
	
	a->node_buckets.push_back(t);
}

void ASTAllocateDataBucket(AST* a) {
	ASTDataBucket* t = (ASTDataBucket*)malloc(sizeof(ASTDataBucket));

	InitializeASTDataBucket(t);

	a->data_buckets.push_back(t);
}

ASTNodeKey ASTAllocateNode(AST *a) {
	// TODO
}

void ASTDeallocateNode(ASTNodeKey k) {
	// TODO
}


AST *CreateAST() {
	AST* a = (AST*)malloc(sizeof(AST));

	ASTAllocateNodeBucket(a);
	ASTAllocateDataBucket(a);
	
	return a;
}

