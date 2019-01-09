#ifndef ITERATOR_H
#define ITERATOR_H
#include "nosuchobject.h"

template <typename> class List;

template <typename T>
class ListIterator
{
    friend class List<T>;
    
public:
    ListIterator();
    bool hasNext() const;
    bool hasPrevious() const;
    T &next() throw ( NoSuchObject );
    T &previous() throw ( NoSuchObject );
    void printInternal() const;
    
private:
    Node<T> *current;
    bool before;
    
};

template <typename T>
ListIterator<T>::ListIterator(){
    current = 0;
    before = true;
}

template <typename T>
bool ListIterator<T>::hasNext() const{
    if (current->getNextPtr() == 0 && before == false)
        return false;
    return true;
}

template <typename T>
bool ListIterator<T>::hasPrevious() const{
    if (current->getPrevPtr() == 0 && before == true)
        return false;
    return true;
}

template <typename T>
T & ListIterator<T>::next() throw (NoSuchObject){
    if (!hasNext())
        throw NoSuchObject
        ("ListIterator<T>::next: no next object");
    if (before == true)
        before = false;
    else if (before == false)
        current = current->getNextPtr();
    return current->getObject();
}

template <typename T>
T & ListIterator<T>::previous() throw (NoSuchObject){
    if (!hasPrevious())
        throw NoSuchObject
        ("ListIterator<T>::previous: no previous object");
    if (before == false)
        before = true;
    else if (before == true)
        current = current->getPrevPtr();
    return current->getObject();
}

template <typename T>
void ListIterator<T>::printInternal() const{
    if (current != 0){
        cout << "  address: " << current << endl;
        cout << "  object: "
        << current->getObject() << endl;
        cout << "  previous: "
        << current->getPrevPtr() << endl;
        cout << "  next: "
        << current->getNextPtr() << endl;
    }
}

#endif // ITERATOR_H
