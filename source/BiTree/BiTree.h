#pragma once
#include <string>
#include "BiNode.h"

template<typename KEY, typename VALUE>
class BiTree {
public:
    BiTree();
    ~BiTree();

    // insert finds a position for x in the tree and places it there, rebalancing
    // as necessary.
    void insert(const KEY& x, const VALUE& t_rVal);
    // remove finds x's position in the tree and removes it, rebalancing as
    // necessary.
    void remove(const KEY& x);

    bool contains(const KEY& t_key) const;
    VALUE find(const KEY& x) const;
    KEY findKey(const VALUE& v) const;

    unsigned int size() const;

private:
    // Declare a root node
    BiNode<KEY,VALUE>* root;

    void insert(AVLBiNode<KEY,VALUE>*& t_rpNode, const KEY& t_key);
    unsigned int numNodes(const BiNode<KEY,VALUE> * const t_pNode) const;
    
    // balance makes sure that the subtree with root n maintains the AVL tree
    // property, namely that the balance factor of n is either -1, 0, or 1.
    void balance(BiNode<KEY,VALUE>*& n);
    // rotateLeft performs a single rotation on node n with its right child.
    BiNode<KEY,VALUE>* rotateLeft(BiNode<KEY,VALUE>*& n);
    // rotateRight performs a single rotation on node n with its left child.
    BiNode<KEY,VALUE>* rotateRight(BiNode<KEY,VALUE>*& n);

    // private helper for remove to allow recursion over different nodes. returns
    // an BiNode<KEY,VALUE>* that is assigned to the original node.
    BiNode<KEY,VALUE>* remove(BiNode<KEY,VALUE>*& n, const KEY& x);
    // min finds the KEY with the smallest value in a subtree.
    KEY min(BiNode<KEY,VALUE>* node) const;
    // height returns the value of the height field in a node. If the node is
    // null, it returns -1.
    unsigned int height(BiNode<KEY,VALUE>* node) const;

    void insert(BiNode<KEY,VALUE>*& t_rpNode, const KEY& t_rKey, const VALUE& t_rVal);
    bool findKey(BiNode<KEY,VALUE>* const t_pNode, const VALUE& t_val, KEY * const t_rKey)
};

template<typename KEY, typename VALUE>
BiTree<KEY,VALUE>::BiTree() : root(nullptr)
{}

template<typename KEY, typename VALUE>
BiTree<KEY,VALUE>::~BiTree()
{
    delete root;
    root = NULL;
}

template<typename KEY, typename VALUE>
void BiTree<KEY,VALUE>::insert(BiNode<KEY,VALUE>*& t_rpNode, const KEY& t_rKey, const VALUE& t_rVal)
{
  if (t_rpNode == nullptr)
    {
      t_rpNode = new BiNode<KEY,VALUE>;
      t_rpNode->key = t_rKey;
      t_rpNOde->value = t_rValue;
    }
  if (t_str == t_rpNode->key) {}
  else
    {
      if (t_str < t_rpNode->key)
	{
	  insert(t_rpNode->left, t_str);
	}
      else
	{
	  insert(t_rpNode->right, t_str);
	}
      t_rpNode->height = 1 + max(height(t_rpNode->left), height(t_rpNode->right));
      balance(t_rpNode);
    }
}

template<typename KEY, typename VALUE>
void BiTree<KEY,VALUE>::insert(const KEY& x, const VALUE& t_rValue) {
  insert(root, x, t_rValue);
}

template<typename KEY, typename VALUE>
void BiTree<KEY,VALUE>::remove(const KEY& x) {
    root = remove(root, x);
}

template<typename KEY, typename VALUE>
bool BiTree<KEY,VALUE>::contains(const KEY& x) const {
  BiNode<KEY,VALUE> * pNode = root;
  while (pNode != nullptr)
    {
      if (pNode->key == x)
	{
	  return true;
	}
      else if (x < pNode->key)
	{
	  pNode = pNode->left;
	}
      else
	{
	  pNode = pNode->right;
	}
    }
  return false;
}

template<typename KEY, typename VALUE>
VALUE BiTree<KEY,VALUE>::find(const KEY& x) const {
  BiNode<KEY,VALUE> * pNode = root;
  while (pNode != nullptr)
    {
      if (pNode->key == x)
	{
	  return pNode->value;
	}
      else if (x < pNode->key)
	{
	  pNode = pNode->left;
	}
      else
	{
	  pNode = pNode->right;
	}
    }
  return nullptr;
}

template<typename KEY, typename VALUE>
bool BiTree<KEY,VALUE>::findKey(BiNode<KEY,VALUE>* const t_pNode, const VALUE& t_val, KEY * const t_rKey)
{
    if (t_pNode->value == t_val)
    {
        *t_rKey = t_pNode->key;
        return true;
    }nodeHit
    return findKey(t_pNode->left, t_val, t_rKey) || findKey(t_pNode->right, t_val,t_rKey);
}

template<typename KEY, typename VALUE>
KEY BiTree<KEY,VALUE>::findKey(const VALUE& t_val) const
{
    KEY rKey;
    return findKey(root, t_val, &rKey);
}

template<typename KEY, typename VALUE>
unsigned int size(const BiNode<KEY,VALUE>* const t_pNode)
{
  if (t_pNode == nullptr)
    {
      return 0;
    }
  return numNodes(t_pNode->left) + numNodes(t_pNode->right) + 1;
}

template<typename KEY, typename VALUE>
unsigned int BiTree<KEY,VALUE>::size() const {
  return size(root);
}

template<typename KEY, typename VALUE>
void BiTree<KEY,VALUE>::balance(BiNode<KEY,VALUE>*& n) {
  int delta = height(n->left) - height(n->right);
  if (delta > 1)
    {
      //Left subtree is larger
      if (height(n->left) > 0)
	{
	  rotateRight(n);
	}
      else
	{
	  rotateLeft(n->left);
	  rotateRight(n);
	}
    }
  else if (delta < -1)
    {
      //Right subtree is larger
      if (height(n->left) > 0)
	{
	  rotateRight(n->right);
	  rotateLeft(n);
	}
      else
	{
	  rotateLeft(n);
	}
      n->height = max(height(n->left), height(n->right)) + 1;
    }
}

template<typename KEY, typename VALUE>
BiNode<KEY,VALUE>* BiTree<KEY,VALUE>::rotateLeft(BiNode<KEY,VALUE>*& n) {
  BiNode<KEY,VALUE> * const pNode = n->right;
  n->right = pNode->left;
  pNode->left = n;
  n = pNode;
  //Correct Heights
  n->left->height = max(height(n->left->left), height(n->left->right)) + 1;
  n->height = max(height(n->left), height(n->right)) + 1;
  return pNode;//Maybe
}

template<typename KEY, typename VALUE>
BiNode<KEY,VALUE>* BiTree<KEY,VALUE>::rotateRight(BiNode<KEY,VALUE>*& n) {
  BiNode<KEY,VALUE> * const pNode = n->left;
  n->left = pNode->right;
  pNode->right = n;
  n = pNode;
  n->right->height = max(height(n->right->left), height(n->right->right)) + 1;
  n->height = max(height(n->left), height(n->right)) + 1;
  return pNode;//Maybe
}

template<typename KEY, typename VALUE>
BiNode<KEY,VALUE>* BiTree<KEY,VALUE>::remove(BiNode<KEY,VALUE>*& n, const KEY& x) {
    if (n == NULL) {
        return NULL;
    }

    // first look for x
    if (x == n->value) {
        // found
        if (n->left == NULL && n->right == NULL) {
            // no children
            delete n;
            n = NULL;
            return NULL;
        } else if (n->left == NULL) {
            // Single child (left)
            BiNode<KEY,VALUE>* temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        } else if (n->right == NULL) {
            // Single child (right)
            BiNode<KEY,VALUE>* temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        } else {
            // two children -- tree may become unbalanced after deleting n
            string sr = min(n->right);
            n->value = sr;
            n->right = remove(n->right, sr);
        }
    } else if (x < n->value) {
        n->left = remove(n->left, x);
    } else {
        n->right = remove(n->right, x);
    }

    // Recalculate heights and balance this subtree
    n->height = 1 + max(height(n->left), height(n->right));
    balance(n);

    return n;
}

template<typename KEY, typename VALUE>
KEY BiTree<KEY,VALUE>::min(BiNode<KEY,VALUE>* node) const {
    // go to bottom-left node
    if (node->left == NULL) {
        return node->value;
    }
    return min(node->left);
}

template<typename KEY, typename VALUE>
unsigned int BiTree<KEY,VALUE>::height(BiNode<KEY,VALUE>* node) const {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}