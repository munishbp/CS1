/*COP 3502C Assignment 5
This program is written by: Munish Persaud
I want to be considered for the bonus and I agree that any of my submissions after
July 22 will not be considered for grading regardless of my score on my most recent
submission before July 22*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
  char name[25];
  int data;
  int depth;
  struct TreeNode* left;
  struct TreeNode* right;
} tree;

// function prototypes
tree* add(tree* root, tree* element, int depth);
tree* sub(tree* root, tree* element);
tree* del(tree* root, char name[]);
tree* search(tree* root, char name[]);
tree* maxVal(tree* root);
tree* parent(tree* root, char name[]);
int detLeaf(tree* node);
int onlyRight(tree* node);
int onlyLeft(tree* node);
int height(tree* root);
void height_balance(tree* root);
void print_depth(tree* root);
void update_depths(tree* root, int depth);
tree* create_node(int data, char name[]);


//if node is parent aka if it has a kid
tree* parent(tree* root, char name[]) {
  if (root == NULL || strcmp(root->name, name) == 0) {
    return NULL;
  }
  if((root->left != NULL && strcmp(root->left->name, name)==0) ||
    (root->right != NULL && strcmp(root->right->name, name)==0)) {
    return root;
  }
  tree* left_result = parent(root->left, name);
  if (left_result != NULL) {
    return left_result;
  }
  return parent(root->right, name);
}


//if node is leaf
int detLeaf(tree* node) {
  return (node->left == NULL && node->right == NULL);
}


//if node only has a left
int onlyLeft(tree* node) {
  return (node->left != NULL && node->right == NULL);
}


//if node only has a right
int onlyRight(tree* node) {
  return (node->left == NULL && node->right != NULL);
}


//deletion function that uses if leaf, parent, maxval, 1 node (right or left), or 2 node conditions
tree* del(tree* root, char name[]) {
  tree *delnode, *new_del_node, *save_node;
  tree *par;
  char save_name[25];
  int save_data;

  delnode = search(root,name);
  //if its empty
  if (delnode == NULL){
    return root;
  }  

  par = parent(root,delnode);

  //if its a leaf
  if(detLeaf(delnode)){
    if (par == NULL) {
      free(root);
      return NULL;
    }
    if(strcmp(name,par->name) < 0){
      free(par->left);
      par->left = NULL;
    } 
    else{
      free(par->right);
      par->right = NULL;
    }
      return root;
  }

  //if theres only left child
  if (onlyLeft(delnode)){
    if(par == NULL){
      save_node = delnode->left;
      free(delnode);
      return save_node;
    }
    if(strcmp(name, par->name) < 0){
      save_node = par->left;
      par->left = par->left->left;
      free(save_node);
      } 
    else{
      save_node = par->right;
      par->right = par->right->left;
      free(save_node);
    }
    return root;
  }

  //if theres only a right child
  if(onlyRight(delnode)){
    if(par == NULL){
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }
    if(strcmp(name, par->name) < 0){
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    } 
    else{
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }

  //if the node has two children
  new_del_node = maxVal(delnode->left);
  strcpy(save_name, new_del_node->name);
  save_data = new_del_node->data;

  root = del(root, save_name);

  strcpy(delnode->name, save_name);
  delnode->data = save_data;

  return root;
}


//add function. uses print depth function to actually print. every recursive call to add it properly add 1 to the depth.
//made my strcmp a variable to make if conditionals look cleaner.  
tree* add(tree* root, tree* element, int depth) {
  if(root == NULL) {
    element->depth = depth;
    print_depth(element);
    return element;
  } 
  else {
    int compare = strcmp(root->name, element->name);
    if(compare > 0){
      root->left = add(root->left, element, depth + 1);
    } 
    else if(compare < 0){
      root->right = add(root->right, element, depth + 1);
    } 
    else if(compare == 0){
      root->data += element->data;
      print_depth(root);
      free(element);
    }
  }
  return root;
}


//subtraction function. same idea with compare variable. 
tree* sub(tree* root, tree* element) {
  if(root == NULL){
    return NULL;
  } 
  int compare = strcmp(root->name, element->name);
  if(compare > 0){
      root->left = sub(root->left, element);
  } 
  else if(compare < 0){
    root->right = sub(root->right, element);
  }
  else{
    if(root->data < element->data){
      root->data = 0;
    }
    else{
      root->data -= element->data;
    }
      print_depth(root);
    }
  return root;
}


//used in del function to find the left max. 
tree* maxVal(tree* root) {
  if(root->right == NULL){
    return root;
  } 
  else{
    return maxVal(root->right);
  }
}


//search function with same compare functionality. 
tree* search(tree* root, char name[]){
  if(root == NULL){
    return NULL;
  }
  int compare = strcmp(name, root->name);
  if(compare == 0){
    return root;
  }
  if(compare < 0){
    return search(root->left, name);
  }
  return search(root->right, name);
}


//height function that uses recursion. it is called from height_balance. 
int height(tree* root) {
  if (root == NULL) {
    return -1;
  }
  int left_height = height(root->left);
  int right_height = height(root->right);

  if (left_height > right_height){
       return left_height + 1;
  } 
  else{
     return right_height + 1;
  }
}


//finds max height of each side of a node. if none there it is -1. if one is missing it is -1. else will calculate
//using the height functions recursive call. 
void height_balance(tree* root) {
  if (root == NULL) {
    printf("left height = -1 right height = -1 balanced\n");
    return;
  }
  int leftHeight = height(root->left);
  int rightHeight = height(root->right);
  printf("left height = %d right height = %d ", leftHeight, rightHeight);
  if ((leftHeight - rightHeight) == 0){
    printf("balanced\n");
  }
  else{
    printf("not balanced\n");
  }
}


//print_depth function called to print. basically a pseduowrapper print function
void print_depth(tree* root) {
  if (root != NULL){
    printf("%s %d %d\n", root->name, root->data, root->depth);
  }
}


//used in main after an operation call to make sure the depth of all nodes are correct. 
void update_depths(tree* root, int depth) {
  if (root == NULL){
    return;
  } 
  root->depth = depth;
  update_depths(root->left, depth + 1);
  update_depths(root->right, depth + 1);
}


//plain jane create node function thats called in main. 
tree* create_node(int data, char name[]) {
  tree* temp = (tree*)malloc(sizeof(tree));
  strcpy(temp->name, name);
  temp->data = data;
  temp->depth = 0;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}


//uses strcmp to match the input for operations. after that depending on which operation, I will call in the name
// or values needed as not all need them in order to work. 
int main(void) {
  int num;
  char operation[15], name[25];
  int val;
  tree* myroot = NULL;

  scanf("%d", &num);

  for (int i = 0; i < num; i++) {
    scanf("%s", operation);

    if(strcmp(operation, "height_balance") == 0){//dont need anything else for height balance
      height_balance(myroot);
    } 
    else if(strcmp(operation, "del") == 0){//del needs a name. prints if it can find it, then updates depths otherwise its not found
      scanf("%s", name);
      tree* node = search(myroot, name);
      if (node != NULL){
        myroot = del(myroot, name);
        update_depths(myroot, 0);
        printf("%s deleted\n", name);
      } 
      else{
        printf("%s not found\n", name);
      }
    } 
    else if(strcmp(operation, "search") == 0){//search will go unless the result of it is NULL
      scanf("%s", name);
      tree* result = search(myroot, name);
      if (result == NULL){
        printf("%s not found\n", name);
      } 
      else{
        print_depth(result);
      }
    } 
    else if(strcmp(operation, "add") == 0){//add call that also creates node
      scanf("%s %d", name, &val);
      tree* node = create_node(val, name);
      myroot = add(myroot, node, 0);
    } 
    else if(strcmp(operation, "sub") == 0){//sub call that also creates node
      scanf("%s %d", name, &val);
      tree* node = create_node(val, name);
      myroot = sub(myroot, node);
      }
  }
  return 0;
}