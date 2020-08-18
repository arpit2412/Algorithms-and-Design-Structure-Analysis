/*
Name: Arpit Garg
ADSA Assignment 2
Task:
Binary Tree Traversal
AVL Tree Insertion and Deletion
ID: A1784072
 */
// Importing all the required header files and clang is used for formatting
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
/*creating structure node which contains data and height. Data contains the
value in the node
and height contains the height of the node. Left and right are the nodes. */
struct Node {
  int data;
  int height;
  Node *left;
  Node *right;
} * root;
// Creating separate class for AVL Trees
class AvlTrees {
public:
  // default constructor
  AvlTrees() { root = NULL; }
  struct Node *insert(Node *, int);  // Insert declaration
  struct Node *remove(Node *, int);  // Remove declaration
  struct Node *rotate_Right(Node *); // Rotation right declaration
  struct Node *rotate_Left(Node *);  // Rotation left declaration
  struct Node *leftMax(Node *);      // Left maximum declaration
  void preorder(Node *);             // Preorder display declaration
  void inorder(Node *);              // Inorder display declaration
  void postorder(Node *);            // Postorder display declaration
  int blncFactor(Node *);            // Balance factor declaration
  int height(Node *);                // Find Height declaration
  void setHeight(Node *);            // Set Height declaration
};
// Inorder definition
void AvlTrees::inorder(Node *nodes) {
  if (nodes == NULL) // if node is NULL then return
  {
    return;
  } else // if not null then inorder traversal (left,root,right)
  {
    inorder(nodes->left);
    std::cout << nodes->data << "  ";
    inorder(nodes->right);
  }
}
// Preorder definition
void AvlTrees::preorder(Node *nodes) {
  if (nodes == NULL) // if node is null return
  {
    return;
  } else // if node is not null then preorder traversal(root,left,right)
  {
    std::cout << nodes->data << "  ";
    preorder(nodes->left);
    preorder(nodes->right);
  }
}
// Postorder definition
void AvlTrees::postorder(Node *nodes) {
  if (nodes == NULL) // if node is null return
  {
    return;
  } else // if node is not null then postorder traversal(left,right,root)
  {
    postorder(nodes->left);
    postorder(nodes->right);
    std::cout << nodes->data << "  ";
  }
}
// return the height of the node
int AvlTrees::height(Node *node) { return (node == NULL) ? 0 : node->height; }
// return the balancing factor of the node
int AvlTrees::blncFactor(Node *node) {
  return (node == NULL) ? 0 : (height(node->left) - height(node->right));
}
// find the largest in the left side of the node (used in remove)
Node *AvlTrees::leftMax(Node *node) {
  Node *temp = node;
  while (temp->right != NULL) {
    temp = temp->right;
  }
  return temp;
}
// set the updated height
void AvlTrees::setHeight(Node *node) {
  if (node != NULL || node->left != NULL || node->right != NULL) {
    int temp = std::max(height(node->left), height(node->right));
    node->height = 1 + temp;
  }
}
// rotate the tree right
Node *AvlTrees::rotate_Right(Node *node) {
  Node *left_node;      // creating new node
  Node *leftRight_node; // creating new node
  left_node = node->left;
  leftRight_node = left_node->right;
  left_node->right = node;
  node->left = leftRight_node;
  setHeight(node);      // set the new height
  setHeight(left_node); // set the new height
  return left_node;     // return the node
}
// rotate the tree left
Node *AvlTrees::rotate_Left(Node *node) {
  Node *right_node;     // creating new node
  Node *rightleft_node; // creating new node
  right_node = node->right;
  rightleft_node = right_node->left;
  right_node->left = node;
  node->right = rightleft_node;
  setHeight(node);       // set the new height
  setHeight(right_node); // set the new height
  return right_node;     // return the node
}
// Insert the new node definition
Node *AvlTrees::insert(Node *node, int data) {
  if (node == NULL) // if tree is empty then it will create a new node
  {
    node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
  } else if (data < node->data) { // if value is smaller then it will added to left
    node->left = insert(node->left, data);
  }

  else if (data > node->data) { // if value is larger then it will added to right
    node->right = insert(node->right, data);
  } else {
    return node; // return node
  }

  if (node != NULL) {
    setHeight(node); // setting height
  }
  int balance = blncFactor(node); // calculating the balancing factor
  if (balance > 1)                // if balancing factor is larger then 1
  {
    if (data < node->left->data) // left imbalance
    {
      return rotate_Right(node);
    }
    if (data > node->left->data) // left-right imbalance
    {
      node->left = rotate_Left(node->left); // left rotate
      return rotate_Right(node);
    }
  }
  if (balance < -1) // if balancing factor is less than 1
  {
    if (data > node->right->data) // right imbalance
    {
      return rotate_Left(node);
    }
    if (data < node->right->data) // right-left imbalance
    {
      node->right = rotate_Right(node->right); // right rotate
      return rotate_Left(node);
    }
  }
  return node;
}
// Delete the node definition
Node *AvlTrees::remove(Node *node, int data) {
  if (node == NULL) // if node is null then return
  {
    return node;
  }
  // locate the value need to be deleted if its less then current value moveleft
  // otherwise right
  if (data < node->data) {
    node->left = remove(node->left, data);
  } else if (data > node->data) {
    node->right = remove(node->right, data);
  } else if (data == node->data) // if the node has only one child
  {
    if (node->left == NULL && node->right == NULL) {
      node = NULL;
    } else if (node->left == NULL) {
      if (node->right != NULL) {
        node = node->right;
      }
    } else if (node->right == NULL) {
      if (node->left != NULL) {
        node = node->left;
      }
    } else // if the node has two children swap with largest on left
    {
      Node *temp = leftMax(node->left);
      node->data = temp->data;
      node->left = remove(node->left, temp->data);
    }
  }
  if (node != NULL) // setting the height
  {
    setHeight(node);
  }
  int balance = blncFactor(node); // calculating the balance factor
  if (balance > 1)                // balancing factor greater than 1
  {
    if (blncFactor(node->left) >= 0) // left imbalance
    {
      return rotate_Right(node);
    }
    if (blncFactor(node->left) < 0) // right-left imabalnce
    {
      node->left = rotate_Left(node->left);
      return rotate_Right(node);
    }
  }
  if (balance < -1) // balancing factor less than 1
  {
    if (blncFactor(node->right) <= 0) // right imbalance
    {
      return rotate_Left(node);
    }
    if (blncFactor(node->right) > 0) // left-right imbalance
    {
      node->right = rotate_Right(node->right);
      return rotate_Left(node);
    }
  }
  return node;
}
// Main function
/*A different approach is used for entering the elements to make the program
more generalised Steps: 1:Input is taken using inline 2:According to spaces
between them all are added to vector 3: Now in vector if first char is
A(case-insensitive) then insert or if D(case-insensitive) then remove is called
4. Then value at last vector is observed and to ignore the multichar warning
second char is compared if IN then N if PRE then R if POST then O
5. Return 0
END*/
int main(int argc, char const *argv[]) {
  AvlTrees tree;           // object of class so default constructor empty tree
  std::vector<char *> vec; // creating vector
  char data[1000];
  std::cin.getline(data, 1000);           // taking input
  char *token_arrays = strtok(data, " "); // dividing input separated by spaces
  while (token_arrays) {
    vec.push_back(token_arrays); // adding each separated by spaces to vector
    token_arrays = strtok(NULL, " ");
  }
  for (auto it = vec.begin(); it != vec.end() - 1;
       ++it) // checking for first character
  {
    if (it[0][0] == 'a' || it[0][0] == 'A') // if 'a' or 'A' then insert
    {
      for (unsigned int i = 1; i <= strlen(it[0]); i++) 
      //'A' or 'a' is removed and now it only contain integer
      {
        it[0][i - 1] = it[0][i];
      }
      root = tree.insert(root, atoi(it[0]));       // insert function called
    } else if (it[0][0] == 'd' || it[0][0] == 'D') // if 'd' or 'D' then delete
    {
      for (unsigned int i = 1; i <= strlen(it[0]); i++)
       //'D' or 'd' is removed and now it only contain integer
      {
        it[0][i - 1] = it[0][i];
      }
      root = tree.remove(root, atoi(it[0])); // remove function called
    }
  }
  auto last =
      vec.at(vec.size() - 1);
         // considering the last input word to traverse accordingly
  switch (last[1]) // second character of word is considered
  {
  case 'N':
    if (root == NULL) // if INORDER then second char is N
    {
      std::cout << "EMPTY"; // if no element print EMPTY
    } else {
      tree.inorder(root);
    }
    break;
  case 'R':
    if (root == NULL) // if PREORDER then second char is R
    {
      std::cout << "EMPTY"; // if no element print EMPTY
    } else {
      tree.preorder(root);
    }
    break;
  case 'O':
    if (root == NULL) // if POSTORDER then second char is O
    {
      std::cout << "EMPTY"; // if no element print EMPTY
    } else {
      tree.postorder(root);
    }
    break;
  }
  return 0;
}