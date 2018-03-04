/********************************** Polynomial Adding Program **************************************

Author: Jianlan Zhu (×£½£á°)
Date: 12/17/2016

***************************************************************************************************/

#include<stdio.h>
#include<iostream>
#include<math.h>
#include<limits>

#define MAX_VER_NUM 20 // max vertex number
#define MAX_ARC_NUM 100 // max vertex number
#define dmt 7           // demention of P (also the point numbers)

using namespace std;

/*
struct ArcNode{
    int adjvex;
    ArcNode *next;
};

struct VertexNode{
    int vertex;
    ArcNode *firstedge;
};
*/

typedef struct ArcNode{
    int adjvex; // location of the point that the arc points to
    struct ArcNode *nextarc;
    int info; // informatione
}ArcNode;

typedef struct VNode{
    string data;
    ArcNode *nextver; // point to the first node linked to the point
}VNode;

struct AdjLGragh{
    VNode vertices[MAX_VER_NUM];
    ArcNode *arcs[MAX_ARC_NUM];
    int vernum;
    int arcnum;
    int kind;
};

class ALGragh{
private:
    AdjLGragh algragh;
    bool visited[MAX_VER_NUM];
public:
    ALGragh(float p[dmt][dmt], int d);
    //~ALGragh();
    // void CreateGragh(int *p); // use 2D array to create gragh
    void Dijkstra(int v0); // sourse point is v0(index)
    // int LocateVex(string u);
    // void ALGraghDisplay();
    //void FindInDegree(int indegree[]);
    //bool TopologicalSort();
};


/********************************************* function  *********************************************/
ALGragh::ALGragh(float p[dmt][dmt],int d){ //d:demention; p:array
    ArcNode *a, *r; //r: point to the last node
    //VNode *b;
    int c = 0; // check
    algragh.vernum = d;
    // arc initialize
    for(int m = 0; m < d; m++){ // operate the first element
        /*
        a = new ArcNode;
        a->adjvex = -1;
        a->nextarc = NULL;
        a->info = -1;
        */
        algragh.arcs[m] = NULL;
    } // for : initialize

    // create adjacent list

    for(int i = 0; i < d; i++){ // row
        for(int j = 0; j < d; j++){ // column
            if(p[i][j] > 0 && p[i][j] < INFINITY){
                a = new ArcNode;
                a->adjvex = j;
                a->info = p[i][j]; // mapping the value of p[i][j]
                a->nextarc = NULL;
                // r = algragh.arcs[i];
                if(algragh.arcs[i] == NULL){ // if it is the first arc linked to the point
                    algragh.arcs[i] = a;
                    r = algragh.arcs[i];
                    c++;
                }
                else{ // if it is not the first
                    r->nextarc = a;
                    r = r->nextarc;
                } //if
            } // if
        } //for
    } //for
    //*/
    //test
    /*
    std::cout << "Creation of Adjacent List:" << std::endl;
    for(int x = 0; x < 7; x++){
        a = algragh.arcs[x];
        while(a != NULL){
            cout<<a->info<<" ";
            a = a->nextarc;
        } // while
        cout<<endl;
    } // for */

    if(c == 0){
        std::cout << "Wrong !" << std::endl;
    }

} //ALGragh::ALGragh(float *p, int d)

void ALGragh::Dijkstra(int v0){
    // Dijkstra algorithm to show the shortest path frpm v0 to each other vector
    // if P[v][w] is greater than/equal to 0, means that w is one point which is on the shortest path from v0 to v
    // P[v][w]: the order of w on the path from v0 to v
    //final[v] is true when v is in set S, which means that we have known the shortest path from v0 to v
    int v, w, s;
    bool final[algragh.vernum];
    // cout<<sizeof(final)/sizeof(bool)<<endl;
    int P[dmt][dmt];
    float D[dmt];
    ArcNode *q, *r;

    std::cout << "Dijkstra Algorithm" << std::endl << std::endl;
    for(int x = 0; x < algragh.vernum; x++){
        D[x] = INFINITY;
        final[x] = false;
    }
    for(v = 0; v < algragh.vernum; v++){
        for(w = 0; w < algragh.vernum; w++){
            P[v][w] = -1;
        } // for
    } // for

    // test Display
    /*
    for(int x = 0; x < algragh.vernum; x++){
        for(int y = 0; y < algragh.vernum; y++){
            cout << P[x][y] << "\t";
        } // for
        cout<< endl;
    } // for
    // test Display
    //*/


    q = algragh.arcs[v0];
    P[v0][v0] = 0;
    while(q != NULL){ // if this point has adjacent node
        P[q->adjvex][v0] = 0;
        P[q->adjvex][q->adjvex] = 1; // there must at least be a path from v0 t0 v
        D[q->adjvex] = q->info; // initial value = direct distance
        q = q->nextarc;
    } //while
    D[v0] = 0;
    final[v0] = true;

    // test Display
    /*
    for(int x = 0; x < algragh.vernum; x++){
        cout<<D[x]<<'\t';
    }
    cout<<endl;
    for(int z = 0; z < algragh.vernum; z++){
        cout<<final[z]<<'\t';
    }
    cout<< endl;

    for(int x = 0; x < algragh.vernum; x++){
        for(int y = 0; y < algragh.vernum; y++){
            cout << P[x][y] << '\t';
        } // for
        cout<< endl;
    } // for
    // Display */

    // success

    // real loop****************************************
    for(int i = 1; i < algragh.vernum; i++){
        float mini = INFINITY;
        for(w = 0; w < algragh.vernum; w++){
            if(!final[w] && D[w] < mini){
                v = w;
                mini = D[w];
            } // if
        } // for
        final[v] = true; // add the closest node to final[]
        // for(w = 0; w < algragh.vernum; w++){}
        r = algragh.arcs[v];
        /*
        for(int x=0;x<7;x++){
            cout<<final[x]<<endl;
        } //for */

        while(r != NULL && !final[r->adjvex] && mini < INFINITY && (mini + r->info) < D[r->adjvex] ){
            // if r.adjvex is not linked && v = recent added && we can find the closest node(mini is limited)
            // we update the value that is not minimum
            D[r->adjvex] = mini + r->info; // update D[w]
            for(int n = 0; n < algragh.vernum; n++){
                // update P[w], v0 to w = v0 to v + v to w and now w = r.adjvex
                P[r->adjvex][n] = P[v][n];
            } // for
            P[r->adjvex][r->adjvex] = P[v][v] + 1;
            /*
            for(int x=0;x<7;x++){
                cout<<final[x]<< '\t';
            } // for
            cout<<endl;

            for(int x=0;x<7;x++){
                cout<<D[x]<<'\t';
            } // for
            cout<<endl;*/
            r = r->nextarc;
        } // while
    } // for

    // test Display
    /*
    for(int x = 0; x < algragh.vernum; x++){
        for(int y = 0; y < algragh.vernum; y++){
            cout << P[x][y] << "\t";
        } // for
        cout<< endl;
    } // for
    // Display
    //*/


    for(int k = 0; k < algragh.vernum; k++){
        // display from v0 to k
        int h,c;
        c = 0; // whether there is a path; when the value is 0 there is no path
        if(k != v0){
            std::cout << "The shortest path from v" << v0 << " to v" << k << " : " << D[k] << std::endl;
            std::cout << "v" << v0;
            for(h = 0;h < algragh.vernum; h++){ // cout the sequence
                s = h;
                while(P[k][s] != (h+1)){
                    s++;
                    if(s == algragh.vernum)
                        {break;} // no dead loop
                } // while
                if(s < algragh.vernum){
                    std::cout << " -> " << "v" << s;
                    c++; // there is a path from v0 to k
                } // if
            } // fpr

            if(!c){ // if no path from v0 to k
                std::cout<< " has no path to v" << k;
            } // if
        std::cout << std::endl << std::endl;
        } // if

    } // for
    //*/
    // end of Display
} // ALGragh::Dijkstra

/*********************************************  main  ************************************************/
int main(){
    //                    1        2        3        4        5        6        7
    float ini[dmt][dmt]={{0       ,13      ,8       ,INFINITY,30      ,INFINITY,32      },  //1
                         {INFINITY,0       ,INFINITY,INFINITY,INFINITY,30      ,7       },  //2
                         {INFINITY,INFINITY,0       ,5       ,INFINITY,INFINITY,INFINITY},  //3
                         {INFINITY,INFINITY,INFINITY,0       ,6       ,INFINITY,INFINITY},  //4
                         {INFINITY,INFINITY,INFINITY,INFINITY,0       ,2       ,INFINITY},  //5
                         {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,0       ,17      },  //6
                         {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,0       }}; //7
    // dmt = 7;
    int demention = dmt;
    ALGragh G1(ini,demention);
    int v0 = 0;
    /*
    float jj = INFINITY;
    if(jj==INFINITY)
        cout<<INFINITY;
    //*/

    G1.Dijkstra(v0);
    return 1;
}





