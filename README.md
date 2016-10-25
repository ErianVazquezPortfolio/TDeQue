# TDeQue

This project is a dynamic template double ended queue in c++. 
This means it allow users to create the double ended queue data sctructure of any data type (i.e. String, int, or any custom object type) as long as there is a to string function for that object.
This double ended queue also grows dynamiclly with the number of items currently added to the queue. Its initial size is 8 but will increase or decrease depending on how many are added or removed.

Current opperations for the template double ended queue are :

* push_front - Inserts an element at the front of the queue. This will take a template object and output void. This will cause the array to grow when it is full to double its current size.
* push_back - Inserts an element at the back of the queue. This will take a template object and output void. This will cause the array to grow when it is full to double its current size.
* pop_front - Deletes the element at the front of the queue. This has no input but outputs an object template. This may cause the array to shrink to ½ its original size if it is ¼ and the capacity is greater than 8.
* pop_back - Deletes the element at the back of the queue. This has no input but outputs an object template. This may cause the array to shrink to ½ its original size if it is ¼ and the capacity is greater than 8.
* empty - checks to see if the queue is empty. This takes in no object and output a bool.
* size - returns the size of the queue. This takes in no object and outputs an int with the capacity.
* toStr – concatenates the contents of the queue from front to back into a return string with each string item followed by a newline character in the return string. This has no input but outputs previously stated string.

The tDeQue_main.cpp creates a template double ended queue and then uses op (operations) to allow the user to use the provided functions. 
