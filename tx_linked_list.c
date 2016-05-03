#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

node_t * head = NULL;

static __attribute__((transaction_safe))
void insert(int val) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->val = val;
	__transaction_atomic {
		if (head == NULL) {
			head = new_node;
		} else {
			node_t *curr = head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = new_node;
		}

	}
}

static __attribute__((transaction_unsafe))
void print() {
	__transaction_relaxed {
		if (head == NULL) {
			printf("Empty!\n");
		} else {
			node_t *curr = head;
			while (curr != NULL) {
				printf("(%d)->", curr->val);
				curr = curr->next;
			}
		}
	}
}

static __attribute__((transaction_safe))
void delete(int val) {
	__transaction_atomic {
		if (head == NULL) {
			return;
		}
		if (head->val == val) {
			head = head->next;
		}
		node_t *curr = head;
		while (curr->next != NULL) {
			if (curr->next->val == val) {
				node_t *tmp = curr->next;
				curr->next = curr->next->next;
				free(tmp);
				break;
			}
			curr = curr->next;
		}
	}
}

int main() {
	insert(1);
	insert(2);
	print();
	return 0;
}
