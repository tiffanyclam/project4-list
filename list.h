#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdexcept>
#include <new>
#include "node.h"
#include "iterator.h"
#include "nosuchobject.h"

template <typename T>
class List;

template <typename T>
ostream &operator<<( ostream &, const List<T> & );

template <typename T>
class List {
    
    friend ostream &operator<< <>( ostream &, const List<T> & );
    
public:
    List();
    List( const List<T> & ) throw ( bad_alloc );
    ~List();
    void add( unsigned, const T & ) throw ( bad_alloc, out_of_range );
    void addAll( const List<T> & ) throw ( bad_alloc );
    void addAll( unsigned, const List<T> & ) throw ( bad_alloc, out_of_range );
    void addFirst( const T & ) throw ( bad_alloc );
    void addLast( const T & ) throw ( bad_alloc );
    void clear();
    bool contains( const T & ) const;
    bool empty() const;
    int indexOf( const T & ) const;
    T &get( unsigned ) const throw ( out_of_range );
    T &getFirst() const throw ( NoSuchObject );
    T &getLast() const throw ( NoSuchObject );
    ListIterator<T> listIterator();
    ListIterator<T> listIterator( unsigned ) throw ( out_of_range );
    T remove( unsigned ) throw ( out_of_range );
    T removeFirst() throw ( NoSuchObject );
    T removeFirstOccurrence( const T & ) throw ( NoSuchObject );
    T removeLast() throw ( NoSuchObject );
    T removeLastOccurrence( const T & ) throw ( NoSuchObject );
    T set( unsigned, const T & ) throw ( out_of_range );
    unsigned size() const;
    T *toArray() const throw ( bad_alloc );
    const List<T> &operator=( const List<T> & ) throw ( bad_alloc );
    void printInternal( ostream & = cout );
    
private:
    Node<T> *frontPtr, *backPtr;
    unsigned sz;
    
    void add( Node<T> *, const T & ) throw ( bad_alloc );
    void initialize();
    Node<T> *getIthNode( unsigned ) const throw ( out_of_range );
    T remove( Node<T> * );
    
}; // List class


template <typename T>
List<T>::List(){
    initialize();
}

template <typename T>
List<T>::List(const List<T> &list) throw (bad_alloc){
    initialize();
    *this = list;
}

template <typename T>
List<T>::~List(){
    clear();
}

template <typename T>
void List<T>::add(unsigned index, const T &object) throw (bad_alloc, out_of_range){
    Node <T> * ith = getIthNode(index);
    add(ith, object);
}

template <typename T>
void List<T>::add(Node<T> *current, const T &object) throw (bad_alloc){
    if (current == frontPtr)
        addFirst(object);
    else {
        Node<T> * temp = current->getPrevPtr();
        Node<T> * ptr = new Node<T>(object);
        temp->setNextPtr(ptr);
        ptr->setPrevPtr(temp);
        ptr->setNextPtr(current);
        current->setPrevPtr(ptr);
        sz++;
    }
}

template <typename T>
void List<T>::addAll(const List<T> &list) throw (bad_alloc){
    sz+=list.sz;
    Node<T> *qptr = list.frontPtr;
    while (qptr != 0){
        if (backPtr == 0)
            frontPtr = backPtr = new Node<T>(*qptr);
        else {
            backPtr->setNextPtr(new Node<T>(*qptr));
            backPtr->getNextPtr()->setPrevPtr(backPtr);
            backPtr = backPtr->getNextPtr();
        }
        qptr = qptr->getNextPtr();
    }
}

template <typename T>
void List<T>::addAll(unsigned index, const List<T> &list) throw (bad_alloc, out_of_range){
    Node<T> * ith = getIthNode(index);
    Node<T> *qptr = list.frontPtr;
    while (qptr != 0){
        if (backPtr == 0)
            frontPtr = backPtr = new Node<T>(*qptr);
        else {
            add(ith, qptr->getObject());
        }
        qptr = qptr->getNextPtr();
    }
}

template <typename T>
void List<T>::addFirst(const T &object) throw (bad_alloc){
    if (empty()){
        Node<T> *temp = new Node<T>(object);
        frontPtr = temp;
        backPtr = temp;
    }
    else {
        Node<T> *temp = new Node<T>(object);
        temp->setNextPtr(frontPtr);
        frontPtr->setPrevPtr(temp);
        frontPtr = temp;
        frontPtr->setPrevPtr(0);
    }
    sz++;
}

template <typename T>
void List<T>::addLast(const T &object) throw (bad_alloc){
    if (empty()){
        Node<T> *temp = new Node<T>(object);
        frontPtr = temp;
        backPtr = temp;
    }
    else {
        Node<T> *temp = new Node<T>(object);
        backPtr->setNextPtr(temp);
        temp->setPrevPtr(backPtr);
        backPtr = temp;
    }
    sz++;
}

template <typename T>
void List<T>::clear(){
    Node<T> *temp = frontPtr;
    while (temp != 0){
        temp = temp->getNextPtr();
        delete frontPtr;
        frontPtr = temp;
    }
    sz = 0;
    backPtr = 0;
}

template <typename T>
bool List<T>::contains(const T &object) const{
    Node<T> * temp = frontPtr;
    while (temp!= 0){
        if (temp->getObject() == object)
            return true;
        temp = temp->getNextPtr();
    }
    return false;
}

template <typename T>
bool List<T>::empty() const{
    return (sz == 0);
}

template <typename T>
T & List<T>::get(unsigned index) const throw (out_of_range){
    Node<T> * ptr = getIthNode(index);
    return ptr->getObject();
}

template <typename T>
T & List<T>::getFirst() const throw (NoSuchObject){
    if (empty())
        throw NoSuchObject
        ("List<T>::getFirst: empty list");
    return frontPtr->getObject();
}

template <typename T>
Node<T> *List<T>::getIthNode(unsigned index) const throw (out_of_range){
    if (index >= sz || index < 0)
        throw out_of_range
        ("List<T>::getIthNode: out of range");
    if (index <= double(sz)/2){
        Node<T> * temp = frontPtr;
        for (unsigned i = 0; i < index; i++)
            temp = temp->getNextPtr();
        return temp;
    }
    else {
        Node<T> * temp2 = backPtr;
        for (unsigned i = (sz-1); i > index; i--)
            temp2 = temp2->getPrevPtr();
        return temp2;
    }
    return 0;
}

template <typename T>
T & List<T>::getLast() const throw (NoSuchObject){
    if (empty())
        throw NoSuchObject
        ("List<T>::getLast: empty list");
    return backPtr->getObject();
}

template <typename T>
int List<T>::indexOf(const T &object) const{
    Node<T> * temp = frontPtr;
    for (unsigned i = 0; i < sz; i++){
        if (temp->getObject() == object)
            return i;
        temp = temp->getNextPtr();
    }
    return -1;
}

template <typename T>
void List<T>::initialize(){
    frontPtr = 0;
    backPtr = 0;
    sz = 0;
}

template <typename T>
ListIterator<T> List<T>::listIterator(){
    ListIterator<T> li;
    li.current = frontPtr;
    li.before = true;
    return li;
}

template <typename T>
ListIterator<T> List<T>::listIterator(unsigned index) throw (out_of_range){
    ListIterator<T> li;
    Node<T> * ith = getIthNode(index);
    li.current = ith;
    li.before = true;
    return li;
}

template <typename T>
const List<T> & List<T>::operator=(const List<T> &list) throw (bad_alloc){
    if (&list != this){
        if (!empty())
            clear();
        sz = list.sz;
        Node<T> *qptr = list.frontPtr;
        while (qptr != 0){
            if (backPtr == 0)
                frontPtr = backPtr = new Node<T>(*qptr);
            else {
                backPtr->setNextPtr(new Node<T>(*qptr));
                backPtr->getNextPtr()->setPrevPtr(backPtr);
                backPtr = backPtr->getNextPtr();
            }
            qptr = qptr->getNextPtr();
        }
    }
    return *this;
}

template <typename T>
void List<T>::printInternal(ostream &out){
    Node<T>* current = frontPtr;
    int i = 0;
    out << "front: " << frontPtr << endl;
    out << "back: " << backPtr << endl;
    while (current != 0) {
        out << "Node " << i << endl;
        out << "  address: " << current << endl;
        out << "  object: "
        << current->getObject() << endl;
        out << "  previous: "
        << current->getPrevPtr() << endl;
        out << "  next: "
        << current->getNextPtr() << endl;
        current = current->getNextPtr();
        i++;
    }
}

template <typename T>
T List<T>::remove(unsigned index) throw (out_of_range){
    Node<T> * ith = getIthNode(index);
    T returnObject = remove(ith);
    return returnObject;
}

template <typename T>
T List<T>::remove(Node<T> *current){
    T returnObject = T();
    if (current == frontPtr)
        returnObject = removeFirst();
    else if (current == backPtr)
        returnObject = removeLast();
    else {
        Node<T> * temp = current->getNextPtr();
        Node<T> * temp2 = current->getPrevPtr();
        returnObject = current->getObject();
        delete current;
        temp2->setNextPtr(temp);
        temp->setPrevPtr(temp2);
        sz--;
    }
    return returnObject;
}

template <typename T>
T List<T>::removeFirst() throw (NoSuchObject){
    if (empty())
        throw NoSuchObject
        ("List<T>::removeFirst: empty list");
    Node<T> *temp = frontPtr;
    frontPtr = frontPtr->getNextPtr();
    T object = temp->getObject();
    delete temp;
    if (frontPtr != 0)
        frontPtr->setPrevPtr(0);
    else
        backPtr = 0;
    sz--;
    return object;
}

template <typename T>
T List<T>::removeFirstOccurrence(const T & object) throw (NoSuchObject){
    T returnObject = T();
    Node<T> * temp = frontPtr;
    bool exists = false;
    while (temp != 0 && exists == false){
        if (temp->getObject() == object){
            returnObject = remove(temp);
            exists = true;
        }
        temp = temp->getNextPtr();
    }
    if (exists == false)
        throw NoSuchObject
        ("List<T>::removeFirstOccurrence: no such object");
    return returnObject;
}

template <typename T>
T List<T>::removeLast() throw (NoSuchObject){
    if (empty())
        throw NoSuchObject
        ("List<T>::removeLast: empty list");
    Node<T> *temp = backPtr;
    backPtr = backPtr->getPrevPtr();
    T object = temp->getObject();
    delete temp;
    if (backPtr != 0)
        backPtr->setNextPtr(0);
    else
        frontPtr = 0;
    sz--;
    return object;
}

template <typename T>
T List<T>::removeLastOccurrence(const T &object) throw (NoSuchObject){
    T returnObject = T();
    Node<T> * temp = backPtr;
    bool exists = false;
    while (temp != 0 && exists == false){
        if (temp->getObject() == object){
            returnObject = remove(temp);
            exists = true;
        }
        temp = temp->getPrevPtr();
    }
    if (exists == false)
        throw NoSuchObject
        ("List<T>::removeLastOccurrence: no such object");
    return returnObject;
}

template <typename T>
T List<T>::set(unsigned index, const T &object) throw (out_of_range){
    Node<T> * ith = getIthNode(index);
    T returnObject = ith->getObject();
    ith->setObject(object);
    return returnObject;
}

template <typename T>
unsigned List<T>::size() const{
    return sz;
}

template <typename T>
T *List<T>::toArray() const throw (bad_alloc){
    Node <T> * temp = frontPtr;
    T * x = new T[sz];
    for (unsigned i = 0; i < sz; i++){
        x[i] = temp->getObject();
        temp = temp->getNextPtr();
    }
    return x;
}

template <typename T>
ostream &operator<<(ostream &out, const List<T> &list){
    Node<T> * temp = list.frontPtr;
    if (list.size() == 0)
        out << "[]";
    else if (list.size() == 1)
        out << "[" << temp->getObject() << "]";
    else {
        out << "[" << temp->getObject();
        temp = temp->getNextPtr();
        for (unsigned i = 1; i < list.size(); i++){
            out << ", " << temp->getObject();
            temp = temp->getNextPtr();
        }
        out << "]";
    }
    return out;
}

#endif // LIST_H
