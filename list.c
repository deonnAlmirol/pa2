#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 1000

/* A node in the linked list */
struct node {
    int data;
    struct node *next;
};

struct node *create_list(int intarray[], int len);

struct node *add_item_at_start(struct node *head, int data);

int search_array(int integers[], int numints, int element);

int search_list(struct node *head, int element);

struct node *create_sorted_list(struct node *head);

struct node *add_item_sorted(struct node *head, int data);

int copy_list_to_array(struct node *head, int *array);

void print_list(struct node *head);

void print_array(int integers[], int len);

int main(int argc, char *argv[])
{
    /* TODO: Complete the main method according to the steps outlined */
    if (argc > 2 || argc < 2) {
        printf("Usage: ./list <input_file>\n");
        return 1;
    }

    /* Open a file for reading */
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return 1;
    }

    /* Read the numbers from the file, into an array */
    int *num_array = malloc(MAX_INTS * sizeof(int));
    if (num_array == NULL) {
        printf("num_array mem error :(\n");
        return 1;
    }
    int current_num;
    int num_ints = 0;

    while (fscanf(file, "%d", &current_num) != EOF) {
        num_array[num_ints] = current_num;
        num_ints++;
    }

    /* Print the array */
    printf("Original Array:\n");
    print_array(num_array, num_ints);

    /* Create a linked list with the integers from the array */
    struct node *array_linked_list = create_list(num_array, num_ints);

    /* Print the linked list */
    printf("Original Linked List:\n");
    print_list(array_linked_list);

    /* Repeatedly prompt the user for a number to be searched.
     *  Search the array for the number and print out the result as shown in the
     * specs. Search the linked list for the number and print out the result as
     * shown in the specs. Stop prompting when the user enters 'q' (just the
     * character q without the single quotes).
     */
    char input[10];
    int run = 1;
    for (;;) {
        printf("Enter number: ");
        scanf("%s", input);

        if (strncmp(input, "q", 1) == 0) {
            break;
        }

        int array_position = search_array(num_array, num_ints, atoi(input));
        int list_position = search_list(array_linked_list, atoi(input));

        printf("Found %s in array at index %d\n", input, array_position);
        printf("Found %s in linked list at position %d\n", input,
               list_position);

        memset(input, 0, sizeof(input));
    }

    /* Create a sorted list(in ascending order) from the unsorted list */
    struct node *linked_list_sorted = create_sorted_list(array_linked_list);

    /* Print the sorted list */
    printf("Sorted Linked List:\n");
    print_list(linked_list_sorted);

    /* Copy the sorted list to an array with the same sorted order */
    int *sorted_array = (int *)malloc(num_ints * sizeof(int));
    if (sorted_array == NULL) {
        printf("sorted_array mem error :(\n");
        return 1;
    }
    copy_list_to_array(linked_list_sorted, sorted_array);

    /* Print out the sorted array */
    printf("Sorted Array: \n");
    print_array(sorted_array, num_ints);

    /* Print the original linked list again */
    printf("Original Linked List:\n");
    print_list(array_linked_list);

    /* Print the original array again */
    printf("Original Array:\n");
    print_array(num_array, num_ints);

    /* Open a file for writing */
    FILE *result_file = fopen("sorted_numbers.txt", "w");

    /* Write the sorted array to a file named "sorted_numbers.txt" */
    int f_index = 0;
    for (f_index = 0; f_index < num_ints; f_index++) {
        fprintf(result_file, "%d\n", sorted_array[f_index]);
    }

    /* Print out the number of integers written to the file */
    printf("Wrote %d numbers to sorted_numbers.txt\n", f_index);

    struct node *tmp = array_linked_list;
    while (array_linked_list != NULL) {
        array_linked_list = array_linked_list->next;
        free(tmp);
        tmp = array_linked_list;
    }

    free(sorted_array);

    struct node *sorted_tmp = linked_list_sorted;
    while (linked_list_sorted != NULL) {
        linked_list_sorted = linked_list_sorted->next;
        free(sorted_tmp);
        sorted_tmp = linked_list_sorted;
    }

    free(num_array);
}

struct node *create_list(int intarray[], int len)
{
    struct node *result = (struct node *)malloc(sizeof(struct node));
    if (result == NULL) {
        printf("mem error in creating node :(\n");
    }
    result->data = intarray[0];
    result->next = NULL;

    for (int i = 1; i < len; i++) {
        result = add_item_at_start(result, intarray[i]);
    }

    return result;
}

struct node *add_item_at_start(struct node *head, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("mem error in creating node :(\n");
    }

    new_node->data = data;
    new_node->next = head;

    return new_node;
}

int search_list(struct node *head, int element)
{
    int result = -1;
    int position = 1;
    while (head != NULL) {
        if (head->data == element) {
            result = position;
        }

        head = head->next;
        position++;
    }

    return result;
}

int search_array(int integers[], int numints, int element)
{
    int result = -1;
    for (int i = 0; i < numints; i++) {
        if (integers[i] == element) {
            result = i;
        }
    }

    return result;
}

int copy_list_to_array(struct node *head, int *array)
{
    int i = 0;
    for (i = 0; head != NULL; i++) {
        array[i] = head->data;
        head = head->next;
    }

    return i;
}

struct node *create_sorted_list(struct node *head)
{
    struct node *result = (struct node *)malloc(sizeof(struct node));
    if (result == NULL) {
        printf("mem error in creating node :(\n");
    }
    result->data = head->data;
    result->next = NULL;
    head = head->next;

    while (head != NULL) {
        result = add_item_sorted(result, head->data);
        head = head->next;
    }

    return result;
}

struct node *add_item_sorted(struct node *sorted_head, int data)
{
    int previous_int = -1;
    struct node *node_ptr = sorted_head;
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("mem error in creating node :(\n");
    }
    struct node *tmp = NULL;
    new_node->data = data;
    new_node->next = NULL;

    while (node_ptr->next != NULL) {
        if (data > node_ptr->data) {
            tmp = node_ptr;
            node_ptr = node_ptr->next;
            continue;
            // new_node->next = node_ptr->next;
            // node_ptr->next = new_node;
            // return sorted_head;
        }
        new_node->next = node_ptr;
        if (tmp != NULL) {
            tmp->next = new_node;
            node_ptr = tmp;
        } else {
            sorted_head = new_node;
        }
        return sorted_head;
    }
    if (data < node_ptr->data) {
        new_node->next = node_ptr;
        tmp->next = new_node;
        node_ptr = tmp;
        return sorted_head;
    }
    node_ptr->next = new_node;
    // node_ptr->next = new_node;

    return sorted_head;
}

void print_list(struct node *head)
{
    if (head == NULL) {
        printf("Linked List is Empty.\n");
    } else {
        struct node *temp = head;
        printf("head->");
        while (temp != NULL) {
            printf("|%d|->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void print_array(int integers[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("| %d ", integers[i]);
    }
    printf("|\n");
}