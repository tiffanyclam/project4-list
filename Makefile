CC = g++
CFLAGS = -Wall -g
#CFLAGS = -std=c++11 -Wall -g
SRCS = main.cpp
#SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}
INCLS = ${SRCS:.cpp=.h} list.h iterator.h node.h nosuchobject.h

a.out: $(OBJS)
    $(CC) $(CFLAGS) $(OBJS)

$(OBJS):
    $(CC) $(CFLAGS) -c $*.cpp

depend: Makefile.dep
    $(CC) -MM $(SRCS) > Makefile.dep

Makefile.dep:
    touch Makefile.dep

.PHONY: submit clean

submit:
    rm -f submit.zip
    zip submit.zip $(SRCS) $(INCLS) Makefile Makefile.dep HONOR

clean:
    rm -f *.o a.out core

include Makefile.dep



