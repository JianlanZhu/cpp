/********************************** BinaryTree Program *******************************************

Author: Jianlan Zhu (×£½£á°)
Date: 12/10/2016

***************************************************************************************************/

#include<stdio.h>
#include<stack>
#include<iostream>
using namespace std;

typedef struct BiTNode{
    char data;
    BiTNode *lchild;
    BiTNode *rchild;
    //BiTNode *parant;
}BiTNode, *BiTP;

typedef struct BiTNode2{
    BiTNode *btn;  // binary tree node
    int tag;
}BiTNode2, *BiTP2;

class BinaryTree{
    private:
        BiTNode *bt;
    public:
        BinaryTree(){
            bt = NULL;
        };
        //~BinaryTree();
        int BTCreate(char *p);
        void PreorderTraverse();
        void PostorderTraverse();
};

/*********************************************  function  *********************************************/
int BinaryTree::BTCreate(char *p){   // preorder create tree
    if(*p == '\0' || *p == '#'){
        std::cout << "Empty tree!!";
        return 0;
    } // if

    stack<BiTP> bts;  // binary tree stack
    BiTNode *q, *t, *s;
    // s : stack operation ; t : connection ; q : new node ;
    // bt = NULL;
    q = new BiTNode;
    q -> data = *p;
    q -> lchild = NULL;
    q -> rchild = NULL;
    bt = q;
    p++;
    t = bt;
    bts.push(q);
    while(*p != '\0'){
        if(*p != '#'){
            q = new BiTNode;
            q -> data = *p;
            q -> lchild = NULL;
            q -> rchild = NULL;
            t -> lchild = q;
            //cout << t -> data << " ";
            t = t -> lchild;
            bts.push(q);
            //cout << bts.size() << endl;
            //t = t -> lchild;
            p++;
        }
        else{  // goto right subtree if p = #
            if(*(p+1) != '#' && *(p+1) != '\0'){  // deal with the last #
                t = bts.top();
                bts.pop();
                q = new BiTNode;
                q -> data = *(p+1);
                q -> lchild = NULL;
                q -> rchild = NULL;
                t -> rchild = q;
                t = t -> rchild;
                //t = t -> rchild;
                bts.push(q);
                p++;
                p++;
            }
            else if(*(p+1) == '#'){
                t = bts.top();
                bts.pop();
                p++;
            }
            else
                p++;
            //  if
        } // if
    } // while
    //t = bt -> lchild;
    //cout << "jianlan " << t -> data << " jianlan " << endl;
    if(bts.empty())
        return 1; // successfully create
    else
        return 0; // wrong sequence
    // if
} // BinaryTree::BTCreate

void BinaryTree::PreorderTraverse(){
    std::cout << "The preorder traverse of the sequence is" << std::endl;
    BiTNode *p, *t;
    p = bt;
    stack<BiTP> bts;
    if(p == NULL)
        cout << "empty tree!" << endl;
    while(p || !bts.empty()){
        if(p){  // traverse left subtree
            std::cout  << p -> data << "!";
            bts.push(p);
            p = p -> lchild;
        }
        else{  // if stack not empty && p = NULL
            p = bts.top();
            bts.pop();
            p = p -> rchild;
        } // if
    } // while
    std::cout << endl << "End Perorder traverse!" << std::endl;
} // BinaryTree::PreorderTraverse

void BinaryTree::PostorderTraverse(){
    std::cout << "The postorder traverse of the sequence is" << std::endl;
    BiTNode *p;
    p = bt;
    stack<BiTP2> bts2;
    BiTP2 temp;
    //cout << p -> lchild -> data;

    while(p || !bts2.empty()){
        if(p){
            BiTNode2 *t = new BiTNode2;
            t -> btn = p;
            t -> tag = 1;
            bts2.push(t);
            p = p -> lchild;
            //cout << bts2.size();
        }

        else{
            temp = bts2.top();
            bts2.pop();
            if(temp -> tag == 1){  // if the first time to be at top
                temp -> tag = 2;
                bts2.push(temp);
                p = temp -> btn -> rchild;
            }
            else{
                std::cout << temp -> btn -> data << "!";
                p = NULL;  // why?
            } //if
        } //if
        //*/
    } // while

    std::cout << endl << "End Perorder traverse!" << std::endl;

} // BinaryTree::PostorderTraverse

/*********************************************  main  ************************************************/
int main(){
    char str[] = {"ABC##DE#G##F###"};
    char *p = str;
    BinaryTree BT;
    /*  test 1
    while(*p != '\0'){
        cout << *p;
        p++;
    }*/

    /* test 2
    stack<BiTP> bts1;
    BiTNode *q, *r;
    q = new BiTNode;
    q -> data = 'd';
    q -> lchild = NULL;
    q -> rchild = NULL;
    cout << q -> data << endl;
    bts1.push(q);
    cout << "q _> data = " << q -> data << endl;
    r = bts1.top();
    bts1.pop();
    cout << r -> data << endl;
    if(bts1.empty())
        cout << "emp";
    else
        cout << "not";
    // if
    */
    // end test2

    int i = BT.BTCreate(p);
    //cout << i << " ";
    if(i){
        std::cout << "Seccessfully Create!" << std::endl;
        //BiTNode *q;
        //cout << BT.bt->data << "sjeji" << endl;
        BT.PreorderTraverse();
        BT.PostorderTraverse();
    }
    else
        std::cout << "Wrong input sequence!" << std::endl;
    //if
    return 0;
}
