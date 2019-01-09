#include "main.h"

int main(){
    try{
        // LIST 1
        List<int> l1;
        l1.addFirst(2);
        l1.addFirst(1);
        l1.addLast(3);
        l1.addLast(4);
        l1.addLast(3);
        cout << "Empty? " << l1.empty() << endl;
        cout << "First: " << l1.getFirst() << endl;
        cout << "Last: " << l1.getLast() << endl;
        cout << "Index of: " << l1.indexOf(2) << endl;
        cout << "Contains: " << l1.contains(4) << endl;
        cout << "Get: " << l1.get(1) << endl;
        cout << "Size? " << l1.size() << endl;
        l1.printInternal();
        l1.removeLastOccurrence(3);
        l1.removeLast();
        l1.printInternal();
        cout << "--------------------------------------" << endl;
        
        // LIST 2
        List<int> l2;
        l2.addFirst(350);
        l2.addFirst(150);
        l2.add(1, 250);
        l2.add(1, 200);
        l2.add(2, 300);
        l2.addLast(100);
        l2.addLast(350);

        l2.printInternal();
        l2.removeFirstOccurrence(350);
        l2.removeFirst();
        l2.remove(1);
        l2.set(1, 700);
        l2.printInternal();
        l2.addAll(l1);
        l2.printInternal();
        l2 = l1;
        l2.printInternal();
        l2.clear();
        l2.addLast(5);
        l2.addLast(6);
        l2.addLast(7);
        l2.printInternal();
        l2.addAll(2, l1);
        l2.printInternal();
        cout << "--------------------------------------" << endl;

        // MISC
        cout << l1 << endl;
        cout << l2 << endl;
        int *cArray = l2.toArray();
        for (unsigned i = 0; i < l2.size(); i++){
            cout << cArray[i] << endl;
        }
        delete [] cArray;
        cout << "--------------------------------------" << endl;

        // LIST ITERATOR 1
        ListIterator<int> li = l2.listIterator();
        cout << "Has next? " << li.hasNext() << endl;
        cout << "Has previous? " << li.hasPrevious() << endl;
        li.printInternal();
        cout << "Printing next " << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;
        cout << li.next() << endl;

        cout << "Printing previous " << endl;
        cout << li.previous() << endl;
        cout << li.previous() << endl;
        cout << "--------------------------------------" << endl;

        // LIST ITERATOR 2
        List<string>l4;
        l4.addFirst("abc");
        l4.addFirst("def");
        l4.add(1, "jkl");
        l4.add(2, "mnop");
        l4.addLast("qrs");
        l4.printInternal();
        
        ListIterator<string> lol = l4.listIterator(2);
        cout << "Printing next " << endl;
        cout << lol.next() << endl;
        cout << lol.next() << endl;
        cout << lol.next() << endl;

        cout << "Printing previous " << endl;
        cout << lol.previous() << endl;
        cout << lol.previous() << endl;
        cout << lol.previous() << endl;
        cout << lol.previous() << endl;
        
    }
    catch (out_of_range &e){
        cout << "Out of range: "
        << e.what() << endl;
    }
    catch (invalid_argument &e){
        cout << "Invalid argument: "
        << e.what() << endl;
    }
    catch (NoSuchObject &e){
        cout << "No such object: "
        << e.what() << endl;
    }
    catch (logic_error &e){
        cout << "Logic error: "
        << e.what() << endl;
    }
    catch (...){
        cout << "Uncaught exception" << endl;
    }
    
    return 0;
}



