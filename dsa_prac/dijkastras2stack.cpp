#include<bits/stdc++.h>
using namespace std;

int ans(string fix){
    stack<int>val;
    stack<char>oper;
    for(auto it: fix){
        if(isalnum(it)) val.push(it-'1'+1);
        else if(it=='(') continue;
        else if(it==')'){
            char op=oper.top();
            oper.pop();
            int x=val.top();
            val.pop();
            int y=val.top();
            val.pop();
            int z;
            if(op=='+') z=x+y;
            else if(op=='-') z=x-y;
            else if(op=='*') z=x*y;
            else z=0;
            val.push(z);
        }
        else oper.push(it);
    }
    int a=val.top();
    val.pop();
    if(val.empty()) return a;
    else{
        char op=oper.top();
        oper.pop();
        int x=val.top();
        val.pop();
        int z;
        if(op=='+') z=x+a;
        else if(op=='-') z=x-a;
        else if(op=='*') z=x*a;
        else z=0;
        return z;
    }
}

int main(){
    string test="1+(2*3)*4";
    cout<<ans(test)<<endl;
}