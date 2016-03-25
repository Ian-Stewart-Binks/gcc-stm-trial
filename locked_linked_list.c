#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct node {
    int val;
    struct node * next;
} node_t;

node_t * head = NULL;

void insert(int val) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->val = val;
	pthread_mutex_lock(&lock);
	if (head == NULL) {
		head = new_node;
	} else {
		node_t *curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = new_node;
	}
	pthread_mutex_unlock(&lock);
	printf("Node inserted\n");
}

void print() {
	pthread_mutex_lock(&lock);
	if (head == NULL) {
		printf("Empty!\n");
	} else {
		node_t *curr = head;
		while (curr != NULL) {
			printf("(%d)->", curr->val);
			curr = curr->next;
		}
	}
	pthread_mutex_unlock(&lock);
}

void delete(int val) {
	pthread_mutex_lock(&lock);
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
	pthread_mutex_lock(&lock);
}

int main() {
	insert(1);
	insert(2);
	print();
	return 0;
}
