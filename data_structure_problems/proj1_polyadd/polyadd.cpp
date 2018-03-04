/********************************** Polynomial Adding Program **************************************

Author: Jianlan Zhu (×£½£á°)
Date: 12/05/2016

***************************************************************************************************/

#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define Max 20

using namespace std;

typedef struct PolyAr{
    float coef;  // coefficient
    int exp;  // exponent
}PolyArray[Max];

struct PolyNode{
    float coef;
    int exp;
    PolyNode *next;
};

class Poly{
private:
    PolyNode *Head;
public:
    Poly(){
        PolyNode *s;
        s = new PolyNode;
        s -> next = NULL;
        s -> coef = 0;
        s -> exp = -1;
        Head = s;
    };   // constructor
    ~Poly(){};   // destructor
    void CreatePoly(PolyArray a, int n);  // create polynomial linklist
    void PolyDisplay();  // display polynomial
    void PolySort();  // sort the list
    void PolyCopy(Poly LB);
    void PolyAdd(Poly LB);  // addition
    void PolyMul(Poly LB);  // multiplication
};

/*********************************************  function  *********************************************/

void Poly::PolyCopy(Poly LB){
    PolyNode *s, *r, *p, *t;
    r = Head;
    while(r -> next != NULL){
        t = r -> next;
        while(t -> next != NULL)
            t = t -> next;
        delete t;
    }  // while

    p = LB.Head -> next;
    while(p != NULL){
        s = new PolyNode;
        s -> coef = p -> coef;
        s -> exp = p -> exp;
        s -> next = NULL;
        r -> next = s;
        r = r -> next;
        p = p -> next;
    }  // while
}  // PolyCopy


void Poly::CreatePoly(PolyArray a, int n){
    // create polynomial linklist from polynomial array
    PolyNode *s, *r;
    int i;
    r = Head;
    for(i = 0; i < n; i++){
        s = new PolyNode;
        s -> coef = a[i].coef;
        s -> exp = a[i].exp;
        s -> next = NULL;
        r -> next = s;
        r = s;
    }  // for
}  // CreatePoly

void Poly::PolySort(){
    // sort the sortedlist
    PolyNode *p, *q, *r;
    p = Head -> next;
    if(p != NULL){
        r = p -> next;
        p -> next = NULL;
        p = r;
        while(p != NULL){
            r = p -> next;
            q = Head;
            while(q -> next != NULL && q -> next -> exp < p -> exp)
                q = q -> next;  // insert *p's precursor *q
            p -> next = q -> next;  // *p inserted after *q
            q -> next = p;
            p = r;
        }  // while
    }  // if
}  // PolySort

void Poly::PolyDisplay(){
    PolyNode *p;
    p = Head -> next;
    if(p != NULL){
        if(p -> exp ==0)
            std::cout << p -> coef;
        else
            std::cout << p -> coef << "x^" << p -> exp;
        p = p -> next;
        while(p != NULL){
            if(p -> coef > 0){
                std::cout << " + " << p -> coef << "x^" << p -> exp;
                p = p -> next;
            }
            else{
                std::cout << " - " << -(p -> coef) << "x^" << p -> exp;
                p = p -> next;
            }  // if
        }  // while
    }
    else{
        std::cout << "NULL!" << endl;
    }  // if
}  // PolyDisplay

void Poly::PolyAdd(Poly LB){
    float sum;
    PolyNode *pa, *pb, *qa, *qb;
    pa = Head;
    qa = pa -> next;
    pb = LB.Head;
    qb = pb -> next;
    while(qa != NULL && qb != NULL){
        if(qa -> exp < qb -> exp){
            pa = qa;
            qa = qa -> next;
        }
        else if(qa -> exp > qb -> exp){
            pb -> next = qb -> next;
            qb -> next = qa;
            pa -> next = qb;
            pa = qb;
            qb = pb ->next;
        }
        else{
            sum = qa -> coef + qb -> coef;
            if(sum == 0){
                pa -> next = qa -> next;
                delete qa;
                qa = pa -> next;
                pb -> next = qb -> next;
                delete qb;
                qb = pb -> next;
            }  // if sum == 0
            else{
                qa -> coef = sum;
                pa = qa;
                qa = qa -> next;
                pb -> next = qb -> next;
                delete qb;
                qb = pb -> next;
            }  // if
        }  // if
    }  // while
    if(qb != NULL){
        pa -> next = qb;
        delete pb;
    }  // if
}  // PolyAdd

void Poly::PolyMul(Poly LB){
    PolyNode *p, *q, *r, *s, *t;
    p = Head -> next;
    q = LB.Head -> next;
    Poly LC;
    r = LC.Head;
    while(p != NULL){
        while(q != NULL){
            s = new PolyNode;
            s -> coef = (p -> coef) * (q -> coef);
            s -> exp = (p -> exp) + (q -> exp);
            s -> next = NULL;
            r -> next = s;
            r = r -> next;
            q = q -> next;
        }  // while
        p = p -> next;
        q = LB.Head -> next;
    }  // while

    // LC.PolySort();

    p = LC.Head -> next;
    if(p != NULL){
        r = p -> next;
        p -> next = NULL;
        p = r;
        while(p != NULL){
            r = p -> next;
            q = LC.Head;
            while(q -> next != NULL && q -> next -> exp < p -> exp)
                q = q -> next;  // insert *p's precursor *q
            p -> next = q -> next;  // *p inserted after *q
            q -> next = p;
            p = r;
        }  // while
    }  // if   and end LC.PolySort

    r = Head;
    t = r -> next;
    while(t != NULL){
        r -> next = t -> next;
        delete t;
        t = r -> next;
    }  // while   OK

    // combine
    t = LC.Head -> next;
    r = t -> next;

    while(r != NULL){
        if(t -> exp == r -> exp){
            t -> coef += r -> coef;
            t -> next = r -> next;
            delete r;
            r = t -> next;
        }
        else{

            r = r -> next;
            t = t -> next;
        }  // if
    }  // while

    //PolyCopy(LC);
    r = Head;
    p = LC.Head -> next;
    while(p != NULL){
        s = new PolyNode;
        s -> coef = p -> coef;
        s -> exp = p -> exp;
        s -> next = NULL;
        r -> next = s;
        r = r -> next;
        p = p -> next;
    }  // while     and end PolyCopy(LC)

}  // PolyMul

/*********************************************  main  ************************************************/
int main(){
    // addition
    Poly LA, LB;
    Poly LC;
    PolyArray a = {{7,0}, {3,1}, {9,8},{5,16}};
    PolyArray b = {{8,1}, {22,7}, {-9,8}};  // element number should be 3
    LA.CreatePoly(a,4);
    LB.CreatePoly(b,3);
    LA.PolySort();
    LB.PolySort();
    std::cout << "LA: ";
    LA.PolyDisplay();
    std::cout << endl;
    std::cout << "LB: ";
    LB.PolyDisplay();
    std::cout << endl;

    LA.PolyAdd(LB);
    std::cout << "Adding of two Polynomial: ";
    LA.PolyDisplay();

    //LC.PolyCopy(LB);
    //LC.PolyDisplay();

    /*LA.PolyMul(LB);
    std::cout << "Multiplication of two Polynomial: " << endl;
    LA.PolyDisplay();*/
    std::cout << endl;
    std::cout << "End of Multiplication." << endl;
    return 0;
}  // end main

/*********************************************  end  *************************************************/
