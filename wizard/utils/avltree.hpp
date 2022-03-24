#include <stdlib.h>
#include "types.hpp"

using namespace std;

template<typename T>
class AVLTree {
public:
  T key;

	AVLTree *left;
  AVLTree *right;

	i32 height;
};

inline i32 max(i32 a, i32 b) {
	return a > b ? a : b;
}

template<typename T>
i32 height(AVLTree<T> *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

template<typename T>
AVLTree<T> *CreateAVLTreeNode(T key) {
  AVLTree<T> *node = new AVLTree<T>();

	node->key    = key;
  node->left   = NULL;
  node->right  = NULL;
  node->height = 1;  

	return node;
}

template<typename T>
AVLTree<T> *rightRotate(AVLTree<T> *y) {
  AVLTree<T> *x = y->left;
  AVLTree<T> *z = x->right;

  x->right = y;
  y->left  = z;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

template<typename T>
AVLTree<T> *leftRotate(AVLTree<T> *x) {
  AVLTree<T> *y = x->right;
  AVLTree<T> *z = y->left;

  y->left  = x;
  x->right = z;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

template<typename T>
i32 getBalance(AVLTree<T> *N) {
  if (N == NULL) {
    return 0;
	}
	
  return height(N->left) - height(N->right);
}

template<typename T>
AVLTree<T> *InsertAVLTreeNode(AVLTree<T> *node, T key) {
  if (node == NULL) {
    return CreateAVLTreeNode(key);
	}
	
  if (key < node->key) {
    node->left = InsertAVLTreeNode(node->left, key);
  } else if (key > node->key) {
    node->right = InsertAVLTreeNode(node->right, key);
  } else {
    return node;
	}
	
  node->height = 1 + max(height(node->left), height(node->right));

  i32 balance = getBalance(node);

  if (balance > 1 && key < node->left->key) {
    return rightRotate(node);
	}

  if (balance < -1 && key > node->right->key) {
    return leftRotate(node);
	}

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

template<typename T>
AVLTree<T> *minValueNode(AVLTree<T> *node) {
  AVLTree<T> *current = node;

  while (current->left != NULL) {
    current = current->left;
	}

  return current;
}

template<typename T>
AVLTree<T> *DeleteAVLTreeNode(AVLTree<T> *root, T key) {
  if (root == NULL) {
    return root;
	}

  if (key < root->key) {
    root->left = DeleteAVLTreeNode(root->left, key);
	} else if (key > root->key) {
    root->right = DeleteAVLTreeNode(root->right, key);
	} else {
    if ((root->left == NULL) || (root->right == NULL)) {
      AVLTree<T> *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
			}
			
      free(temp);
    } else {
      AVLTree<T> *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = DeleteAVLTreeNode(root->right, temp->key);
    }
  }

  if (root == NULL) {
    return root;
	}

  root->height = 1 + max(height(root->left), height(root->right));

	i32 balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
	}

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
	}

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}
