#ifndef NOSUCHOBJECT_H
#define NOSUCHOBJECT_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class NoSuchObject: public logic_error {
public:
    NoSuchObject():logic_error("No Such Object"){}
    NoSuchObject(const string &what):logic_error(what){}
}; // NoSuchObject class


#endif // NOSUCHOBJECT_H
