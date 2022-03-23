
#include "utils/config.hpp"
#include "utils/types.hpp"

#include "parser/lexer.hpp"

#include <stack>
#include <vector>

struct ASTNodeKey {
  u32 index;
  u32 bucket;
};

struct ASTDataKey {
  u32 index;
  u32 bucket;
};

enum ASTTag {
  AST_VARIABLE,             // Tag for variable types — x, y, z
  AST_LAMBDA_ABSTRACTION,   // Tag for lambda abstraction — λx:α.term
  AST_LAMBDA_ARG_BINDING,   // Tag for lambda abstraction arguments — λx:α
  AST_LAMBDA_APPLICATION,   // Tag for lambda applications — x y
  AST_DEPENDENT_PI_TYPE,    // Tag for dependent pi types — Πx:α.β
  AST_TYPE_VARIABLE,        // Tag for type variables — α, β, γ
  AST_TYPE_ASSIGNMENT,      // Tag for type assignments — x : α
  AST_LET_ASSIGNMENT, // Tag for untyped let assignments — let x := term

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
  const static u32 size = 256;

  // Array of Tags for Nodes.
  ASTTag tag[size];

  // Array of info for Nodes.
  ASTNodeInfo info[size];

  // Array of data keys for Nodes.
  // this is a key to the 'data_bucket'
  // on the main AST data structure.
  ASTDataKey childs_key[size];
};

struct ASTDataBucket {
  // Maximum Nodes on bucket.
  const static u32 size = 256;

  // Array of data for Nodes.
  ASTNodeData data[size];
};

struct AST {
  // Vector with the bucket of Nodes.
  std::vector<ASTNodeBucket> nodes_bucket;

  // Vector with the bucket of data for Nodes.
  std::vector<ASTDataBucket> data_bucket;

  // Index of the Root of the Tree.
  ASTNodeKey root;

  // Stack with free ASTNodeKey that
  // can be used for allocating new
  // nodes.
  std::stack<ASTNodeKey> freeNode;

  // Stack with free ASTDataKey that
  // can be used for allocating new
  // node data.
  std::stack<ASTDataKey> freeData;
};

AST *CreateAST();

void DestroyAST(AST *ast);

ASTNodeData GetASTNodeData(AST *tree, ASTNodeKey key);

ASTNodeKey CreateVariableNode(AST *tree, ASTNodeInfo info);

ASTNodeKey CreateLetAssignment(AST* tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey term);

ASTNodeKey CreateLambdaAbstraction(AST *tree, ASTNodeInfo info, ASTNodeKey arg_binding, ASTNodeKey body);

ASTNodeKey CreateLambdaArgumentBinding(AST *tree, ASTNodeInfo info, ASTNodeKey var, ASTNodeKey type);

ASTNodeKey CreateLambdaApplication(AST *tree, ASTNodeInfo info, ASTNodeKey lambda, ASTNodeKey argument);



