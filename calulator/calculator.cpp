/********************************** Calculator Program **************************************

Author: Jianlan Zhu (ף���)
Date: 10/30/2016

*********************************************************************************************/
#include<stdio.h>
#include<stack>
#include<math.h>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

// ********************variebles and funstion declaration**********************************

//int Judge(string s,int ii);
float EvalCal(char s[]);
int In(char c);
float Operate(float a, char t, float b);
char Precede(char i,char j);

// **********************************functions*********************************************

// if digit
/*int Judge(string s,int i){
    if(char(s[i])-'0' >= 0 && '9'-char(s[i]) <= 0)
        return s[i]-'0';
    else
        return -1;
};*/

// do single calculaion
float Operate(float a, char t, float b){
    switch(t){
        case '+': return a + b; break;
        case '-': return a - b; break;
        case '*': return a * b; break;
        case '/': return a / b; break;
        default : return 0    ; break;

    }
};  // Operate

// judge priority
char Precede(char i,char j){
    switch(i){
    case '+':{
        if(j == '*' || j == '/' || j == '(')
            {return '<';}
        else
            {return '>';}
        break;
    }
    case '-':{
        if(j == '*' || j == '/' || j == '(')
            {return '<';}
        else
            {return '>';}
        break;
    }
    case '*':{
        if(j == '(' )
            {return '<';}
        else
            {return '>';}
        break;
    }
    case '/':{
        if(j == '(')
            {return '<';}
        else
            {return '>';}
        break;
    }
    case '(':{
        if (j == ')')
            {return '=';}
        else
            {return '<';}
        break;
    }
    case ')':
        return '>'; break;
    case '#':{
        if(j == '#')
            {return '=';}
        else
            {return '<';}
        break;
    }
    default: {return '>'; break;}
    } // switch
}; // Precede

//judge sign or not
int In(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
        return 0;
    else
        return 1;
}; // In


// ***************************************main function*************************************************
int main(){

    while(1){
    float c = 0;    // calculate number value
    int i = 0;
    //int len;      // length of the input
    float result;
    char inp[128] = {'#'};   // input string
    //vector<string> input;
    //vector<float> opnd;  // all the numhers
    // vector<char> optr;  // all the operator

    std::cout << "Please input your expression and end with #.\n";
    std::cin >> inp ;
    std::cout <<"\n";
    /*while(cin >> inp){
        input.push_back(inp);
    }*/

    // EvalExp(inp)//////////////////////////////////////////////////////////////////
    stack<float> OPND; //operand stack
    stack<char>  OPTR; //operator stack
    OPTR.push('#');   // end sign

    float cc = 0;      // value of each number
    char x;
    int ct = 0;       // count the recent number
    //char j = s[ct];
    float a,b;
    char t;
    //int len = inp.size(); // get the length of input

    if(inp[ct] == '-'){
        cc = -1; ++ct;
    }

    while(inp[ct] != '#' || OPTR.top() != '#'){
        if(In(inp[ct])){
                if(cc >= 0)
                    cc = cc*10 + (inp[ct]-'0');
                else if(cc < 0 && ct == 1)
                    cc = ('0' - inp[ct]);
                else
                    cc = cc*10 - (inp[ct]-'0');
            //cc = 10*cc + (inp[ct]-'0');

            ct++;
        }

        else
        {
            if(cc != 0){
                OPND.push(cc);
                cc = 0;
            }
            switch(Precede(OPTR.top(),inp[ct])){
            case '<': // top element priority lower
                OPTR.push(inp[ct]);
                ct++;
                break;
            case '=': // eliminate bracket
                x = OPTR.top();
                OPTR.pop();   //
                ct++;
                break;
            case '>': // pop and push the result
                t = OPTR.top(); OPTR.pop();
                b = OPND.top(); OPND.pop();
                a = OPND.top(); OPND.pop();
                OPND.push(Operate(a,t,b));
                break;
            }   //switch
        }

    }  //while
    result = OPND.top();
    OPND.pop();
    //result = EvalExp(inp);
    // //////////////////////////////////////////////////////////////////////////////
    std::cout << "The result of "<< inp <<" is " <<std::endl
              << result << "\n\n";
    } //while
}
