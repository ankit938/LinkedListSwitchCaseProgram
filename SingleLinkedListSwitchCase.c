#include <stdio.h>
#include <stdlib.h>

typedef struct nodeType {
    int info;
    struct nodeType *next;
} node;

void createEmptyList(node **head) {
    *head = NULL;
}

void traverseInOrder(node *head) {
    while (head != NULL) {
        printf("%d ", head->info);
        head = head->next;
    }
    printf("\n");
}

void traverseInReverseOrder(node *head) {
    if (head == NULL)
        return;
    traverseInReverseOrder(head->next);
    printf("%d ", head->info);
}

node *searchInUnsortedList(node *head, int item) {
    while (head != NULL && head->info != item)
        head = head->next;
    return head;
}

node *searchInSortedList(node *head, int item) {
    while (head != NULL) {
        if (head->info == item)
            return head;
        else if (item < head->info)
            return NULL;
        else
            head = head->next;
    }
    return NULL;
}

void auxiliarySearch(node *head, node **ploc, node **loc, int item) {
    int flag = 0;
    if (head == NULL)
        *ploc = *loc = NULL;
    else if (head->info == item) {
        *ploc = NULL;
        *loc = head;
    } else {
        *ploc = head;
        *loc = head->next;
        while (*loc != NULL && !flag) {
            if ((*loc)->info == item)
                flag = 1;
            else {
                *ploc = *loc;
                *loc = (*loc)->next;
            }
        }
    }
}

void insertAtBeginning(node **head, int item) {
    node *ptr = (node *)malloc(sizeof(node));
    ptr->info = item;
    if (*head == NULL)
        ptr->next = NULL;
    else
        ptr->next = *head;
    *head = ptr;
}

void insertAtEnd(node **head, int item) {
    node *ptr, *loc;
    ptr = (node *)malloc(sizeof(node));
    ptr->info = item;
    ptr->next = NULL;
    if (*head == NULL)
        *head = ptr;
    else {
        loc = *head;
        while (loc->next != NULL)
            loc = loc->next;
        loc->next = ptr;
    }
}

void insertAfterElement(node *head, int after, int item) {
    node *ptr, *loc;
    loc = searchInUnsortedList(head, after);
    if (loc == NULL)
        return;
    ptr = (node *)malloc(sizeof(node));
    ptr->info = item;
    ptr->next = loc->next;
    loc->next = ptr;
}

void deleteFromBeginning(node **head) {
    if (*head == NULL)
        return;
    node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteFromEnd(node **head) {
    if (*head == NULL)
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    node *prev = NULL;
    node *curr = *head;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    free(curr);
}

void deleteAfterElement(node *head, int after) {
    node *prev, *temp;
    prev = searchInUnsortedList(head, after);
    if (prev == NULL || prev->next == NULL)
        return;
    temp = prev->next;
    prev->next = temp->next;
    free(temp);
}

void reverseList(node **head) {
    node *prev = NULL;
    node *curr = *head;
    node *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void deleteList(node *head) {
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    node *head;
    int choice, element, after;
    createEmptyList(&head);

    while (1) {
        printf("\n        Options Available\n");
        printf("+++++++++++++++++++++++++\n\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After a Given Element\n");
        printf("4. Traverse in Order\n");
        printf("5. Traverse in Reverse Order\n");
        printf("6. Delete from Beginning\n");
        printf("7. Delete from End\n");
        printf("8. Delete After an Element\n");
        printf("9. Reverse LinkedList\n");
        printf("10. Delete LinkedList\n");
        printf("11. Exit\n");
        printf("\n-----Enter your choice (1 to 11): ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &element);
                insertAtBeginning(&head, element);
                break;
            case 2:
                printf("Enter element: ");
                scanf("%d", &element);
                insertAtEnd(&head, element);
                break;
            case 3:
                printf("Enter element: ");
                scanf("%d", &element);
                printf("Enter element after which you want to insert: ");
                scanf("%d", &after);
                insertAfterElement(head, after, element);
                break;
            case 4:
                if (head == NULL)
                    printf("List is empty.\n");
                else
                    traverseInOrder(head);
                break;
            case 5:
                if (head == NULL)
                    printf("List is empty.\n");
                else
                    traverseInReverseOrder(head);
                break;
            case 6:
                deleteFromBeginning(&head);
                break;
            case 7:
                deleteFromEnd(&head);
                break;
            case 8:
                printf("Enter element after which you want to delete: ");
                scanf("%d", &after);
                deleteAfterElement(head, after);
                break;
            case 9:
                reverseList(&head);
                break;
            case 10:
                deleteList(head);
                createEmptyList(&head);
                break;
            case 11:
                exit(0);
        }
    }

    return 0;
}

