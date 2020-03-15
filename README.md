## 队列定义
* 队列是一种特殊的线性表，特殊之处在于它只允许在表的前端（front）进行删除操作，而在表的后端（rear）进行插入操作，和栈一样，队列是一种操作受限制的线性表。进行插入操作的端称为队尾，进行删除操作的端称为队头。（转自百度百科）
PS：下面介绍的队列是用链表实现的


#### 1.首先先来一段代码。先看代码，再说为什么这样定义
##### ①定义队列节点
```
typedef struct _queue_node {
	struct _queue_node *next;
	KEY_TYPE key; // 这里是的KEY_TYPE是一个类型（可以为int，double之类的），先别管具体是什么类型
} queue_node;
```
上面是一个队列节点的定义，包含指向的下一个节点和当前节点的数据。
##### ②定义队列
```
typedef struct _queue {
	queue_node *front;  // 指向队列头
	queue_node *rear;   // 指向队列尾
	int queue_size;     // 队列长度
} queue;
```
* ***为什么这样定义？***
当队列为空的时候，**front = rear = NULL** ；
当队列只有一个元素的时候，**front = rear = node**
当队列有一个以上的元素时，**front指向队列的第一个元素，rear指向队列最后一个元素。**比如队列的第一个节点为node_1，最后一个节点为node_n，这时front = node_1, rear = node_n
* **后面看代码的时候，会发现这样定义相当方便**

#### 2.初始化
```
void init_queue(queue *q) {
	q->front = q->rear = NULL;  // 初始化，将队列头和队列尾置空
	q->queue_size = 0;  //  长度为0
} 
```

#### 3.插入元素到队列尾
```
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
```
#### 4.取出队列头元素
```
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
```

#### 5.销毁队列
```
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
```
---
2020.1.5  16:10  广州
