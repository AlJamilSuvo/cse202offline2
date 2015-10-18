#include<iostream>
#include <cstdio>
#include <string>
#include <stdio.h>
using namespace std;

class Element {
private:
    Element * next;
	Element * prev;
	int value;
public:
	void setNext(Element *n) {
		next = n;
	}
	Element * getNext() {
		return next;
	}
	void setPrev(Element *p) {
		prev  = p;
	}
	Element * getPrev() {
		return prev;
	}
	void setValue(int v) {
		value = v;
	}
	int getValue() {
		return value;
	}
};

class LinkedListBase {
protected:
	Element * head;
	Element * tail;
	int size;
public:
	LinkedListBase() {
        head=new Element;
        tail=new Element;
		head->setNext(tail);
		tail->setPrev(head);
		size = 0;
    }
	int getSize() {
		return size;
	}
	~LinkedListBase() {
		delete head;
		delete tail;
	}
};

class LinkedList: public LinkedListBase {
private:
    Element * getAdress(int index);
public :
    void add(Element e);
    void add(int index,Element e);
    void addFirst(Element e);
    void addLast(Element e);
    string toString();
    bool isEmpty();
    bool contains(Element e);
    Element get(int index);
    Element getFirst();
    Element getLast();
    int indexOf(Element e);
    int lastIndexOf(Element e);
    Element remove(int index);
    bool remove(Element e);
    Element removeFirst();
    Element removeLast();
    bool removeFirstOccurrence(Element e);
    bool removeLastOccurrence(Element e);
    void clear();

    //int size(){return getSize();}

};


Element * LinkedList::getAdress(int index){
    if (index<0 && index>=size) return NULL;
    Element * temp;
    temp=head;
    int i=0;
    while(i!=index) {
        temp=temp->getNext();
        i++;
    }
    return temp;
}


void LinkedList::add(Element e){
    if (isEmpty()){
        head->setValue(e.getValue());
    }
    else{
        Element *temp;
        temp=new Element;
        tail->setValue(e.getValue());
        temp->setPrev(tail);
        tail->setNext(temp);
        tail=temp;
    }
    size++;
}
void LinkedList::add(int index,Element e){
    Element *temp;
    temp=getAdress(index);
    if (temp==NULL) return;
    Element *temp2;
    temp2=new Element;
    temp2->setValue(e.getValue());
    temp2->setPrev(temp->getPrev());
    temp2->setNext(temp);
    temp->setPrev(temp2);
    if (temp==head) head=temp2;
    else temp2->getPrev()->setNext(temp2);
    size++;
}

void LinkedList::addFirst(Element e){
    if (isEmpty()){
        head->setValue(e.getValue());
    }
    else{
        Element *temp;
        temp=new Element;
        temp->setValue(e.getValue());
        temp->setNext(head);
        head->setPrev(temp);
        head=temp;
    }
    size++;

}

void LinkedList::addLast(Element e){
    add(e);
}

bool LinkedList::contains(Element e){
    int i=indexOf(e);
    return (i!=-1);
}

Element LinkedList::get(int index){
    Element e,*temp;
    temp=getAdress(index);
    e.setValue(temp->getValue());
    return e;
}

Element LinkedList::getFirst(){
    return get(0);
}
Element LinkedList::getLast(){
    return get(size-1);
}

int LinkedList::indexOf(Element e){
    if (size==0) return -1;
    Element *temp;
    temp=head;
    int i=0;
    while(temp->getValue()!=e.getValue() && i<size){
        temp=temp->getNext();
        i++;
    }
    if (i<size) return i;
    else return -1;
}

int LinkedList::lastIndexOf(Element e){
    if (size==0) return -1;
    Element *temp;
    temp=tail->getPrev();
    int i=size-1;
    while(temp->getValue()!=e.getValue() && i>0){
        temp=temp->getPrev();
        i--;
    }
    if (i>=0) return i;
    else return -1;
}
Element LinkedList::remove(int index){
    Element e;
    if (index<0 && index>=size) return e;
    Element *temp=(Element *)getAdress(index);
    e=get(index);
    if(temp==head){
        head=head->getNext();
    }
    else{
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrev(temp->getPrev());
    }
    delete temp;
    size--;
    return e;
}
bool LinkedList::remove(Element e){
    int index=indexOf(e);
    if (index==-1) return false;
    remove(index);
    return true;
}
Element LinkedList::removeFirst(){
    return remove(0);
}

Element LinkedList::removeLast(){
    return remove(size-1);
}
bool LinkedList::removeFirstOccurrence(Element e){
    remove(e);
}
bool LinkedList::removeLastOccurrence(Element e){
    Element *temp;
    temp=head;
    int i=0,index=-1;
    while(temp!=tail){
        if (temp->getValue()==e.getValue()){
            index=i;
        }
        temp=temp->getNext();
    }
    if (index==-1) return false;
    remove(index);
    return true;

}



bool LinkedList::isEmpty(){
    return (size==0);
}

string LinkedList::toString(){
    string str;
    int i=0;
    Element * temp;
    temp=head;
    if (isEmpty()){
        str="(list is empty)";
        return str;
    }
    while(i<size){
        char t[1000];
        sprintf(t,"%d",temp->getValue());
        str+=t;
        temp=temp->getNext();
        if (temp!=tail)str+=",";
        i++;
    }
    return str;
}

void LinkedList::clear(){
    Element * temp,*temp2;
    temp=head;
    while(temp!=tail){
        temp2=temp;
        temp=temp->getNext();
        delete temp2;
    }
    head=new Element;
    tail=new Element;
    head->setNext(tail);
    tail->setPrev(head);
    size = 0;


}



// a very simple main
int main() {
    Element e1;
    Element e2;
    Element e3;
    e1.setValue(10);
    e2.setValue(20);
    e3.setValue(30);
	LinkedList ll;
	ll.add(e1);
	ll.add(e2);
	cout<<ll.toString()<<endl;
	cout << ll.getSize() << endl;
	ll.addFirst(e3);
	cout<<ll.toString()<<endl;
	cout<<ll.contains(e3)<<endl;
	e3.setValue(50);
	ll.addLast(e3);
	cout<<ll.toString()<<endl;
	cout<<ll.get(1).getValue()<<endl;
	cout<<ll.getFirst().getValue()<<endl;
	cout<<ll.getLast().getValue()<<endl;
	cout<<ll.remove(1).getValue()<<endl;
	ll.clear();
	cout<<ll.toString()<<endl;
	Element e4;
	e4.setValue(20);
	e1.setValue(20);
	e2.setValue(30);
	e3.setValue(20);
	e4.setValue(30);
	ll.add(e1);
	ll.add(e2);
	ll.add(e3);
	ll.add(e4);
	cout<<ll.toString()<<endl;
	cout<<ll.indexOf(e1)<<endl;
	cout<<ll.lastIndexOf(e1)<<endl;
	cout<<ll.removeFirstOccurrence(e1)<<endl;
	cout<<ll.toString()<<endl;
	cout<<ll.removeLastOccurrence(e1)<<endl;
	cout<<ll.toString()<<endl;
	e1.setValue(100);
	ll.add(1,e1);
	cout<<ll.toString()<<endl;
	e1.setValue(500);
	ll.add(0,e1);
	cout<<ll.toString()<<endl;
	ll.removeFirst();
	cout<<ll.toString()<<endl;
	return 0;
}
