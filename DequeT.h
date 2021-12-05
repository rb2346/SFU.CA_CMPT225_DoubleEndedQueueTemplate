#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class NodeT{
public:
    T data;
    NodeT* next;

    // Constructors

    NodeT();
    NodeT(T);
    NodeT(T , NodeT*);
};

template <typename T>
NodeT<T>::NodeT(){
    data = NULL;
    next = nullptr;
}

template <typename T>
NodeT<T>::NodeT(T inpdata){
    data = inpdata;
    next = nullptr;
}

template <typename T>
NodeT<T>::NodeT(T inpdata, NodeT* inpnode){
    data = inpdata;
    next = inpnode;
}

template <typename T>
class QueueT{
private:
    NodeT<T>* front;
    NodeT<T>* back;
    int cur_size;
public:
    QueueT();
    QueueT(const QueueT<T> &);
    ~QueueT();
    QueueT<T> & operator=(const QueueT<T> &);

    void enqueue(T);
    T dequeue();

    void print() const;

    bool empty() const;

    int size() const;

    void concatenate(QueueT<T> &, int);
    QueueT<T> merge(const QueueT<T> &);

    NodeT<T>* getFront() const{ return front; };
};

template <typename T>
QueueT<T>::QueueT() {
    front = nullptr;
    back = nullptr;
    cur_size = 0;
}

template <typename T>
QueueT<T>::QueueT(const QueueT<T> &q) {
    cur_size = q.size();
    NodeT<T>* tmp = q.getFront();
    front = new NodeT<T>();
    NodeT<T>* cur_ptr = front;
    while(tmp != nullptr){
        cur_ptr->data = tmp->data;
        if(tmp->next != nullptr) {
            cur_ptr->next = new NodeT<T>();
            cur_ptr = cur_ptr->next;
        }
        tmp = tmp->next;
    }
    back = cur_ptr;
}

template <typename T>
QueueT<T>::~QueueT<T>() {
    if(!empty()){
        NodeT<T>* curPtr = front;
        NodeT<T>* tempPtr;
        while(curPtr != nullptr){
            tempPtr = curPtr;
            curPtr = curPtr->next;
            delete tempPtr;
        }
    }
}

template <typename T>
QueueT<T> & QueueT<T>::operator=(const QueueT<T> &q) {
    QueueT<T>* tmp = new QueueT<T>(q);
    front = tmp->getFront();
    back = tmp->back;
    cur_size = tmp->size();
    return *this;
}

template <typename T>
void QueueT<T>::enqueue(T arg) {
    NodeT<T>* cur_ptr = getFront();
    if(cur_ptr != nullptr){
        while(cur_ptr->next != nullptr)
            cur_ptr = cur_ptr->next;
        cur_ptr->next = new NodeT<T>(arg);
        cur_size++;
        back = cur_ptr->next;
    } else {
        front = back = new NodeT<T>(arg);
        cur_size++;
    }

}

template <typename T>
T QueueT<T>::dequeue() {
    if(!empty()){
        T tmp = front->data;
        front = front->next;
        cur_size--;
        return tmp;
    } else {
        throw runtime_error(" > Dequeue Failed. Runtime Error.");
    }

}

template <typename T>
void QueueT<T>::print() const {
    NodeT<T>* tmp = front;
    while (tmp != nullptr){
        cout << tmp->data << endl;
        tmp = tmp->next;
    }
}

template <typename T>
bool QueueT<T>::empty() const {
    if(cur_size == 0)
        return true;
    else
        return false;
}

template <typename T>
int QueueT<T>::size() const {
    return cur_size;
}

template <typename T>
void QueueT<T>::concatenate(QueueT<T> &q, int n) {
    if(n > q.size())
        throw runtime_error(" > Concatenation Failed. Runtime Error.");
    else{
        for(int i = 0; i < n; i++){
            T tmp = q.dequeue();
            enqueue(tmp);
        }
    }
}

template <typename T>
QueueT<T> QueueT<T>::merge(const QueueT<T> &q) {
    int n = (q.size() >= size()) ? q.size()  : size();
    QueueT<T> result;
    NodeT<T>* tmp1 = getFront();
    NodeT<T>* tmp2 = q.getFront();
    for(int i = 0; i < n; i++){
        if(tmp1 != nullptr){
            result.enqueue(tmp1->data);
            tmp1 = tmp1->next;
        }
        if(tmp2 != nullptr){
            result.enqueue(tmp2->data);
            tmp2 = tmp2->next;
        }
    }
    return result;
}