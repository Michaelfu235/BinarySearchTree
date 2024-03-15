#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Node {
public:
  int data;
  Node* left;
  Node* right;

  Node(int newData){
    data = newData;
    left = NULL;
    right = NULL;
  }
};



void add(Node* tree, int data);
void printTree(Node* tree, int depth, int fromwhere);
int search(Node* tree, int searchNum);

int main(){
  Node* treeHead = new Node(-1);
  add(treeHead, 5);
  add(treeHead, 3);
  add(treeHead, 15);
  add(treeHead, 9);
  add(treeHead, 1);
  add(treeHead, 4);
  add(treeHead, 6);
  add(treeHead, 7);
  add(treeHead, 11);
  add(treeHead, 2);
  add(treeHead, 8);
  add(treeHead, 13);
  add(treeHead, 14);
  add(treeHead, 16);

  cout << search(treeHead, 5) << endl;
  cout << search(treeHead, 17) << endl;
  cout << search(treeHead, 13) << endl;
  cout << search(treeHead, 1) << endl;

  
  printTree(treeHead, 0, 0);

  
  //  cout << "hi" << endl;
}


void add(Node* tree, int data){
  if(tree->data == -1){
    tree->data = data;
    return;
  } else {
    
    if(data < tree->data && tree->left!=NULL){
      tree = tree->left;
      add(tree, data);
    } else if (data < tree->data && tree->left==NULL){
      Node* newNode = new Node(data);
      tree->left = newNode;
      return;
    }

    /*
    if(data == tree->data && tree->left!=NULL){
      tree = tree->left;
      add(tree, data);
    } else if (data == tree->data && tree->left == NULL){
      Node* newNode = new Node(data);
      tree->left = newNode;
      return;
      }*/
    
    if(data > tree->data && tree->right!=NULL){
      tree = tree->right;
      add(tree, data);
    } else if (data > tree->data && tree->right==NULL){
      Node* newNode = new Node(data);
      tree->right = newNode;
      return;
      }
    
  }
}


void printTree(Node* tree, int depth, int fromwhere){
  if(tree->data==-1){
    cout << "tree is empty" << endl;
    return;
    
  }
  if(tree->right!=NULL){
    //for(int i = 0;i<depth-1;i++){
    //  cout << "\t";
    //}
    //cout << "/▔▔▔▔▔" << tree->right->data << endl;;
    
    printTree(tree->right, depth+1,1);
    //cout << tree->right->data << endl;
  }

  for(int i = 0;i<depth-1;i++){
    cout << "\t";
  }
  
  if(fromwhere==2){
    cout << "\\____";
  } else if(fromwhere == 1){
    cout << "/▔▔▔▔▔";
  }
  cout << tree->data << endl;

  if(tree->left!=NULL){
    //for(int i = 0;i<depth-1;i++){
    //  cout << "\t";
   //}
    //cout << "\\_____" << tree->left->data << endl;

    printTree(tree->left, depth+1, 2);
    //cout << tree->left->data << endl;
  }
  
  
}






int search(Node* tree, int searchNum){

  if(tree == NULL){
    return -1;
  }
  if(tree->data == searchNum){
    return(tree->data);
  }
  if(tree->data < searchNum){
    //if(tree->right != NULL){
    return search(tree->right, searchNum);
      //}
  } else {
    return search(tree->left, searchNum);
  }
  
}

