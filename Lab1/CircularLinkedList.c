#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int value;
    struct ListNode *next;
};

void printList(struct ListNode* head){
    struct ListNode* temp = head;
    int count = 0;
    if(head == NULL)
        return;
        
    do{
        printf("%d ", temp -> value);
        temp = temp -> next;
        count++;
    }while(temp != head);
    printf("\n%d elements in Linked List\n", count);
}

void search(struct ListNode* head, int x){
    struct ListNode* temp = head;

    do{
        if(temp -> value == x){
            printf("%d is in the Linked List\n", x);
            return;
        }
        temp = temp -> next;
    }while(temp != head);

    printf("%d is not in the Linked List \n", x);
}

void push(struct ListNode** head, int x){
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    struct ListNode* temp = *head;
    newNode -> value = x;
    newNode -> next = *head;
   
    if(*head != NULL){
        while (temp -> next != *head){
            temp = temp -> next;
        }
        temp -> next = newNode;
    }
    else
        newNode -> next = newNode;
    
    *head = newNode;
    
    printf("%d pushed into the List\n", x);
}   

void append(struct ListNode** head, int x){
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    struct ListNode* temp = *head;
    newNode -> value = x;
    newNode -> next = *head;

    if(*head != NULL){
        while (temp -> next != *head){
            temp = temp -> next;
        }
        temp -> next = newNode;
    }
    else
        newNode -> next = newNode;

    printf("%d appended into the List\n", x);
}

void delete(struct ListNode* head, int x){
    struct ListNode* temp = head;
    struct ListNode* prev;

    if(temp == NULL)
        return;
    

    while(temp -> value != x){
        if(temp -> next == head){
            printf("%d is not in the List\n", x);
            return;
        }
        prev = temp;
        temp = temp -> next;
    }

    if (temp -> next == head){
        head = NULL;
        free(temp);
        return;
    }

    if(temp == head){
        prev = head;
        while(prev->next != head)
            prev = prev -> next;
        head = temp -> next;
        prev -> next = head;
        free(temp);
    }
    else if(temp -> next == head && temp == head){
        prev -> next = head;
        free(temp);
    }
    else{
        prev -> next = temp -> next;
        free(temp);
    }

    printf("%d deleted from the List\n", x);

}

int main() {
    struct ListNode* head = NULL;

    int x = 0;

    while(x != 6){
        int input;
        printf("\nChoose one of the following options: \n1-push 2-append 3-delete 4-search 5-print 6-quit\n");
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
            printList(head);
        }
    }
    
    return 0;
}