#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int value;
    struct ListNode *next;
};

void printList(struct ListNode* head){
    struct ListNode* temp = head;
    int count = 0;
    while(temp != NULL){
        printf("%d ", temp->value);
        temp = temp -> next;
        count++;
    }
    printf("\n%d elements in Linked List\n", count);
}

void search(struct ListNode* head, int x){
    struct ListNode* temp = head;
    printf("\n");
    while(temp != NULL){
        if(temp->value == x){
            printf("%d is in the Linked List", x);
            return;
        }
        temp = temp -> next;
    }
    printf("%d is not in the Linked List ", x);
}

void push(struct ListNode** head, int x){
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode -> value = x;

    newNode -> next = *head;
    *head = newNode;

    printf("%d pushed into the List\n", x);
}

void append(struct ListNode** head, int x){
    struct ListNode* temp = *head;

    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode -> value = x;
    newNode -> next = NULL;

    if(*head == NULL){
        *head = newNode;
        return;
    }  

    while(temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = newNode;

    printf("%d appended into the List\n", x);
}

void delete(struct ListNode* head, int x){
    struct ListNode* temp = head;
    struct ListNode* prev;

    if(temp == NULL)
        return;

    if(temp != NULL && temp -> value == x){
        head = temp -> next;
        free(temp);
        printf("%d deleted from the List\n", x);
        return;
    }

    while(temp != NULL && temp -> value != x){
        prev = temp;
        temp = temp -> next;
    }
    prev -> next = temp -> next;
    free(temp);
    printf("%d deleted from the List\n", x);
}

struct ListNode* merge(struct ListNode* a, struct ListNode* b){
    struct ListNode* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->value <= b->value) {
        result = a;
        result->next = merge(a->next, b);
    }
    else {
        result = b;
        result->next = merge(a, b->next);
    }
    return (result);
}
  
void partition(struct ListNode* head, struct ListNode** front, struct ListNode** end){
    struct ListNode* fast;
    struct ListNode* slow;
    slow = head;
    fast = head->next;
  
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
  
    *front = head;
    *end = slow->next;
    slow->next = NULL;
}

void sort(struct ListNode** head){
    struct ListNode* temp = *head;
    struct ListNode* a;
    struct ListNode* b;
  
    if ((temp == NULL) || (temp->next == NULL)) {
        return;
    }
  
    partition(*head, &a, &b);
  
    sort(&a);
    sort(&b);
  
    *head = merge(a, b);
}

int main(){
    struct ListNode* head = NULL;
    int x = 0;

    while(x != 7){
        int input;
        printf("\nChoose one of the following options: \n1-push 2-append 3-delete 4-search 5-sort 6-print 7-quit\n");
        scanf("%d", &x);

        if(x == 1){
            printf("Input a value: ");
            scanf("%d", &input);
            push(&head, input);
        }

        if(x == 2){
            printf("Input a value: ");
            scanf("%d", &input);
            append(&head, input);
        }

        if(x == 3){
            printf("Input a value: ");
            scanf("%d", &input);
            delete(head, input);
        }

        if(x == 4){
            printf("Input a value: ");
            scanf("%d", &input);
            search(head, input);
        }

        if(x == 5){
            sort(&head);
            printf("List has been sorted\n");
        }

        if(x == 6){
            printList(head);
        }
    }

    return 0;
}