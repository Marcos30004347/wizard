#include "ast.hpp"

#include <cassert>
#include <cmath>
#include <cstddef>


void InitializeASTNodeBucket(ASTNodeBucket* t) {
	t->top  = 0;
}

void InitializeASTDataBucket(ASTDataBucket* t) {
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
	// Get a new node at the end of the nodes buckets.
	u32 bucket = a->node_buckets.size() - 1;

	ASTNodeBucket* b = a->node_buckets[bucket];
	
	if(b->top == b->capacity) {
		ASTAllocateNodeBucket(a);

		bucket = a->node_buckets.size() - 1;

		b = a->node_buckets[bucket];
	}
	
	ASTNodeKey key;

	key.bucket = bucket;
	key.index  = b->top;

	return key;
}

ASTDataKey ASTAllocateData(AST *a) {
	// Get a new node at the end of the nodes buckets.
	u32 bucket = a->node_buckets.size() - 1;

	ASTDataBucket* b = a->data_buckets[bucket];
	
	if(b->top == b->capacity) {
		ASTAllocateDataBucket(a);

		bucket = a->data_buckets.size() - 1;

		b = a->data_buckets[bucket];
	}
	
	ASTDataKey key;

	key.bucket = bucket;
	key.index  = b->top;

	return key;
}


AST *CreateAST() {
	AST* a = (AST*)malloc(sizeof(AST));

	ASTAllocateNodeBucket(a);
	ASTAllocateDataBucket(a);
	
	return a;
}

void DestroyAST(AST *ast) {
	for(u32 i = 0; i < ast->node_buckets.size(); i++) {
		free(ast->node_buckets[i]);
	}

	for(u32 i = 0; i < ast->data_buckets.size(); i++) {
		free(ast->data_buckets[i]);
	}
	
  delete ast;
}

ASTNodeData GetASTNodeData(AST *tree, ASTNodeKey k) {
	assert(tree->node_buckets[k.bucket]->top < k.index);
	ASTDataKey d = tree->node_buckets[k.bucket]->data[k.index];

	assert(tree->data_buckets[d.bucket]->top < d.index);
	return tree->data_buckets[d.bucket]->data[d.index];
}

ASTTag GetASTNodeTag(AST* tree, ASTNodeKey key) {
	assert(tree->node_buckets[key.bucket]->top < key.index);
	return tree->node_buckets[key.bucket]->tag[key.index];
}

ASTNodeKey CreateVariableNode(AST *tree, ASTNodeInfo info){
	ASTNodeKey key = ASTAllocateNode(tree);

	ASTNodeBucket* b = tree->node_buckets[key.bucket];

	b->tag[key.index] = ASTTag::AST_VARIABLE;
	b->info[key.index] = info;
	
	return key;
}

ASTNodeKey CreateLetAssignmentNode(AST* tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey term) {
	ASTNodeKey nkey = ASTAllocateNode(tree);
	ASTDataKey dkey = ASTAllocateData(tree);

	ASTNodeBucket* nb = tree->node_buckets[nkey.bucket];
	ASTDataBucket* db = tree->data_buckets[dkey.bucket];

	nb->tag[nkey.index] = ASTTag::AST_LET_ASSIGNMENT;

	nb->info[nkey.index] = info;
	nb->data[nkey.index] = dkey;
	
	db->data[dkey.index].left_child  = var;
	db->data[dkey.index].right_child = term;
	
	return nkey;
}

ASTNodeKey CreateTypeBindingNode(AST* tree, ASTNodeInfo info, ASTNodeKey term, ASTNodeKey type) {
	ASTNodeKey nkey = ASTAllocateNode(tree);
	ASTDataKey dkey = ASTAllocateData(tree);

	ASTNodeBucket* nb = tree->node_buckets[nkey.bucket];
	ASTDataBucket* db = tree->data_buckets[dkey.bucket];

	nb->tag[nkey.index] = ASTTag::AST_TYPE_BINDING;

	nb->info[nkey.index] = info;
	nb->data[nkey.index] = dkey;
	
	db->data[dkey.index].left_child = term;
	db->data[dkey.index].right_child = type;
	
	return nkey;
}

ASTNodeKey CreateLambdaAbstractionNode(AST* tree, ASTNodeInfo info, ASTNodeKey arg, ASTNodeKey body) {
	ASTNodeKey nkey = ASTAllocateNode(tree);
	ASTDataKey dkey = ASTAllocateData(tree);

	ASTNodeBucket* nb = tree->node_buckets[nkey.bucket];
	ASTDataBucket* db = tree->data_buckets[dkey.bucket];

	nb->tag[nkey.index] = ASTTag::AST_LAMBDA_ABSTRACTION;

	nb->info[nkey.index] = info;
	nb->data[nkey.index] = dkey;
	
	db->data[dkey.index].left_child = arg;
	db->data[dkey.index].right_child = body;
	
	return nkey;
}

ASTNodeKey CreateLambdaApplicationNode(AST* tree, ASTNodeInfo info, ASTNodeKey lamda, ASTNodeKey arg) {
	ASTNodeKey nkey = ASTAllocateNode(tree);
	ASTDataKey dkey = ASTAllocateData(tree);

	ASTNodeBucket* nb = tree->node_buckets[nkey.bucket];
	ASTDataBucket* db = tree->data_buckets[dkey.bucket];

	nb->tag[nkey.index] = ASTTag::AST_LAMBDA_ABSTRACTION;

	nb->info[nkey.index] = info;
	nb->data[nkey.index] = dkey;
	
	db->data[dkey.index].left_child = lamda;
	db->data[dkey.index].right_child = arg;
	
	return nkey;
}

ASTNodeKey CreateKindTypeNode(AST *tree, ASTNodeInfo info){
	ASTNodeKey key = ASTAllocateNode(tree);

	ASTNodeBucket* b = tree->node_buckets[key.bucket];

	b->tag[key.index] = ASTTag::AST_KIND_TYPE;
	b->info[key.index] = info;
	
	return key;
}

ASTNodeKey CreateVariableTypeNode(AST *tree, ASTNodeInfo info){
	ASTNodeKey key = ASTAllocateNode(tree);

	ASTNodeBucket* b = tree->node_buckets[key.bucket];

	b->tag[key.index] = ASTTag::AST_TYPE_VARIABLE;
	b->info[key.index] = info;
	
	return key;
}

ASTNodeKey CreateDependentPiTypeNode(AST* tree, ASTNodeInfo info, ASTNodeKey first, ASTNodeKey second) {
	ASTNodeKey nkey = ASTAllocateNode(tree);
	ASTDataKey dkey = ASTAllocateData(tree);

	ASTNodeBucket* nb = tree->node_buckets[nkey.bucket];
	ASTDataBucket* db = tree->data_buckets[dkey.bucket];

	nb->tag[nkey.index] = ASTTag::AST_TYPE_DEPENDENT_PI;

	nb->info[nkey.index] = info;
	nb->data[nkey.index] = dkey;
	
	db->data[dkey.index].left_child = first;
	db->data[dkey.index].right_child = second;
	
	return nkey;
}
