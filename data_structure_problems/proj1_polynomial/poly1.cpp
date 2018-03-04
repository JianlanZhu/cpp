/********************************** Polynomial Adding Program **************************************

Author: Jianlan Zhu (×£½£á°)
Date: 12/05/2016

***************************************************************************************************/

#include<stdio.h>
#include<vector>
#include<iostream>
#define max(a, b)  (((a) > (b)) ? (a) : (b))
using namespace std;


typedef struct Node{
    int coe;      // coefficient
    Node *next;
    Node *prior;
}Node;            // Node

Node* Initial_linklist(){
    Node *head;
    head = new Node;
    head -> coe = 0;
    return head;
} // Initial_linklist

Node* CreateList(int n){
    Node *head;
    Node *p;
    Node *q;
    head = q = new Node;
    head -> coe = 0;
    head -> prior = NULL;
    head -> next = NULL;
    for(int i = 0; i < n; i++){
        p = new Node;
        p -> coe = 0;
        p -> prior = q;
        p -> next = NULL;
        q -> next = p;
        q = q -> next;
    } // for
    return head;
} // CreateList(int n)

int main(){
    int poly1[] = {0, 1, 2, 3, 4, 5};   // x + 2x^2 + 3x^3 + 4x^4 + 5x^5
    int poly2[] = {4, 3, 2, 1};
    int len1 = sizeof(poly1)/sizeof(int);
    int len2 = sizeof(poly2)/sizeof(int);
    int len = max(len1,len2); // length of the final expression
    Node *polyadd = CreateList(len);
    Node *p = polyadd -> next;
    Node *q = polyadd -> next -> next;
    for(int i = 0; i < len; i++){    // the coefficient of result expression
        if(i < len1 && i < len2){
            p -> coe = poly1[i] + poly2[i];
            p = p -> next;
        }
        else if(len1 <= len2){
            p -> coe = poly2[i];
            p = p -> next;
        }
        else{
            p -> coe = poly1[i];
            p = p -> next;
        }

    } // for

    std::cout << "(" << poly1[0] ;  // first element

    for(int i = 1; i < len1; i++){     // display the first polynomial
        if(poly1[i] > 0)
            std::cout << "+" << poly1[i] << "x^" << i;
        else if(poly1[i] < 0)
            std::cout << poly1[i] << "x^" << i;
    }  // for
    cout << ")+(";
    std::cout << poly2[0];
    for(int i = 1; i < len2; i++){     // display the second polynomial
        if(poly2[i] > 0)
            std::cout << "+" << poly2[i] << "x^" << i;
        else if(poly2[i] < 0)
            std::cout << poly2[i] << "x^" << i;
    } // for
    cout << ")=";

    std::cout << q -> coe;

    q = q -> next;
    for(int i = 1; i < len; i++){
        if(q -> coe > 0){
            std::cout << "+" << q -> coe << "x^" << i;
            q = q -> next;
        }
        else if (q -> coe < 0){
            std::cout << q -> coe << "x^" << i;
            q = q -> next;
        }
    }  // for
    std::cout << ")";

    char flag;
    cin>>flag;

    return 1;
} // int main
