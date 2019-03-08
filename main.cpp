#include <iostream>
#include "dlr.h"
using namespace std;

int main(int argc, char *argv[])
{
    dlr<int, int> d1;
    d1.pushBack(1, 10);
    d1.pushBack(2, 20);
    d1.pushBack(3, 30);
    d1.pushBack(3, 40);
    //d1.pushMiddle(17, 17, 3);
    d1.pushBack(1, 50);
    d1.pushBack(2, 60);
    d1.pushBack(3, 70);
    d1.pushBack(3, 80);
    //d1.removeElement(3);

    d1.print();
    dlr<int, int> d2;//(d1);
    //d2 = d1;
    //d2.print();
    //d1 = d1+d2;
    d2.pushBack(1, 15);
    d2.pushBack(2, 25);
    d2.pushBack(3, 35);
    d2.pushBack(3, 45);
    d2.print();
    //typename dlr<int, int>::iterator myIter = d1.begin();
    //--myIter;
    //cout<<myIter.getD()<<endl;
    produce(d1, 1, 3, true, d2, 1, 1, true, 3, true).print();
    //cout << "Hello World!" << endl;
    return 0;
}
