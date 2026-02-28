#include<iostream>
#include<cstring>
using namespace std;
template<class T>
class chainnode;
template<class T>
class chain{
public:
    chain();
    ~chain();
    void insert(int k,T x);//将x插入到链表的第k个结点之后
    void output();//输出链表
    T find(T x);//寻找链表第一个存储比x大的数的结点（x取数值上限时等效查找链表结点数量）
    T rfind(T x);//寻找链表第一个存储比x小的数的结点
    void paste(chain<T> &dest);//（需保证本链表原结点按照升序存储）将dest链表中的结点依次加入本链表中，并保持升序存储
    T erase(int k);//删除链表中第k个结点，并返回原来结点的值
    void samebreaker();//（需保证本链表原结点按照升/降序存储）将存储数据相同的结点唯一化
    void plus(chain<T> &p1,chain<T> &p2);//将p1，p2链表中的数据按十进位制进位相加
private:
    chainnode<T>* first;
};
template<class T>
class chainnode{
    friend chain<T>;
private:
    T data;
    chainnode<T>* link;
};
template<class T>
chain<T>::chain(){
    first=new chainnode<T>;
    first->link=nullptr;
}
template<class T>
chain<T>::~chain(){
    chainnode<T>* next;
    while(first){
        next=first->link;
        delete[] first;
        first=next;
    }
}
template<class T>
void chain<T>::insert(int k,T x){
    auto *p=new chainnode<T>;
    p->data=x;
    chainnode<T> *q=first;
    for(int num=0;num<k;num++)
        q=q->link;
    p->link=q->link;
    q->link=p;
}
template<class T>
void chain<T>::output(){
    chainnode<T>* next=first->link;
    while(next){
        cout<<next->data;
        next=next->link;
        if(next)
            cout<<"->";
    }
    cout<<'\n';
}
template<class T>
T chain<T>::find(T x){
    chainnode<T>* next=first->link;
    int n=0;
    while(next){
        if(next->data<=x)
            n++;
        else
            return n;
        next=next->link;
    }
    return n;
}
template<class T>
T chain<T>::rfind(T x){
    chainnode<T>* next=first->link;
    int n=0;
    while(next){
        if(next->data>=x)
            n++;
        else
            return n;
        next=next->link;
    }
    return n;
}
template<class T>
void chain<T>::paste(chain<T>& dest){
    chainnode<T>* next=dest.first->link;
    while(next){
        T k=next->data;
        this->insert(this->find(k),k);
        next=next->link;
    }
}
template<class T>
T chain<T>::erase(int k){
    chainnode<T>* next=first;
    for(int a=1;a<k;a++)
        next=next->link;
    chainnode<T>* temp=next->link->link;
    T n=next->link->data;
    delete[] next->link;
    next->link=temp;
    return n;
}
template<class T>
void chain<T>::samebreaker(){
    chainnode<T>* next=first->link;
    int k=1;
    while(next && next->link){
        if(next->data==next->link->data){
            erase(k+1);
            continue;
        }
        else {
            k++;
            next = next->link;
        }
    }
}
template<class T>
void chain<T>::plus(chain<T>& p1,chain<T>& p2){
    chainnode<T> *op1=p1.first,*op2=p2.first;
    int temp=0,n=0;
    do{
        if(op1->link){
            op1=op1->link;
            temp+=op1->data;
        }
        if(op2->link){
            op2=op2->link;
            temp+=op2->data;
        }
        insert(n,temp%10);
        n++;
        temp/=10;
    }
    while(temp||op1->link||op2->link);
}
void op1(){//(1)-(2)
    //(1)
    chain<int> A,B;
    for(int num=0;num<4;num++){
        int x;
        cin>>x;
        A.insert(A.find(x),x);
    }
    cout<<"A:";
    A.output();
    for(int num=0;num<5;num++){
        int x;
        cin>>x;
        B.insert(B.rfind(x),x);
    }
    cout<<"B:";
    B.output();
    chain<int> C;
    C.paste(A);
    C.paste(B);
    C.samebreaker();
    cout<<"C:";
    C.output();
    //(2)
    int m;
    cin>>m;
    cout<<C.erase(C.find(2147483647)-m+1)<<'\n';
}
void op2(){//(3)
    chain<int> D,E;
    char d[10],e[10];
    cin>>d>>e;
    for(int num=0;num<strlen(d);num++)
        D.insert(0,d[num]-'0');
    for(int num=0;num<strlen(e);num++)
        E.insert(0,e[num]-'0');
    chain<int> F;
    F.plus(D,E);
    F.output();
}
int main(){
    op1();
    op2();
    return 0;
}