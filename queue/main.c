/*
Auther:		Billy Gene Ridgeway
Purpose:	Learn about queues in C.
Date:		August 3rd. 2022.
*/

// NOTE: In the last example we looked at the basics of a doubly linked list
// here, I'll show you how you would normally use them as a 'queue'
// a queue is a 'first-in, first-out' (FIFO) structure
// NOTE: you can also easily insert and remove items at any point in the queue if you wish, 
// but it is more common to keep to FIFO operations.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This what is going to be in the queue.
typedef struct listitem {
	struct listitem *next;			// Pointer to the next item.
	struct listitem *prev;			// Pointer to the previous item.
	int data;						// Some integer data.
} LISTITEM;

// This is the queue 'header'.
typedef struct {
	struct listitem *first;			// Pointer to the first item.
	struct listitem *last;			// Pointer to last item.
} LISTHDR;

LISTHDR head;						// Declare this statically so that 'enqueue' (add an item to the end of the queue) and 
									//'dequeue' (remove an item from the beginning of the queue) can both use it.

									// This puts an item in at the end of the queue.
void enqueue(LISTITEM *item) {
	LISTITEM *temp;

	temp = head.last;				// Get the 'last' item in the queue and keep hold of it.
	head.last = item;				// Put the item in the queue at the end.
	item->prev = temp;				// Link back to old 'last' item.
	item->next = (LISTITEM*)&head;	// Set the forward link of the new item.
	temp->next = item;				// Finally set the forward link of the old 'last' item to the new one.
}

									// This removes an item from the front of the queue 
									// and returns the item or NULL if there are no more items.
LISTITEM *dequeue() {
	LISTITEM *temp;

	temp = head.first;					// Get the 'first' item.
	if (temp == (LISTITEM*)&head) {		// If the head of the queue points to itself ...
		temp = NULL;					// ... then the queue is empty.		
	} else {
		head.first = temp->next;		// Set the queue header to point to the 'second' item.
		head.first->prev = (LISTITEM*)&head;
	}
	return temp;
}

int main() {
	LISTITEM *temp;

	// First, make an empty queue.
	// Which is a queue where the header points to itself and there are no items in it.
	head.first = (LISTITEM*)&head;
	head.last = (LISTITEM*)&head;

	for (int i = 0; i < 3; i++) {			// Populate the queue.
		temp = malloc(sizeof(LISTITEM)); 	// Allocate some memory for the new queue item.
		temp->data = i;						// Set the item's data to the loop count so that we can see where it is in the queue.
		enqueue(temp);						// Put the item in the queue.
	}

	printf("First item = %d\n", head.first->data);
	printf("Last item = %d\n\n", head.last->data);

	// Now, let's dequeue from the end of the queue.
	do {							// Keep going until the queue is empty.
		temp = dequeue();			// If the queue is empty we will get NULL returned.
		if (temp != NULL) {
			printf("Data is %d\n", temp->data);
			free(temp);				// Call 'free' to clean up.
		}
	} while (temp != NULL);

	return 0;
}