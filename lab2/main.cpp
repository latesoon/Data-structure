#include <iostream>
#include <cstring>

using namespace std;
template<class T>
class stack{
public:
    stack(int maxn=1000000);
    ~stack();
    bool isempty();
    T findtop();
    void push(T x);
    T pop();
    void ex_pop(int& start,int& pace);
    T get_max();
    void print();
    void samefinder(int& start,int& pace);
    void samebreaker();
private:
    int top;
    int maxtop;
    T* mstack;
};
template<class T>
stack<T>::stack(int maxn) {
    top=0;
    maxtop=maxn;
    mstack=new T[maxn];
}
template<class T>
stack<T>::~stack() {
    delete[]mstack;
}
template<class T>
bool stack<T>::isempty(){
    return top==0;
}
template<class T>
T stack<T>::findtop(){
    return mstack[top-1];
}
template<class T>
void stack<T>::push(T x) {
    if(top==maxtop){
        throw out_of_range("Out of bounds!\n");
    }
    mstack[top++]=x;
}
template<class T>
T stack<T>::pop(){
    if(!top){
        throw out_of_range("Out of bounds!\n");
    }
    T a=mstack[--top];
    return a;
}
template<class T>
void stack<T>::ex_pop(int& start,int& pace) {
    for(int a=start;a+pace<top;a++){
        mstack[a]=mstack[a+pace];
    }
    top-=pace;
}
template<class T>
T stack<T>::get_max(){
    if(!top){
        throw out_of_range("No elements!\n");
    }
    T maxn=mstack[0];
    for(int p=1;p<top;p++)
        maxn=max(maxn,mstack[p]);
    return maxn;
}
template<class T>
void stack<T>::print(){
    if(isempty())return;
    cout<<mstack[0];
    for(int p=1;p<top;p++){
        cout<<','<<mstack[p];
    }
    cout<<'\n';
}
template<class T>
void stack<T>::samefinder(int& start,int& pace){
    for(int p=0;p<top-1;p++){
        if(mstack[p]==mstack[p+1]) {
            start=p;
            pace=2;
            break;
        }
    }
    if(pace==0)return;
    int a=start,b=a+1;
    while(++b<top && --a>=0){
        if(mstack[a]!=mstack[b])
            return;
        else{
            start--;
            pace+=2;
        }
    }
}
template<class T>
void stack<T>::samebreaker(){
    while(!isempty()){
        int start,pace=0;
        samefinder(start,pace);
        if(pace==0)
            break;
        else{
            ex_pop(start,pace);
        }
    }
}
void oper1() {
    stack<int> A;
    do {
        int x;
        cin >> x;
        A.push(x);
    } while (getchar() == ',');
    cout << A.get_max() << '\n';
    A.samebreaker();
    A.print();
}
void cal1(stack<double>& B,stack<char>& C){
    double c2=B.pop(),c1=B.pop();
    char m=C.pop();
    switch(m) {
        case '+':
            c1 += c2;
            B.push(c1);
            break;
        case '-':
            c1 -= c2;
            B.push(c1);
            break;
        case '*':
            c1*=c2;
            B.push(c1);
            break;
        case '/':
            if(c2==0) throw invalid_argument("Divided by 0!");
            c1/=c2;
            B.push(c1);
            break;
    }
}
void calculator(){
    stack<double>B;
    stack<char>C;
    char s[1000000];double s1=0;bool getint=false,getop=false,neg=false,getdot=true;double position;
    cin>>s;
    for(int p=0;p<strlen(s);p++){
        if((s[p]>='0'&&s[p]<='9')||s[p]=='.'){
            if(s[p]=='.'){
                if(getdot) {
                    getdot = false;
                    position=0.1;
                }
                else
                    throw invalid_argument("Invalid input!");
            }
            else{
                if(getdot){
                    s1=s1*10+s[p]-'0';
                    getint=true;
                }
                else{
                    s1+=position*(s[p]-'0');
                    position*=0.1;
                    getint=true;
                }
            }
        }
        else {
            if (getint) {
                if(neg)
                    s1*=(-1);
                neg= false;
                B.push(s1);
                s1 = 0;
                getint=false;
                getop=true;
                getdot=true;
            }
            if (s[p] == '+' ) {
                if(getop) {
                    while (!C.isempty() && C.findtop() != '(') {
                        cal1(B, C);
                    }
                    C.push(s[p]);
                    getop = false;
                }
                else
                    throw invalid_argument("Invalid input!");
            }
            else if(s[p]=='-'){
                if(getop){
                    while (!C.isempty() && C.findtop() != '(') {
                        cal1(B, C);
                    }
                    C.push(s[p]);
                    getop=false;
                }
                else {
                    if(neg) neg=false;
                    else neg=true;
                }
            }
            else if (s[p] == '*' || s[p] == '/') {
                if(getop) {
                    while (!C.isempty() && C.findtop() != '(' && C.findtop() != '+' && C.findtop() != '-') {
                        cal1(B, C);
                    }
                    C.push(s[p]);
                    getop = false;
                }
                else
                    throw invalid_argument("Invalid input!");
            }
            else if (s[p] == '(')
                C.push(s[p]);
            else if (s[p]==')'){
                while (C.findtop() != '(') {
                    cal1(B, C);
                }
                C.pop();
            }
            else
                throw invalid_argument("Invalid input!");
        }
    }
    if(getint) {
        if (neg)
            s1 *= (-1);
        B.push(s1);
        s1 = 0;
    }
    while(!C.isempty()){
        cal1(B, C);
    }
    double ans=B.pop();
    if(!(B.isempty())){
        throw invalid_argument("Invalid input!");
    }
    cout<<ans<<'\n';
}
int main() {
    oper1();//（2)
    calculator();//(3)
    return 0;
}
