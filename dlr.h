#ifndef DLR_H
#define DLR_H
#include <iostream>
#include <algorithm>
using namespace std;


template <typename key, typename info>
class dlr{ //single linked list
private:
    struct element{  //struct is declared in private scope in order to protect it from functions outside the class
        key id;
        info data;
        element* previous;
        element* next;
    };
    element *head;
    element *tail;

    int length;
    void removeAllElements(){ //remove all elements
        element *etr = head;
        for (int i=0;i<length;i++){
            etr = etr->next;
            delete head;
            head = etr;
        }
        length = 0;
    };
    void copyAllElements(const dlr& obj){ //copy all elements
        element* xtr = obj.head;
        //element* etr = tail;
        for (int i=0;i<obj.length;i++){
            pushBack(xtr->id, xtr->data);
            xtr = xtr->next;
        }
    };





public:
    int getLength() const{ //method to get the length
        return length;
    };

    //typedef custIterator<const int> const_iterator;
    class custIterator
    {
        friend class dlr;
    private:
        custIterator(element* item){ //constructor with one argument for iterator
            this->item = item;
        };
        element* item;


    public:
        custIterator(const custIterator& obj){//copy constructor
            this->item = obj.item;
        };

        bool operator!=(custIterator const& obj) const{//operator!= overloading for iterator
            return this->item->data!=obj.item->data||this->item->id!=obj.item->id;
        };
        bool operator==(custIterator const& obj) const{//operator== overloading for iterator
            return this->item->data==obj.item->data&&this->item->id==obj.item->id;
        }; //need for BOOST_FOREACH
//two get methods
        info getD() const{
            return item->data;
        }
        key getI() const{
            return item->id;
        }
        custIterator& operator++(){//prefix operator++ overloading for iterator
            this->item = this->item->next;
            return *this;
        };
        custIterator& operator--(){//prefix operator-- overloading for iterator
            this->item = this->item->previous;
            return *this;
        };



    };

    typedef custIterator iterator;
    dlr(){ //empty constructor
        head = NULL;
        tail = NULL;
        length = 0;
    };
    ~dlr(){ //destructor
        removeAllElements();
    };
    void pushFront(key id, info data){ //insert at head
        element* pl = new element;
        pl->id = id;
        pl->data =data;
        pl->next = this->head;
        pl->previous = this->tail;
        if (length>0){
            this->head->previous = pl;
        }

        this->head = pl;
        if (length>0){
            this->tail->next = pl;
        } else {
            this->tail = pl;
        }
        length++;

    };

    void insertAt(key id, info data, int pos){//insert at a particular position
        if (pos==0 || length==0){
            pushFront(id, data);
            return;
        }
        if (pos%length==0){
            pushBack(id, data);
            return;
        }
        element* placeBefore = head;
        for (int i=0;i<pos;i++){
            placeBefore = placeBefore->next;
        }
        element* pl = new element;
        pl->id = id;
        pl->data =data;
        pl->next = placeBefore;
        pl->previous = placeBefore->previous;
        pl->previous->next = pl;
        pl->next->previous = pl;
        length++;
    };

    void pushBack(key id, info data){//insert element at tail
        element* pl = new element;
        pl->id = id;
        pl->data =data;
        pl->next = this->head;
        pl->previous = this->tail;
        if (length>0){
            this->head->previous = pl;
        }

        //this->head = pl;
        if (length>0){
            this->tail->next = pl;
        } else {
            this->head = pl;
        }
        this->tail = pl;
        length++;
    };
    //two basic iterator functions
    iterator begin() const{
        return custIterator(head);
    };
    iterator end() const{
        return custIterator(tail);
    };

    void removeElement (int pos){//function to remove an element at a particular position
        if (this->length==0){
            return;
        } else if (this->length==1){
            delete head;
            return;
        }

        element* current = this->head;
        for (int i=0;i<pos;i++){
            current = current->next;
        }

        current->previous->next = current->next;
        current->next->previous = current->previous;

        if (pos%this->length==0){
            head = current->next;
        } else if (pos%this->length==this->length-1){
            tail = current->previous;
        }

        delete current;
        length--;
    };
//two get functions needed to access the data from element without exposing pointers
    info getData(int n) const{
        element* current = this->head;
        for (int i=0;i<n-1;i++){
            if (current->next!=nullptr){
                current = current->next;
            }
        }
        return current->data;
    };
    key getId(int n) const{
        element* current = this->head;
        for (int i=0;i<n-1;i++){
            if (current->next!=nullptr){
                current = current->next;
            }
        }
        return current->id;
    };

    void print() const{//print function
        element* current = this->head;
        for (int i=0; i<this->length; i++){

            cout<<current->data<< " ";
            current = current->next;
        }
        cout<<endl;
        cout<<endl;
    };

    dlr (const dlr & obj){//copyconstructor
        head = NULL;
        tail = NULL;
        length = 0;
        copyAllElements(obj);
    };
    dlr & operator=(const dlr & obj){//assignment operator overloading
        if(this==&obj)
            return *this;
        removeAllElements();
        copyAllElements(obj);
        return *this;
    };
    dlr operator+(const dlr & obj){//operator+ overloading
        element* current =obj.head;
        //element * temp = this->head;
        dlr resultM;
        resultM = *this;
        for (int i=0; i<obj.length;i++)
        {
            resultM.pushBack(current->id, current->data);
            current = current->next;
        }
        //resultM.sortTheListById();
        return resultM;

    };
    dlr operator-(const dlr & obj){//operator- overloading
        element * current = obj.head;
        element * temp = this->head;
        dlr resultM;

        resultM = *this;

        for (int i=0;i<obj.length;i++)
        {
            resultM.removeElement(current->id);
        }
        resultM.sortTheListById();
        return resultM;
    }; //-operator overriding


    bool isEmpty() const{ //function to check if dlr is empty
        if (length>0){
            return false;
        } else {
            return true;
        }
    };







};


template <typename key, typename info>//produce function allows two create a third dlr out of 2 supplied as arguments along with other correct input
dlr<key, info> produce (const dlr<key,info>& ring1, int start1, int step1, bool dir1,
                        const dlr<key,info>& ring2, int start2, int step2, bool dir2,
                        int num, bool dir){
    dlr<key,info> ring3;
    try{
        if (ring1.getLength()<2&&ring1.getLength()<=start1){
            throw 1;
        }
        if (ring2.getLength()<2&&ring2.getLength()<=start2){
            throw 2;
        }

    } catch (int j){
        cerr <<j<<" ring position is unacceptable"<<endl;
        return ring3;
    }


    auto iter1 = ring1.begin();
    auto iter2 = ring2.begin();
    if(dir1){
        for (int i=0;i<start1;i++){
            ++iter1;
        }
    } else{
        for (int i=0;i<start1;i++){
            --iter1;
        }
    }

    if(dir2){
        for (int i=0;i<start2;i++){
            ++iter2;
        }
    } else{
        for (int i=0;i<start2;i++){
            --iter2;
        }
    }
    for (int j=0;j<num;j++){

        for (int k=0;k<step1;k++){
            if (dir){
                ring3.pushBack(iter1.getI(), iter1.getD());
            } else {
                ring3.pushFront(iter1.getI(), iter1.getD());
            }

            if (dir1){
                ++iter1;
            } else {
                --iter1;
            }
        }

        for (int l=0;l<step2;l++){ //first elements from first sequence inserted
            if (dir){
                ring3.pushBack(iter2.getI(), iter2.getD());
            } else {
                ring3.pushFront(iter2.getI(), iter2.getD());
            }
            if (dir2){
                ++iter2;
            } else {
                --iter2;
            }
        }


    }

    return ring3;




};



#endif // DLR_H
