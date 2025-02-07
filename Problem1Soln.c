#include <stdio.h>
#define STACK_SIZE 50
#define QUEUE_SIZE 50

/* Stack implementation */
struct inventory_item
{
    int quantity;
    int price;
};
struct stack
{
    int top;
    struct inventory_item data[STACK_SIZE];
};
struct stack new_stack()
{
    struct stack s;
    s.top = -1;
    return s;
}
int stack_push(struct stack *stack, struct inventory_item data)
{
    if (stack->top == STACK_SIZE - 1)
    {
        return 0; // Indicate overflow
    }
    stack->top++;
    stack->data[stack->top] = data; // Add the element
    return 1;                       // Indicate success
}
int stack_pop(struct stack *stack, struct inventory_item *value)
{
    if (stack->top == -1)
    {
        return 0; // Indicate underflow
    }
    *value = stack->data[stack->top]; // Return the value we just popped
    stack->top--;                     // Decrement the top pointer e.g. remove the value
    return 1;
}
int tos(struct stack *stack, struct inventory_item **top)
{
    if (stack->top == -1)
    {
        return 0; // There cannot be a top of an empty stack
    }
    *top = &(stack->data[stack->top]); // Get a pointer to the current top of the stack
    return 1;
}
void print_stack(struct stack *stack)
{
    printf("Stack: \n");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("(Price: %d, Quantity: %d)\n", stack->data[i].price, stack->data[i].quantity);
    }
}

/* Queue implementation */
// Use an array queue
struct queue
{
    struct inventory_item data[QUEUE_SIZE];
    int front;
    int end;
    int count;
};
struct queue new_queue()
{
    struct queue q;
    q.front = -1;
    q.end = -1;
    q.count = 0;
    return q;
}
int queue_insert(struct queue *queue, struct inventory_item data)
{

    // Queue is full
    if (queue->count == QUEUE_SIZE)
    {
        return 0; // Cannot insert into a full queue
    }

    // Insert with wrap around
    queue->end = (queue->end + 1) % QUEUE_SIZE;
    queue->data[queue->end] = data;

    // Queue is empty
    if (queue->count == 0)
    {
        queue->front = queue->end;
    }
    queue->count++;
    return 1;
}
int queue_remove(struct queue *queue, struct inventory_item *data)
{
    // Queue is empty
    if (queue->count == 0)
    {
        return 0; // Cannot remove from an empty queue
    }

    // Save the data
    *data = queue->data[queue->front];

    // Remove with wrap around
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;

    // If the last item was just removed, need to reset
    if (queue->count == 0)
    {
        queue->front = -1;
        queue->end = -1;
    }
    return 1;
}
int front_of_queue(struct queue *queue, struct inventory_item **data)
{
    if (queue->count == 0)
    {
        return 0;
    }
    *data = &queue->data[queue->front];
    return 1;
}
void print_queue(struct queue *queue)
{
    if (queue->count == 0)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: \n");
    int c = queue->front;
    while (1)
    {
        if (c == queue->end)
        {
            printf("(Price: %d), (Quantity: %d)", queue->data[c].price, queue->data[c].quantity);
            break;
        }
        else
        {
            printf("(Price: %d), (Quantity: %d)->", queue->data[c].price, queue->data[c].quantity);
        }
        c = (c + 1) % QUEUE_SIZE;
    }
}

/* Problem specific code*/
#define NUM_OPERATIONS 6
enum operation_types
{
    BUY,
    SELL
};
struct entry
{
    enum operation_types operation;
    int quantity;
    int unit_price;
};

int main(void)
{
    // Array of operations
    struct entry operations[NUM_OPERATIONS] = {
        {BUY, 20, 1000},
        {BUY, 25, 900},
        {BUY, 10, 850},
        {SELL, 30, 1200},
        {BUY, 15, 1050},
        {SELL, 15, 1350}};

   
    // Compute the earnings under FIFO accounting
    int fifo_earnings = 0;
    struct stack s = new_stack();
    for (int i = 0; i < NUM_OPERATIONS; i++)
    {

        if (operations[i].operation == BUY)
        {
            struct inventory_item tmp;
            tmp.price = operations[i].unit_price;
            tmp.quantity = operations[i].quantity;
            stack_push(&s, tmp);
        }

        if (operations[i].operation == SELL)
        {

            // Number of items we need to sell
            int sell_num = operations[i].quantity;
            int revenue = operations[i].unit_price * sell_num;
            while (sell_num != 0)
            {
                // Pop off the last bought item if its quantity is less than
                // or equal to the sale quantity
                
                struct inventory_item *p_tos;
                tos(&s, &p_tos); // Get the top of the stack
                if (p_tos->quantity <= sell_num)
                {
                    struct inventory_item tmp;
                    stack_pop(&s, &tmp);
                    sell_num = sell_num - tmp.quantity;
                    revenue = revenue - tmp.price*tmp.quantity;
                }
                else
                {
                    // If we bought more than the sell amount, then need to
                    // sell off just the required ones
                    int to_sell = p_tos->quantity - sell_num;
                    p_tos->quantity = p_tos->quantity - to_sell;
                    revenue = revenue - to_sell*p_tos->price;
                    sell_num  = sell_num - to_sell;
                }
            }
            fifo_earnings += revenue;
            printf("Earnings: %d\n", fifo_earnings);
        }
        print_stack(&s);
        
    }
    printf("Earnings under FIFO accounting: %d\n", fifo_earnings);

    // Compute the earnings under FIFO accounting
    
}