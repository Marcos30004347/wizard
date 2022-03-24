
#include "utils/types.hpp"

#include "utils/stack.hpp"
#include "utils/avltree.hpp"

#include "parser/lexer.hpp"

#include <stack>
#include <vector>

struct ASTNodeKey {
  u8  index;
  u32 bucket;
};

struct ASTDataKey {
  u8  index;
  u32 bucket;
};

enum ASTTag : u8 {
  // Tag for variable types — x, y, z 
  AST_VARIABLE,
	
	// Tag for lambda abstraction — λx:α.term 
  AST_LAMBDA_ABSTRACTION,
	
	// Tag for lambda applications — x y 
	AST_LAMBDA_APPLICATION,
	
	// Tag for untyped let assignments — let x := term 
  AST_LET_ASSIGNMENT,

	// Tag for dependent pi types — Πx:α.β 
  AST_TYPE_DEPENDENT_PI,

	// Tag for arrow types — α → β
	AST_TYPE_ARROW,
	
	// Tag for type variables — α, β, γ 
  AST_TYPE_VARIABLE,

	// Tag for type assignments — x : α 
  AST_TYPE_BINDING,

	// Tag for sort of types — * 
	AST_KIND_TYPE,
	
  // Utils
  AST_UTIL_LIST,      // Tag for internal use, represent lists of Nodes.

  AST_UTIL_LIST_END,  // Tag for internal use, represent the end of a list.
};

struct ASTNodeInfo {
  // Key to the token of the ASTNode
  TokenKey root_token;
};

struct ASTNodeData {
  // Left operand of node.
  ASTNodeKey left_child;

  // Right operand of node.
  ASTNodeKey right_child;
};


struct ASTNodeBucket {
  // Maximum Nodes on bucket.
  const static u8 capacity = 32;

	// Current Nodes allocated on this bucket.
	u8 top = 0;

  // Array of Tags for Nodes.
  ASTTag tag[capacity];

  // Array of info for Nodes.
  ASTNodeInfo info[capacity];

  // Array of data keys for Nodes.
  // this is a key to the 'data_bucket'
  // on the main AST data structure.
  ASTDataKey data[capacity];
};

struct ASTDataBucket {
  // Maximum Nodes on bucket.
  const static u8 capacity = 32;

	// Current NodeData's allocated on this bucket.
	u8 top = 0;
	
  // Array of data for Nodes.
  ASTNodeData data[capacity];
};

struct AST {
	// NOTE(marcos): Maybe it will be better to
	// use a self balaned binary tree to store
	// the buckets internally.

	// ast node buckets array.
	std::vector<ASTNodeBucket*> node_buckets;

	// ast data buckets array.
	std::vector<ASTDataBucket*> data_buckets;
};

AST *CreateAST();

void DestroyAST(AST *ast);

ASTNodeData GetASTNodeData(AST *tree, ASTNodeKey key);

ASTTag GetASTNodeTag(AST* tree, ASTNodeKey key);

ASTNodeKey CreateVariableNode(AST *tree, ASTNodeInfo info);

ASTNodeKey CreateLetAssignmentNode(AST* tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey term);

ASTNodeKey CreateTypeBindingNode(AST *tree, ASTNodeInfo indo, ASTNodeKey term, ASTNodeInfo type);

ASTNodeKey CreateLambdaAbstractionNode(AST *tree, ASTNodeInfo info, ASTNodeKey arg, ASTNodeKey body);

ASTNodeKey CreateLambdaApplicationNode(AST *tree, ASTNodeInfo info, ASTNodeKey lambda, ASTNodeKey argument);

ASTNodeKey CreateKindTypeNode(AST *tree, ASTNodeInfo info);

ASTNodeKey CreateDependentPiTypeNode(AST *tree, ASTNodeInfo info, ASTNodeKey first, ASTNodeKey second);

ASTNodeKey CreateVariableTypeNode(AST *tree, ASTNodeInfo info);
