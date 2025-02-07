#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// define item struct
typedef struct item
{
    // value stored in the item
    int data;
    // pointer to the next item in the queue
    struct item *next;
} item;

// define queue struct
typedef struct queue
{
    // define the head of the queue
    item *head;
    // define the tail of the queue
    item *tail;
    // define the number of elements in the queue
    int count;
} Queue;

// function declarations
Queue *create_queue();
item *create_item(int data);
bool isQEmpty(Queue *queue);
bool enqueue(Queue *queue, item *item); // return true if successful
bool dequeue(Queue *queue, int *data);  // return true if successful
bool dequeue_all(Queue *queue);         // return true if successful

int main(void)
{

    return 0;
}

Queue *create_queue()
{
    // allocate space for the queue
    Queue *queue = malloc(sizeof(queue));

    // check if queue allocation failed
    if (queue == NULL)
    {
        printf("Failed to create Queue... \n");
        return NULL;
    }

    // initialize fields
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;

    // return the queue;
    return queue;
}

item *create_item(int data)
{
    // allocate space for item
    item *item = malloc(sizeof(item));

    // check if allocation failed
    if (item == NULL)
    {
        printf("Failed to create item... \n");
        return NULL;
    }

    // initialize fields of the item
    item->data = data;
    item->next = NULL;

    // return item
    return item;
}

bool isQEmpty(Queue *queue)
{
    return (queue->count == 0);
}

bool enqueue(Queue *queue, item *item)
{
    if (item != NULL && queue != NULL)
    {
        // check if queue is empty, head and tail point to new item
        if (isQEmpty(queue))
        {
            queue->head = item;
            queue->tail = item;
        }
        else
        {

            // set the last item's next pointer to point to the new item
            queue->tail->next = item;

            // update the tail pointer
            queue->tail = item;

            // increase the count of the queue
            queue->count++;
        }
    }
    else
    {
        // if this code executes, then either the item or the queue is NULL
        return false;
    }

    return true; // if code reaches here, enqueue was successful
}

bool dequeue(Queue *queue, int *data)
{
    // check if the queue is empty or NULL
    if (queue == NULL || isQEmpty(queue))
    {
        return false;
    }

    // store the value of the last item in "data" via pass by pointer
    *data = queue->head->data;

    // check if the queue only has one item, if yes head and tail should point to NULL
    if (queue->count == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
    {
        // have a reference to the old head
        item *old_head = queue->head;
        // re-route head
        queue->head = queue->head->next;
        // free old head
        free(old_head);
        old_head = NULL;
    }

    // decrement count of queue
    queue->count--;
    return true;
}

bool dequeue_all(Queue *queue)
{
    // check if queue is empty
    if (isQEmpty(queue))
        return false;
    // create a traverser pointer
    item *current_item = queue->head;
    // create a temporary variable
    item *temp;
    // traverse the queue
    while (current_item != NULL)
    {
        // create a "copy" of the current item
        temp = current_item;

        // traverse the current item
        current_item = current_item->next;

        // free the "copy"
        free(temp);
    }

    temp = NULL;
    free(queue); // free the entire queue
    queue = NULL;

    // no need to free "current_item" because it already points to NULL
    return true;
}

#hey i made a cool change