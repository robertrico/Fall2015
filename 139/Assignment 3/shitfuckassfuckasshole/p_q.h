#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef INIT_PRIORITY
#define INIT_PRIORITY 200
#endif
#ifndef FIRST_NODE
#define FIRST_NODE (cur_node->next == NULL && cur_node->before == NULL) 
#endif
#ifndef LAST_NODE
#define LAST_NODE (cur_node->next == NULL && cur_node->before->priority <= new_node->priority)
#endif
#ifndef BETWEEN
#define BETWEEN (cur_node->priority < new_node->priority && cur_node->next->priority >= new_node->priority)
#endif


struct process{
	int num;
	int burst_len;
	int arrival_t;
	int time_remaining;
};

struct algorithm{
	int time_quantum;
	char* name;
	int pre_emt;
};

struct p_queue{
	int element_count;
	struct p_queue_node* front;
	void (*addToPQ)(struct p_queue* queue, struct p_queue_node* node);
	
};

void removeIt(struct p_queue_node* node);
void addToPQ(struct p_queue*, struct p_queue_node*);
void deepCopyNode(struct p_queue_node* dest, struct p_queue_node *src);
void deepCopyProcess(struct process* dest, struct process *src);
void pQueueNodeInit(struct p_queue_node* node);
void pQueueInit(struct p_queue* queue);
void insertBefore(struct p_queue_node *cur_node,struct p_queue_node *node);
void insertAfter(struct p_queue_node *cur_node,struct p_queue_node *node);
void insertBetween(struct p_queue_node *cur_node,struct p_queue_node *node);
int p_fifo(struct p_queue* queue,struct p_queue_node *cur_node,struct p_queue_node *node);
int p_sjf(struct p_queue* queue,struct p_queue_node *cur_node,struct p_queue_node *node);

int testQ();

struct p_queue_node{
	struct p_queue_node* next;
	struct p_queue_node* before;
	struct process* process;
	int priority;
};


