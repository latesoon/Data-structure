#include <iostream>
using namespace std;
const int nu=2e9;
template<class T>
class MQ;
template<class T>
class MQnode{
public:
    friend class MQ<T>;
private:
    T data;
    MQnode<T>* next;
};
template<class T>
class MQ{
public:
    MQ(){first=0;}
    ~MQ();
    bool empty(){if(!first)return true;else return false;}
    T front();
    void push(T x);
    void pop();
private:
    MQnode<T>* first;
};
template<class T>
MQ<T>::~MQ(){
    auto* temp=first;
    while(first){
        first=temp->next;
        delete[]temp;
        temp=first;
    }
}
template<class T>
void MQ<T>::push(T x){
    auto* p=new MQnode<T>;
    p->data=x;p->next=0;
    if(empty()){first=p;return;}
    auto* q=first;
    while(q->next)q=q->next;
    q->next=p;
}
template<class T>
void MQ<T>::pop(){
    MQnode<T>*p=first->next;
    delete[]first;
    first=p;
}
template<class T>
T MQ<T>::front(){
    if(empty())throw invalid_argument("No item!");
    return first->data;
}
template<class T>
class BST;
template<class T>
class BSTnode{
public:
    friend class BST<T>;
private:
    T data;
    BSTnode<T> *Lchild,*Rchild;
};
template<class T>
class BST{
public:
    BST(){root=0;}
    ~BST();
    void release(BSTnode<T>* node);
    void insert(T x);
    void addLchild(BSTnode<T>* father,T x);
    void addRchild(BSTnode<T>* father,T x);
    void defineroot(T x);
    void visit(BSTnode<T>* node);
    void levelorder();
    void upper();
private:
    BSTnode<T>* root;
};
template<class T>
void BST<T>::release(BSTnode<T>* node){
    if(node->Lchild)release(node->Lchild);
    if(node->Rchild)release(node->Rchild);
    delete[]node;
}
template<class T>
BST<T>::~BST(){if(root) release(root);}
template<class T>
void BST<T>::addLchild(BSTnode<T>* father,T x){
    if(father->Lchild!=0)throw invalid_argument("No place!");
    auto* temp=new BSTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    father->Lchild=temp;
}
template<class T>
void BST<T>::addRchild(BSTnode<T>* father,T x){
    if(father->Rchild!=0)throw invalid_argument("No place!");
    auto* temp=new BSTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    father->Rchild=temp;
}
template<class T>
void BST<T>::defineroot(T x){
    if(root)throw invalid_argument("No place!");
    root=new BSTnode<T>;
    root->data=x;
    root->Lchild=root->Rchild=0;
}
template<class T>
void BST<T>::insert(T x){
    if(!root){defineroot(x);return;}
    BSTnode<T>* temp=root;
    while(true){
        if(temp->data<x){
            if(temp->Rchild)temp=temp->Rchild;
            else{addRchild(temp,x);break;}
        }
        else{
            if(temp->Lchild)temp=temp->Lchild;
            else{addLchild(temp,x);break;}
        }
    }
}
template<class T>
void BST<T>::visit(BSTnode<T>* node){
    cout<<node->data<<'(';
    if(node->Lchild)cout<<node->Lchild->data;
    else cout<<'#';
    cout<<',';
    if(node->Rchild)cout<<node->Rchild->data;
    else cout<<'#';
    cout<<") ";
}
template<class T>
void BST<T>::levelorder(){
    MQ<BSTnode<T>*> order;
    int count=0,countc=1,countt=0;
    if(root!=0)
        order.push(root);
    while(!order.empty()){
        visit(order.front());count++;
        if(order.front()->Lchild)order.push(order.front()->Lchild);
        else countt++;
        if(order.front()->Rchild)order.push(order.front()->Rchild);
        else countt++;
        if(count==countc){cout<<'\n';countc=countc*2+1;count+=countt;countt*=2;}
        order.pop();
    }
}
template<class T>
void BST<T>::upper(){
    while(root) {
        BSTnode<T> *temp = root;
        if (!temp->Lchild) {
            cout << temp->data << ' ';
            root=temp->Rchild;
            delete[] temp;
        }
        else{
            while(temp->Lchild->Lchild)
                temp=temp->Lchild;
            cout<<temp->Lchild->data<<' ';
            BSTnode<T>*temp1=temp->Lchild;
            temp->Lchild=temp->Lchild->Rchild;
            delete[]temp1;
        }
    }
    cout<<'\n';
}
template<class T>
class BT;
template<class T>
class BTnode{
public:
    friend class BT<T>;
private:
    T data;
    BTnode<T> *Lchild,*Rchild,*Father;
    int depth;
};
template<class T>
class BT{
public:
    BT(){root=0;}
    ~BT();
    void release(BTnode<T>* node);
    void addLchild(BTnode<T>* father,T x);
    void addRchild(BTnode<T>* father,T x);
    void defineroot(T x);
    void make(int*bt,int& length);
    void visit(BTnode<T>* node);
    void levelorder();
    void getpath(BTnode<T>* m,int k);
    BTnode<T>* getroot();
private:
    BTnode<T>* root;
};
template<class T>
void BT<T>::release(BTnode<T>* node){
    if(node->Lchild)release(node->Lchild);
    if(node->Rchild)release(node->Rchild);
    delete[]node;
}
template<class T>
BT<T>::~BT(){if(root) release(root);}
template<class T>
void BT<T>::addLchild(BTnode<T>* father,T x){
    if(father->Lchild!=0)throw invalid_argument("No place!");
    auto* temp=new BTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    temp->Father=father;
    temp->depth=father->depth+1;
    father->Lchild=temp;
}
template<class T>
void BT<T>::addRchild(BTnode<T>* father,T x){
    if(father->Rchild!=0)throw invalid_argument("No place!");
    auto* temp=new BTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    temp->Father=father;
    temp->depth=father->depth+1;
    father->Rchild=temp;
}
template<class T>
void BT<T>::defineroot(T x){
    if(root)throw invalid_argument("No place!");
    root=new BTnode<T>;
    root->data=x;
    root->Lchild=root->Rchild=0;
    root->Father=0;
    root->depth=1;
}
template<class T>
BTnode<T>* BT<T>::getroot(){
    if(!root)throw invalid_argument("Empty!");
    return root;
}
template<class T>
void BT<T>::make(int*bt,int& length){
    defineroot(bt[1]);
    MQ<BTnode<T>*> mk;
    mk.push(root);
    int fb=1;
    while(fb<length){
        if(bt[++fb]!=nu){
            addLchild(mk.front(),bt[fb]);
            mk.push(mk.front()->Lchild);
        }
        if(bt[++fb]!=nu){
            addRchild(mk.front(),bt[fb]);
            mk.push(mk.front()->Rchild);
        }
        mk.pop();
    }
}
template<class T>
void BT<T>::visit(BTnode<T>* node){
    cout<<node->data<<'(';
    if(node->Lchild)cout<<node->Lchild->data;
    else cout<<'#';
    cout<<',';
    if(node->Rchild)cout<<node->Rchild->data;
    else cout<<'#';
    cout<<") ";
}
template<class T>
void BT<T>::levelorder(){
    MQ<BTnode<T>*> order;
    int count=0,countc=1,countt=0;
    if(root!=0)
        order.push(root);
    while(!order.empty()){
        visit(order.front());count++;
        if(order.front()->Lchild)order.push(order.front()->Lchild);
        else countt++;
        if(order.front()->Rchild)order.push(order.front()->Rchild);
        else countt++;
        if(count==countc){cout<<'\n';countc=countc*2+1;count+=countt;countt*=2;}
        order.pop();
    }
}
template<class T>
void BT<T>::getpath(BTnode<T>* m,int k){
    BTnode<T>* ancestor=0;
    int* dt=new int[m->depth];
    int score=0,position=0;
    do{
        if(!ancestor)ancestor=m;
        else ancestor=ancestor->Father;
        score+=ancestor->data+ancestor->depth;
        dt[position++]=ancestor->data;
        if(score==k){
            for(int g=position-1;g>=0;g--){
                cout<<dt[g]<<' ';
            }
            cout<<'\n';
        }
    }
    while(ancestor!=root);
    if(m->Lchild)getpath(m->Lchild,k);
    if(m->Rchild)getpath(m->Rchild,k);
}
void op1(){
    BST<double> A;
    double a;
    do{cin>>a;A.insert(a);}
    while(getchar()!='\n');
    A.levelorder();
    A.upper();
}
void op2(){
    int B[100000],length=0,num=0,k;
    bool p=0;
    char u;
    cin>>u;
    while(u!=']'){
        cin>>u;
        if(u=='#'){
            B[++length]=nu;
            cin>>u;
        }
        else{
            while(u!=','){
                if(u=='-')p=1;
                else{num*=10,num+=(u-'0');}
                cin>>u;
            }
            if(p)num*=-1;
            B[++length]=num;num=0,p=0;
        }
    }
    while(getchar()!='=');
    cin>>k;
    BT<int>tree;
    tree.make(B,length);
    tree.levelorder();
    tree.getpath(tree.getroot(),k);
}
int main() {
    op1();
    op2();
    return 0;
}
/*
7 2 9 1 5 4 6
[8,3,9,11,2,#,13,6,7,#,4,8,#,#,5,-2,#,1,#,-3,#],K=28
*/