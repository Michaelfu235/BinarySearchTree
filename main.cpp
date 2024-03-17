/*
  Author: Michael Fu
  Date: 3/21/2024
  Description: this code cretes a binary search tree that allows you to add through console and file, search for a number, delete a number, and print the tree. 

  
 */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//node struct with data value and pointers to left and right
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


//function prototypes

void add(Node* tree, int data);
void printTree(Node* tree, int depth, int fromwhere);
int search(Node* tree, int searchNum);
Node* deleteNode(Node* tree, int deleteNum);
Node* nextValue(Node* tree);
void addByFile(Node* &tree);


int main(){
  //a node that is the head of the tree that everything else goes off of
  Node* treeHead = new Node(-1);

  char inputt[15];
  

  //input and keep going variables
  bool justKeepGoing = true;
  while(justKeepGoing == true){
    //prompt for input
    cout << "Enter a command (ADD, SEARCH, DELETE, PRINT, or QUIT): " << endl;
    cin >> inputt;

    if(strcmp(inputt, "ADD") == 0){
      //if they want to add, ask if they want to do so through file or console. if they want file, call the add by file function. Otherwise, if they want to add through console, keep looping with justKeepGoingtwo until they say done, and until then, ask what number they want to add and call the add function. 
      cout << "input type? (FILE or CONSOLE)" << endl;
      cin >> inputt;
      if(strcmp(inputt, "FILE")==0){
	addByFile(treeHead);
      } else if (strcmp(inputt, "CONSOLE")==0){
	bool justKeepGoingtwo = true;
	char input[10];

	while(justKeepGoingtwo){
	  cout << "enter numbers from 1-999, or \"DONE\" when done" << endl;

	  cin >> input;
	  if(strcmp(input, "DONE")==0){
	    justKeepGoingtwo = false;
	  } else {
	    int num = atoi(input);
	    add(treeHead, num);
	  }
	}
      }
    } else if (strcmp(inputt, "SEARCH")==0){
      //if they want to search, prompt for the number and call the search function. if the search function gave back the number they want to find, then the number exits. otherwise, it doesn't. 
      cout << "what number do you want to find?" << endl;
      int numby;
      cin >> numby;
      int numbytwo = search(treeHead, numby);
      if(numbytwo == numby){
	cout << numby << " exits in the tree" << endl;
      } else {
	cout << numby << " does not exist in the tree" << endl;
      }
    } else if (strcmp(inputt, "DELETE")==0){
      //if they want to delete something, check if the number exists, then call the deleteNode function. 
      cout << "what number do you want to delete?" << endl;
      int numby;
      cin >> numby;
      int numbytwo = search(treeHead, numby);
      if(numbytwo==numby){
	deleteNode(treeHead, numby);
      } else {
	cout << numby << " does not exist" << endl;
      }
    } else if (strcmp(inputt, "PRINT")==0){
      //if they want to print, call the print tree function. 
      printTree(treeHead, 0, 0);
    } else if (strcmp(inputt, "QUIT")==0){
      //if they want to quit, end the loop. 
      justKeepGoing = false;
    }

    
  }
  return 0;

}


void add(Node* tree, int data){
  //for the add function, if the tree is empty, set the data of the tree to the inputted data. 
  if(tree->data == -1){
    tree->data = data;
    return;
  } else {
    //if the data the user wants to add is less than the data of the tree node, set tree to tree->left, and recursivevly call the add function. 
    if(data < tree->data && tree->left!=NULL){
      tree = tree->left;
      add(tree, data);
      
    } else if (data < tree->data && tree->left==NULL){
      //but if the data wants to add is less than the data of the tree, and left is null, set left to a node with the new data. 
      Node* newNode = new Node(data);
      tree->left = newNode;
      return;
    }


    //for the other side (if the data to be added is greater than the trees data) do the same thing as with above, but with the < sign turned into a > sign
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


//for the printtree, if the trees data is -1, the tree is empty.
//if tree->right is not null, then call the print function again, but with tree->right, depth+1, and 1 to signify that the next node that is being called in the print function is a right node.
//then print the number of tabs (depth-1), then an arrow/line depending on if it came from 2(left) or 1(right). Then print the data.
//if tree->left is not null, do the same thing with tree->right, with the function being called with tree->left, depth+1, and 2.
void printTree(Node* tree, int depth, int fromwhere){
  if(tree->data==-1){
    cout << "tree is empty" << endl;
    return;
    
  }
  if(tree->right!=NULL){
    printTree(tree->right, depth+1,1);
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
    printTree(tree->left, depth+1, 2);
    
  }
  
  
}





//for the search function, if the tree is null, return -1.
//if tree->data is the number we want, return the number.
//if tree->data is less than, return search of right. Otherwise, return search of left. 
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


//if the tree is empty, return null. if the tree->data is less than the number to delete, set tree->right to deleteNode(tree->right, deletenum). same thing with if tree->data is more than the number to delete, set tree->left to deleteNode(tree->left, deletenum). 

Node* deleteNode(Node* tree, int deleteNum){
  if(tree==NULL){
    return NULL;
  }
  if(tree->data < deleteNum){
    tree->right = deleteNode(tree->right, deleteNum);
  } else if (tree->data > deleteNum){
    tree->left = deleteNode(tree->left, deleteNum);
  } else if (tree->data == deleteNum){
    //if the data of the tree node given is equal to the number to delete, then if that node has no children, return NULL (which the previous call of the function will set the node to null, essentially deleting it)
    if(tree->left == NULL && tree->right == NULL){
      return NULL;
    } else if (tree->left != NULL && tree->right == NULL){
      //if there is only a left node, then set a temp node of tree->left, and return the temp node. (which the previous call of the function will basically replace the node to delete with it's onyl child. 
      Node* temp = tree->left;
      delete tree;
      return temp;
    } else if (tree->right != NULL && tree->left == NULL){
      //same thing with if theres a right node as if theres only a left node. ^
      Node* temp = tree->right;
      delete tree;
      return temp;
    }

    //if theres both a left and right node, then create a tempNode of the next value (smallest number that branches off of the node given, by caling the nextValue function). then set tree->data to temporary node's data, and set tree->right to deleteNode(tree->right, temp->data) (delete the node that has been duplicated to replace the node that has been deleted);
    Node* temp = nextValue(tree->right);
    tree->data = temp->data;
    tree->right = deleteNode(tree->right, temp->data);
  }
  //then return tree. 
  return tree;
  
}

//for the next, value, repeatedly go to the left until its at the end, then return the leftmost node pointer. 
Node* nextValue(Node* tree){
  Node* current = tree;
  while(current != NULL && current->left != NULL){
    current = current->left;
  }
  return current;
}



//for the addByFile, ask then waht file they want to add from, then repeatedly call the add function using the contents of the file, then close the file. 
void addByFile(Node* &tree){
  char* fileName = new char[80];

  cout << "what's the name of the file you want to add (including .txt)" << endl;
  cin >> fileName;
  cin.ignore();
  fstream file;
  file.open(fileName);

  int input = 0;
  while(file >> input){
    add(tree, input);
  }
  file.close();
}
