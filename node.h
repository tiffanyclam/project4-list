#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    
public:
    Node(const T & = T());
    void setObject(const T &);
    T &getObject();
    void setNextPtr(Node<T> *);
    Node<T> *getNextPtr() const;
    void setPrevPtr(Node<T> *);
    Node<T> *getPrevPtr() const;
    
private:
    T object;
    Node<T> *nextPtr;
    Node<T> *prevPtr;
    
}; // Node<T> class

template <typename T>
Node<T>::Node(const T &object){
    this->object = object;
    this->nextPtr = 0;
    this->prevPtr = 0;
} // Node<T>::Node

template <typename T>
void Node<T>::setObject(const T &object){
    this->object = object;
} // Node<T>::setObject

template <typename T>
T &Node<T>::getObject(){
    return object;
} // Node<T>::getObject

template <typename T>
void Node<T>::setNextPtr(Node<T> *nextPtr){
    this->nextPtr = nextPtr;
} // Node<T>::setNextPtr

template <typename T>
Node<T> *Node<T>::getNextPtr() const{
    return nextPtr;
} // Node<T>::getNextPtr

template <typename T> 
void Node<T>::setPrevPtr(Node<T> *prevPtr){
    this->prevPtr = prevPtr;
} // Node<T>::setPrevPtr

template <typename T>
Node<T> *Node<T>::getPrevPtr() const{
    return prevPtr;
} //Node<T>::getPrevPtr

#endif // NODE_H
