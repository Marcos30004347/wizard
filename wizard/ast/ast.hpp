
#include "utils/config.hpp"
#include "utils/types.hpp"

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
  AST_VARIABLE,              // Tag for variable types — x, y, z
  AST_LAMBDA_ABSTRACTION,    // Tag for lambda abstraction — λx:α.term
  AST_LAMBDA_ARG_BINDING,    // Tag for lambda abstraction arguments — λx:α
  AST_LAMBDA_APPLICATION,    // Tag for lambda applications — x y
  AST_DEPENDENT_PI_TYPE,     // Tag for dependent pi types — Πx:α.β
  AST_TYPE_VARIABLE,         // Tag for type variables — α, β, γ
  AST_VARIABLE_TYPE_BINDING, // Tag for type assignments — x : α
  AST_LET_ASSIGNMENT,        // Tag for untyped let assignments — let x := term

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

struct IndicesStack {
	// Maximum capacity of the stack.
	const static u8 capacity = 32;

	// Top indice of the stack.
	u8 top = 0;

	// Stack data.
	u8 stack[capacity];
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
  ASTDataKey childs_key[capacity];

	// Stack of free indices between 0 and top.
  IndicesStack fragIndices;
};

struct ASTDataBucket {
  // Maximum Nodes on bucket.
  const static u8 capacity = 32;

	// Current NodeData's allocated on this bucket.
	u8 top = 0;
	
  // Array of data for Nodes.
  ASTNodeData data[capacity];

	// Stack of free indices between 0 and top.
	IndicesStack fragIndices;
};

struct AST {
	// ast node buckets array.
	std::vector<ASTNodeBucket*> node_buckets;

	// ast data buckets array.
	std::vector<ASTDataBucket*> data_buckets;
};

AST *CreateAST();

void DestroyAST(AST *ast);

ASTNodeData GetASTNodeData(AST *tree, ASTNodeKey key);

ASTNodeKey CreateVariableNode(AST *tree, ASTNodeInfo info);

ASTNodeKey CreateLetAssignmentNode(AST* tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey term);

ASTNodeKey CreateVariableTypeBinding(AST *tree, ASTNodeInfo indo, ASTNodeKey var, ASTNodeInfo type);

ASTNodeKey CreateLambdaAbstractionNode(AST *tree, ASTNodeInfo info, ASTNodeKey arg_binding, ASTNodeKey body);

ASTNodeKey CreateLambdaArgumentBindingNode(AST *tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey type);

ASTNodeKey CreateLambdaApplicationNode(AST *tree, ASTNodeInfo info, ASTNodeKey lambda, ASTNodeKey argument);



