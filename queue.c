#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ALLOC_SIZE 512

typedef int KEY_TYPE;

typedef struct _queue_node {
	struct _queue_node *next;
	KEY_TYPE key; // 这里是的KEY_TYPE是一个类型（可以为int，double之类的），先别管具体是什么类型
} queue_node;

typedef struct _queue {
	queue_node *front;  // 指向队列头
	queue_node *rear;   // 指向队列尾
	int queue_size;     // 队列长度
} queue;

void init_queue(queue *q) {
	q->front = q->rear = NULL;  // 初始化，将队列头和队列尾置空
	q->queue_size = 0;  //  长度为0
} 

void destroy_queue(queue *q) {
	queue_node *iter;  // 这个里先定义个迭代器
	queue_node *next;

	iter = q->front;  // 迭代器指向队列头

	while (iter) {
		next = iter->next;

		free(iter);
		iter = next;
	}
}

void push_queue(queue *q, KEY_TYPE key) {
	assert(q); // 检查

	if (q->rear) {  // 当队列里有元素时
		queue_node *node = (queue_node*)calloc(1, sizeof(queue_node)); // 分配空间
		assert(node);

		node->key = key;
		node->next = NULL;   // 这两句标准操作，不解释了

		q->rear->next = node;  // 因为插入的元素是在队列尾，将队列尾的元素的next指向当前插入的节点
		q->rear = node;  // 将当前插入的元素置为队列尾
	} else {  // 当队列里没有元素时
		queue_node *node = (queue_node*)calloc(1, sizeof(queue_node));
		assert(node);

		node->key = key;
		node->next = NULL;

		q->front = q->rear = node;  // 队列里没有元素，这时插入的元素即是队列头也是队列尾
	}
	q->queue_size++;
}

void pop_queue(queue *q, KEY_TYPE *key) {
	assert(q);
	assert(q->front != NULL);   // 检查

	if (q->front == q->rear) {  // 只有一个元素
		*key = q->front->key;

		free(q->front); // 释放空间，必须的
		q->front = q->rear = NULL;
	} else {
		queue_node *node = q->front->next;  // 先保存队列头的下一个元素，因为这个node接下来是要做队列头的

		*key = q->front->key;
		free(q->front);

		q->front = node;  // node成为了队列头
	}
	q->queue_size--;
}

int empty_queue(queue *q) {
	assert(q);

	return q->rear == NULL ? 0 : 1;
}

int size_queue(queue *q) {
	return q->queue_size;
}

int main() {
	queue q;
	init_queue(&q);

	int i = 0;
	for (i = 0; i < 1000; i++) {
		push_queue(&q, i+1);
	}

	while (empty_queue(&q)) {
		KEY_TYPE key;
		pop_queue(&q, &key);

		printf("%4d", key);
	}

	destroy_queue(&q);
}
