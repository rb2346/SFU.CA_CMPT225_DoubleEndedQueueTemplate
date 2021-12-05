#include <iostream>
#include "DequeT.h"

using namespace std;

void simpleTest()
{
    cout << "SIMPLE TEST" << endl;
    QueueT<int> q1;

    q1.enqueue(2);
    q1.enqueue(4);
    q1.enqueue(6);

    cout << "empty: 0 = " << q1.empty() << endl;
    cout << "print: {2,4,6} = ";
    q1.print();
    cout << endl << "size: 3 = " << q1.size() << endl;

    QueueT<int> q2(q1);
    QueueT<int> q3;
    q3 = q1;

    q1.dequeue();

    cout << "q1 post copy: {4,6} = ";
    q1.print();
    cout << endl << "q2 (copy): {2,4,6} = ";
    q2.print();
    cout << endl << "q3 (op=): {2,4,6} = ";
    q3.print();

    QueueT<int> q4;
    q4.enqueue(5);

    QueueT<int> q5(q1.merge(q4));
    cout << endl << "q5 (merge): {4,5,6} = ";
    q5.print();

    q1.concatenate(q4, 1);
    cout << endl << "q1 (concatenate): {4,6,5} = ";
    q1.print();

    NodeT<int>* front = q1.getFront();
    cout << endl << "front->next->data: 6 = " << front->next->data << endl;
    cout << "END SIMPLE TEST" << endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    simpleTest();
    return 0;
}
