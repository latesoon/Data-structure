#include <iostream>
using namespace std;

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
class BT;
template<class T>
class BTnode{
public:
    friend class BT<T>;
private:
    T data;
    BTnode<T> *Lchild,*Rchild;
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
    void maketreeforPI(T* pre,T* in,int len);
    void makeLtreeforPI(BTnode<T>* father,int start,int end,T* pre,T* in);
    void makeRtreeforPI(BTnode<T>* father,int start,int end,T* pre,T* in);
    void visit(BTnode<T>* node);
    void levelorder();
    int height(int x);
    int measureheight(BTnode<T>* node);
    BTnode<T>* search(int x);
    void turning(int x);
    BTnode<T>* searchfather(int x);
    void turnright(BTnode<T>* father);
    void turnleft(BTnode<T>* father);
    int countnode(BTnode<T>* base=0);
    void makeperfect();
    void cutnode(MQ<BTnode<T>*>& temp,int nodenum);
    void iscut(MQ<BTnode<T>*>& temp,BTnode<T>* jud,int pos,int nodenum);
    void addnode(MQ<BTnode<T>*>& temp,int nodenum);
    void isadd(MQ<BTnode<T>*>& temp,BTnode<T>* jud,int pos,int nodenum);
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
BT<T>::~BT(){release(root);}
template<class T>
void BT<T>::addLchild(BTnode<T>* father,T x){
    if(father->Lchild!=0)throw invalid_argument("No place!");
    auto* temp=new BTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    father->Lchild=temp;
}
template<class T>
void BT<T>::addRchild(BTnode<T>* father,T x){
    if(father->Rchild!=0)throw invalid_argument("No place!");
    auto* temp=new BTnode<T>;
    temp->data=x;
    temp->Lchild=temp->Rchild=0;
    father->Rchild=temp;
}
template<class T>
void BT<T>::defineroot(T x){
    if(root!=0)throw invalid_argument("No place!");
    root=new BTnode<T>;
    root->data=x;
    root->Lchild=root->Rchild=0;
}
template<class T>
void BT<T>::makeLtreeforPI(BTnode<T>* father,int start,int end,T* pre,T* in){
    if(start>end)return;
    addLchild(father,pre[start]);
    if(start==end)return;
    int i;
    for(i=start;i<=end;i++)if(in[i]==pre[start])break;
    for(int j=i;j>start;j--)in[j]=in[j-1];
    makeLtreeforPI(father->Lchild,start+1,i,pre,in);
    makeRtreeforPI(father->Lchild,i+1,end,pre,in);
}
template<class T>
void BT<T>::makeRtreeforPI(BTnode<T>* father,int start,int end,T* pre,T* in){
    if(start>end)return;
    addRchild(father,pre[start]);
    if(start==end)return;
    int i;
    for(i=start;i<=end;i++)if(in[i]==pre[start])break;
    for(int j=i;j>start;j--)in[j]=in[j-1];
    makeLtreeforPI(father->Rchild,start+1,i,pre,in);
    makeRtreeforPI(father->Rchild,i+1,end,pre,in);
}
template<class T>
void BT<T>::maketreeforPI(T* pre,T* in,int len){
    if(len<=0)throw invalid_argument("Invalid input!");
    defineroot(pre[0]);
    int i;
    for(i=0;i<len;i++)if(in[i]==pre[0])break;
    for(int j=i;j>0;j--)in[j]=in[j-1];
    makeLtreeforPI(root,1,i,pre,in);
    makeRtreeforPI(root,i+1,len-1,pre,in);
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
BTnode<T>* BT<T>::search(int x){
    MQ<BTnode<T>*> order;
    if(root!=0)
        order.push(root);
    while(!order.empty()){
        if(order.front()->data==x){return order.front();}
        if(order.front()->Lchild)order.push(order.front()->Lchild);
        if(order.front()->Rchild)order.push(order.front()->Rchild);
        order.pop();
    }
    throw invalid_argument("Not found!");
}
template<class T>
BTnode<T>* BT<T>::searchfather(int x){
    MQ<BTnode<T>*> order;
    if(root->data==x)throw invalid_argument("Can not turn root!");
    if(root!=0)
        order.push(root);
    while(!order.empty()){
        if(order.front()->Lchild){
            order.push(order.front()->Lchild);
            if(order.front()->Lchild->data==x)
                return order.front();
        }
        if(order.front()->Rchild){
            order.push(order.front()->Rchild);
            if(order.front()->Rchild->data==x)
                return order.front();
        }
        order.pop();
    }
    throw invalid_argument("Not found!");
}
template<class T>
int BT<T>::height(int x){
    return measureheight(search(x));
}
template<class T>
int BT<T>::measureheight(BTnode<T>* node){
    int ans=1;
    if(node->Lchild)ans=max(ans,measureheight(node->Lchild)+1);
    if(node->Rchild)ans=max(ans,measureheight(node->Rchild)+1);
    return ans;
}
template<class T>
void BT<T>::turnright(BTnode<T>* father){
    if(root==father)root=father->Lchild;
    else{
        auto* grandfather=searchfather(father->data);
        if(grandfather->Lchild==father)grandfather->Lchild=father->Lchild;
        else grandfather->Rchild=father->Lchild;
    }
    auto* temp=father->Lchild->Rchild;
    father->Lchild->Rchild=father;
    father->Lchild=temp;
}
template<class T>
void BT<T>::turnleft(BTnode<T>* father){
    if(root==father)root=father->Rchild;
    else{
        auto* grandfather=searchfather(father->data);
        if(grandfather->Lchild==father)grandfather->Lchild=father->Rchild;
        else grandfather->Rchild=father->Rchild;
    }
    auto* temp=father->Rchild->Lchild;
    father->Rchild->Lchild=father;
    father->Rchild=temp;
}
template<class T>
void BT<T>::turning(int x){
    auto* father=searchfather(x);
    if(father->Lchild&&father->Lchild->data==x)turnright(father);
    else turnleft(father);
}
template<class T>
int BT<T>::countnode(BTnode<T>* base){
    if(!base) base=root;
    if(!base) return 0;
    int nodenum=1;
    if(base->Lchild)nodenum+=countnode(base->Lchild);
    if(base->Rchild)nodenum+=countnode(base->Rchild);
    return nodenum;
}
template<class T>
void BT<T>::iscut(MQ<BTnode<T>*>& temp,BTnode<T>* jud,int pos,int nodenum){
    if(jud->Lchild){
        iscut(temp,jud->Lchild,pos*2,nodenum);
        if(pos*2>nodenum){temp.push(jud->Lchild);jud->Lchild=0;}
    }
    if(jud->Rchild){
        iscut(temp,jud->Rchild,pos*2+1,nodenum);
        if(pos*2+1>nodenum){temp.push(jud->Rchild);jud->Rchild=0;}
    }
}
template<class T>
void BT<T>::cutnode(MQ<BTnode<T>*>& temp,int nodenum){
    if(!root)return;
    iscut(temp,root,1,nodenum);
}
template<class T>
void BT<T>::isadd(MQ<BTnode<T>*>& temp,BTnode<T>* jud,int pos,int nodenum) {
    if(pos*2<=nodenum){
        if(!jud->Lchild){jud->Lchild=temp.front();temp.pop();}
        isadd(temp,jud->Lchild,pos*2,nodenum);
    }
    if(pos*2+1<=nodenum){
        if(!jud->Rchild){jud->Rchild=temp.front();temp.pop();}
        isadd(temp,jud->Rchild,pos*2+1,nodenum);
    }
}
template<class T>
void BT<T>::addnode(MQ<BTnode<T>*>& temp,int nodenum){
    if(!root)return;
    isadd(temp,root,1,nodenum);
}
template<class T>
void BT<T>::makeperfect(){
    int nodenum=countnode();
    MQ<BTnode<T>*> temp;
    cutnode(temp,nodenum);
    if(temp.empty())cout<<"True\n";
    else {
        cout<<"False\n";
        addnode(temp,nodenum);
    }
}
int main() {
    int pre[100],in[100],pos=0;
    while(getchar()!='[');
    do cin>>pre[pos++];
    while(getchar()!=']');
    pos=0;
    while(getchar()!='[');
    do cin>>in[pos++];
    while(getchar()!=']');
    BT<int> A;
    A.maketreeforPI(pre,in,pos);
    A.levelorder();
    int x;
    cin>>x;
    cout<<A.height(x)<<'\n';
    A.turning(x);
    A.levelorder();
    A.makeperfect();
    A.levelorder();
    return 0;
}
//INPUT1:[3,9,4,8,1,20,15,17] [4,9,8,1,3,15,20,17]
//INPUT1strength:[1,2,4,8,16,9,18,19,38,39,5,10,11,3,6,12,13][16,8,4,18,9,38,19,39,2,10,5,11,1,12,6,13,3]
//INPUT2:9