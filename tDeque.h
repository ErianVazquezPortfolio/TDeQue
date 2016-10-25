/* 
 * File:   Deque.h
 * Author: erian_000
 *
 * Created on February 21, 2015, 2:05 PM
 */

#ifndef TDEQUE_H
#define	TDEQUE_H

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Deque {
private:
    T *doubleEndedQueue; // the array of elements
    int doubleEndedQueueSize; //used to keep track of size
    int doubleEndedQueueQueued; // used to keep track of the number of elements in the array currently
    int doubleEndedQueueHead; // where is the first element
    int doubleEndedQueueTail; //where is the last element

    void shrink();
public:
    //Constructor
    Deque();
    //Destructor
    ~Deque();

    // Inserts the element at the front of the queue. 
    void push_front(T item);

    // Inserts the element at the back of the queue
    void push_back(T item);

    // Removes and returns the element at the front of the queue. 
    string pop_front();

    // Removes and returns the element at the back of the queue.
    string pop_back();

    // Returns the number of elements in the queue.
    int size();

    // Tells whether the queue is empty or not.
    bool empty();

    // Puts the contents of the queue from front to back into a return string with each string item followed by a newline
    string toStr();
};

#endif	/* TDEQUE_H */

template <class T>
//Constructor
Deque<T>::Deque() {
    doubleEndedQueue = new T[8];
    this->doubleEndedQueueSize = 8;
    this->doubleEndedQueueQueued = 0;
    this->doubleEndedQueueHead = 0;
    this->doubleEndedQueueTail = 0;
}

template <class T>
//Destructor
Deque<T>::~Deque() {

}

template <class T>
// Inserts the element at the front of the queue. 
void Deque<T>::push_front(T item) {
    try {
        if (doubleEndedQueueQueued == 0) { // if no elements start from index 1
            doubleEndedQueueHead = 0;
            doubleEndedQueueTail = 0;
            doubleEndedQueue[0] = item;
        } else if (doubleEndedQueueQueued == doubleEndedQueueSize) { // make the array larger if you need

            if (doubleEndedQueueHead == 0) {//simple case
                T *newArr = new T [doubleEndedQueueSize * 2]; // create a new array that will contain all the old info and new size

                for (int i = 0; i < doubleEndedQueueSize; i++) {
                    newArr[i] = doubleEndedQueue[i]; // add elements from old to new array
                }

                delete [] doubleEndedQueue; //remove old copy
                doubleEndedQueue = newArr; //create new copy

                doubleEndedQueueSize = doubleEndedQueueSize * 2; //set new size
                doubleEndedQueueHead = doubleEndedQueueSize - 1; //set new head location
                doubleEndedQueue [doubleEndedQueueHead] = item; //add newest element
            } else { // complex case when it is not in order
                //increase size and reorder and add to front and make head
                T *newArr = new T [doubleEndedQueueSize * 2]; // create a new array that will contain all the old info and new size
                for (int i = doubleEndedQueueHead; i <= doubleEndedQueueSize - 1; i++) {
                    newArr[i - doubleEndedQueueHead] = doubleEndedQueue[i]; // add elements from old to new array starting at 0
                }
                for (int i = 0; i <= doubleEndedQueueTail; i++) {
                    newArr[i + (doubleEndedQueueSize - doubleEndedQueueHead)] = doubleEndedQueue[i]; // starting from where we left off add more elements
                }

                delete [] doubleEndedQueue; //remove old copy
                doubleEndedQueue = newArr; //create new copy

                doubleEndedQueueTail = doubleEndedQueueSize - 1; //set new tail
                doubleEndedQueueSize = doubleEndedQueueSize * 2; //set new size
                doubleEndedQueueHead = doubleEndedQueueSize - 1; //set new head
                doubleEndedQueue [doubleEndedQueueHead] = item; //add newest element
            }
        } else { // add element when not full or empty
            if (doubleEndedQueueHead == 0) { //special case change head to end
                doubleEndedQueue[doubleEndedQueueSize - 1] = item;
                doubleEndedQueueHead = doubleEndedQueueSize - 1;
            } else { //normal case
                doubleEndedQueueHead--;
                doubleEndedQueue [doubleEndedQueueHead] = item;
            }
        }
        
        doubleEndedQueueQueued++;
    } catch (exception e) {
        throw runtime_error("Caught Exception for running out of memory");
    }
}

template <class T>
// Inserts the element at the back of the queue
void Deque<T>::push_back(T item) {
    try {

        if (doubleEndedQueueQueued == 0) { // case where nothing is in the array set it to object at 0
            doubleEndedQueueHead = 0;
            doubleEndedQueueTail = 0;
            doubleEndedQueue[0] = item;
        } else if (doubleEndedQueueQueued == doubleEndedQueueSize) {
            if (doubleEndedQueueTail == doubleEndedQueueSize - 1) { //simple case head is at 0 tail is at the end
                //increase size, add this to end and make head queue size
                T *newArr = new T [doubleEndedQueueSize * 2]; // create new array with double the size
                for (int i = 0; i < doubleEndedQueueSize; i++) {
                    newArr[i] = doubleEndedQueue[i]; //copy elements
                }

                delete [] doubleEndedQueue; //delete and create array
                doubleEndedQueue = newArr;

                doubleEndedQueueTail = doubleEndedQueueSize; //set correct values tail, size, and new value set
                doubleEndedQueue [doubleEndedQueueTail] = item;
                doubleEndedQueueSize = doubleEndedQueueSize * 2;
            } else { //complex case head is larger then tail
                //increase size and reorder and add to front and make head
                T *newArr = new T [doubleEndedQueueSize * 2]; //create new object
                for (int i = doubleEndedQueueHead; i <= doubleEndedQueueSize - 1; i++) { //add elements from head to  to end
                    newArr[i - doubleEndedQueueHead] = doubleEndedQueue[i]; //starting at 0
                }
                for (int i = 0; i <= doubleEndedQueueTail; i++) {
                    newArr[i + (doubleEndedQueueSize - doubleEndedQueueHead)] = doubleEndedQueue[i]; // add elements from where we left off
                }

                delete [] doubleEndedQueue; //delete and add array
                doubleEndedQueue = newArr;

                doubleEndedQueueHead = 0; //set correct head and tail and size values then set item in
                doubleEndedQueueTail = doubleEndedQueueSize;
                doubleEndedQueue [doubleEndedQueueTail] = item;
                doubleEndedQueueSize = doubleEndedQueueSize * 2;
            }
        } else { //adding and the array is not full or empty
            if (doubleEndedQueueTail == doubleEndedQueueSize - 1) { // special case where tail is at the end loop around
                doubleEndedQueue[0] = item;
                doubleEndedQueueTail = 0;
            } else { //simple case
                doubleEndedQueueTail++;
                doubleEndedQueue [doubleEndedQueueTail] = item;
            }
        }

        doubleEndedQueueQueued++;
    } catch (exception e) {
        throw runtime_error("Caught Exception for running out of memory");
    }
}

// Removes and returns the element at the front of the queue. 

template <class T>
string Deque<T>::pop_front() {

    if (doubleEndedQueueQueued == 0) {
        throw runtime_error("Caught Exception for popping with an empty array");
    }

    ostringstream stream;
    stream << doubleEndedQueue[doubleEndedQueueHead];
    string returnString = stream.str(); // set return string before deleting it
    //    doubleEndedQueue[doubleEndedQueueHead] = "";
    if (doubleEndedQueueHead != doubleEndedQueueSize - 1) { // simple case
        doubleEndedQueueHead++;
    } else {
        doubleEndedQueueHead = 0; // complex case set to 0 if it at the end
    }

    doubleEndedQueueQueued--;

    if ((doubleEndedQueueSize / 4) == doubleEndedQueueQueued && doubleEndedQueueSize > 8) {
        this->shrink();
    }

    return returnString;
}

// Removes and returns the element at the back of the queue.

template <class T>
string Deque<T>::pop_back() {

    if (doubleEndedQueueQueued == 0) {
        throw runtime_error("Caught Exception for popping with an empty array");
    }

    ostringstream stream;
    stream << doubleEndedQueue[doubleEndedQueueTail];
    string returnString = stream.str(); // set return string before deleting it
    //    doubleEndedQueue[doubleEndedQueueTail] = "";
    if (doubleEndedQueueTail != 0) { //simple case      
        doubleEndedQueueTail--;
    } else { //special case set tail to the end
        doubleEndedQueueTail = doubleEndedQueueSize - 1;
    }

    doubleEndedQueueQueued--; // allow lower count

    if ((doubleEndedQueueSize / 4) == doubleEndedQueueQueued && doubleEndedQueueSize > 8) { // only shrink if there is 1/4 left
        this->shrink();
    }

    return returnString;
}

template <class T>
void Deque<T>::shrink() {
    if (doubleEndedQueueHead < doubleEndedQueueTail) { //simple case
        T *newArr = new T [doubleEndedQueueSize / 2];
        for (int i = doubleEndedQueueHead; i <= doubleEndedQueueTail; i++) {
            newArr[i - doubleEndedQueueHead] = doubleEndedQueue[i];
        }

        delete [] doubleEndedQueue;
        doubleEndedQueue = newArr;

        doubleEndedQueueSize = doubleEndedQueueSize / 2;
        doubleEndedQueueHead = 0;
        doubleEndedQueueTail = (doubleEndedQueueSize / 2) - 1;
    } else { //complex case
        T *newArr = new T [doubleEndedQueueSize / 2];
        for (int i = doubleEndedQueueHead; i <= doubleEndedQueueSize; i++) { //move element from old array to new array set these to front
            newArr[i - doubleEndedQueueHead] = doubleEndedQueue[i];
        }
        for (int i = 0; i <= doubleEndedQueueTail; i++) { // add the rest of these to the end of the current list
            newArr[i + (doubleEndedQueueSize - doubleEndedQueueHead)] = doubleEndedQueue[i];
        }

        delete [] doubleEndedQueue;
        doubleEndedQueue = newArr;

        doubleEndedQueueSize = doubleEndedQueueSize / 2; //change all the values for head tail and size
        doubleEndedQueueHead = 0;
        doubleEndedQueueTail = (doubleEndedQueueSize / 2) - 1;
    }
}

// Returns the number of elements in the queue.

template <class T>
int Deque<T>::size() {
    return doubleEndedQueueSize;
}

// Tells whether the queue is empty or not.

template <class T>
bool Deque<T>::empty() {
    return doubleEndedQueueQueued == 0;
}

// Puts the contents of the queue from front to back into a return string with each string item followed by a newline

template <class T>
string Deque<T>::toStr() {

    string returnString = "";
    if (doubleEndedQueueQueued != 0) { // only print if there are elements
        if (doubleEndedQueueHead < doubleEndedQueueTail) { // simple case
            for (int i = doubleEndedQueueHead; i <= doubleEndedQueueTail; i++) { // run through add one by one to string then return string
                if (returnString == "") {
                    ostringstream stream;
                    stream << doubleEndedQueue[i] << "\n";
                    returnString.append(stream.str());
                } else {
                    ostringstream stream;
                    stream << doubleEndedQueue[i] << "\n";
                    returnString.append(stream.str());
                }
            }
           
            return returnString;
        } else if (doubleEndedQueueHead > doubleEndedQueueTail) { //complex case head is higher then tail 
            for (int i = doubleEndedQueueHead; i <= doubleEndedQueueSize - 1; i++) { //add head till end
                if (returnString == "") {
                    ostringstream stream;
                    stream << doubleEndedQueue[i] << "\n";
                    returnString = stream.str();
                } else {
                    ostringstream stream;
                    stream << doubleEndedQueue[i] << "\n";
                    returnString.append(stream.str());
                }
            }
            for (int i = 0; i <= doubleEndedQueueTail; i++) { //add 0 to tail
                ostringstream stream;
                stream << doubleEndedQueue[i] << "\n";
                returnString = returnString.append(stream.str());
            }
           
            return returnString;
        } else { // if they are equal then there is only one element print that one
            ostringstream stream;
            stream << doubleEndedQueue[doubleEndedQueueHead] << "\n";
            return stream.str();
        }
    }
    return "";
}