#include <iostream>
#include <stack>
using namespace std;
template<class T>
class myqueue{
public:
    myqueue();
    ~myqueue(){delete que;}
    void enqueue(T x);
    void sorted_enqueue(T x);
    T dequeue_front();
    T peek_front();
    T peek_back(){return que->top();}
    T dequeue_back();
    int queue_size(){return que->size();}
    bool is_empty(){return que->empty();}
private:
    stack<T>* que;
};
template<class T>
myqueue<T>::myqueue(){
    que=new stack<T>;
}
template<class T>
void myqueue<T>::enqueue(T x){
    que->push(x);
}
template<class T>
void myqueue<T>::sorted_enqueue(T x) {
    while((!is_empty())&&x<peek_back()){
        dequeue_back();
    }
    enqueue(x);
}
template<class T>
T myqueue<T>::dequeue_front(){
    auto* temp=new stack<T>;
    T t1,t;
    while(!que->empty()){
        t=que->top();
        que->pop();
        temp->push(t);
    }
    t=temp->top();
    temp->pop();
    while(!temp->empty()){
        t1=temp->top();
        temp->pop();
        que->push(t1);
    }
    delete temp;
    return t;
}
template<class T>
T myqueue<T>::peek_front(){
    auto* temp=new stack<T>;
    T t1,t;
    while(!que->empty()){
        t=que->top();
        que->pop();
        temp->push(t);
    }
    t=temp->top();
    while(!temp->empty()){
        t1=temp->top();
        temp->pop();
        que->push(t1);
    }
    delete temp;
    return t;
}
template <class T>
T myqueue<T>::dequeue_back() {
    T t,t1;
    auto* temp=new myqueue<T>;
    while(!que->empty()){
        t1=dequeue_front();
        temp->enqueue(t1);
    }
    t=temp->peek_back();
    while(!temp->is_empty()){
        t1=temp->dequeue_front();
        if(!temp->is_empty())
            que->push(t1);
    }
    return t;
}
void op1(){
    double n;
    myqueue<double>ex;
    do {
        scanf("%lf", &n);
        ex.enqueue(n);
    }
    while (getchar()==',');
    cout<<"back:"<<ex.peek_back()<<"\nfront:"<<ex.peek_front();
    cout<<"\ndequeue front:"<<ex.dequeue_front()<<"\ndequeue back:"<<ex.dequeue_back();
    while(!ex.is_empty()){
        cout<<"\ndequeue front:"<<ex.dequeue_front();
    }
    cout<<"\nempty.\n";
}
void op2(){
    int num[10000],size=0,k;
    while (getchar()!='[');
    do scanf("%d",&num[size++]);
    while(getchar()!=']');
    while (getchar()!='=');
    scanf("%d",&k);
    myqueue<int> sorted_queue,num_que;
    for(int a=0;a<k-1;a++) {
        int t=sorted_queue.queue_size();
        sorted_queue.sorted_enqueue(num[a]);
        while(t+1>sorted_queue.queue_size()){
            num_que.dequeue_back();
            t--;
        }
        num_que.sorted_enqueue(a);
    }
    printf("[");
    for(int a=k-1;a<size;a++){
        if(a-num_que.peek_front()>=k){
            sorted_queue.dequeue_front();
            num_que.dequeue_front();
        }
        int t=sorted_queue.queue_size();
        sorted_queue.sorted_enqueue(num[a]);
        while(t+1>sorted_queue.queue_size()){
            num_que.dequeue_back();
            t--;
        }
        num_que.sorted_enqueue(a);
        printf("%d",sorted_queue.peek_front());
        if(a<size-1)printf(",");
    }
    printf("]");
}
int main() {
    op1();
    op2();
    return 0;
}
//in 3.5,4.5,5.5,6.5,7.5 nums=[4,-2,1,6,-5,8,9,3],k=3
