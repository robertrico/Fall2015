#include "p_q.h"

/**/
void pQueueInit(struct p_queue* queue)
{
	queue->element_count = 0;
	queue->addToPQ = &addToPQ;
	queue->front = malloc(sizeof(struct p_queue_node));
	*queue->front = (struct p_queue_node) {NULL , NULL , NULL ,INIT_PRIORITY};
}

void pQueueNodeInit(struct p_queue_node* node)
{
	node->next = NULL;
	node->before = NULL;
	node->process = NULL;
	node->priority = INIT_PRIORITY;
}

void addToPQ(struct p_queue* queue, struct p_queue_node* node)
{
	struct p_queue_node *cur_node;
	struct p_queue_node *new_node = malloc(sizeof(struct p_queue_node));
	*new_node = (struct p_queue_node) { 0 , 0 , 0 , 0 };
	int fifo = 0;

	cur_node = queue->front;

	deepCopyNode(new_node,node);
	while(cur_node != NULL){
		if((fifo = p_fifo(queue,cur_node,new_node)) == 1){
			break;
		}else{
			cur_node = cur_node->next;
		}
	}

	while(queue->front->before != NULL){
		queue->front = queue->front->before;
	}
	
	queue->element_count++;
}

int p_fifo(struct p_queue* queue,struct p_queue_node *cur_node,struct p_queue_node *new_node)
{
	if(FIRST_NODE && cur_node->priority == INIT_PRIORITY){
		queue->front = new_node;
		return 1;	
	}else if(FIRST_NODE){
		if(cur_node->priority > new_node->priority){
			insertBefore(cur_node,new_node);
		}else{
			insertAfter(cur_node,new_node);
		}
		return 1;	
	}else if(LAST_NODE){
		insertAfter(cur_node,new_node);
		return 1;	
	}else if(BETWEEN){
		insertBetween(cur_node,new_node);
		return 1;	
	}else{
		return 0;
	}
}

int p_sjf(struct p_queue* queue,struct p_queue_node *cur_node,struct p_queue_node *new_node)
{
	if(FIRST_NODE && cur_node->priority == INIT_PRIORITY){
		queue->front = new_node;
		return 1;	
	}else if(FIRST_NODE){
		if(cur_node->priority > new_node->priority){
			insertBefore(cur_node,new_node);
		}else{
			insertAfter(cur_node,new_node);
		}
		return 1;	
	}else if(LAST_NODE){
		insertAfter(cur_node,new_node);
		return 1;	
	}else if(BETWEEN){
		insertBetween(cur_node,new_node);
		return 1;	
	}else{
		return 0;
	}
}

void insertBefore(struct p_queue_node *cur_node,struct p_queue_node *node)
{
	if(&cur_node->before != NULL){
		node->before = cur_node->before;
	}
	node->next = cur_node;
	cur_node->before = node;
}
void insertBetween(struct p_queue_node *cur_node,struct p_queue_node *node)
{
	cur_node->next->before = node;
	node->next = cur_node->next;
	node->before = cur_node;
	cur_node->next = node;
}
void insertAfter(struct p_queue_node *cur_node,struct p_queue_node *node)
{
	node->next = NULL;
	node->before = cur_node;
	cur_node->next = node;
}

void deepCopyNode(struct p_queue_node* dest, struct p_queue_node *src)
{
	if(src->next != NULL){
		dest->next = malloc(sizeof(struct p_queue_node));
		memcpy(dest->next,&src->next,sizeof(src->next));
	}
	if(src->before != NULL){
		dest->before = malloc(sizeof(struct p_queue_node));
		memcpy(dest->before,&src->before,sizeof(struct p_queue_node));
	}
	if(src->process != NULL){
		dest->process = malloc(sizeof(struct process));
		deepCopyProcess(dest->process,src->process);
	}
	if(&src->priority != NULL)
		dest->priority = src->priority;
}

void deepCopyProcess(struct process* dest, struct process* src)
{
	if(&src->num != NULL)
		dest->num = src->num;
	if(&src->burst_len != NULL)
		dest->burst_len = src->burst_len;
	if(&src->arrival_t != NULL)
		dest->arrival_t = src->arrival_t;
	if(&src->time_remaining != NULL)
		dest->time_remaining = src->time_remaining;
}

void removeIt(struct p_queue_node* node)
{
	if(node->next != NULL && node->next != NULL){
		node->before->next = node->next;
		node->next->before = node->before;
	}

	if(node->before == NULL){
		node->next->before = NULL;
	}

	if(node->next == NULL){
		node->before->next = NULL;
	}

	free(node);
}
/**/
int testQ()
{
	struct p_queue* priority_queue = malloc(sizeof(struct p_queue));
	struct p_queue_node* starter = malloc(sizeof(struct p_queue_node));
	struct process* process = malloc(sizeof(struct process));

	pQueueNodeInit(starter);
	pQueueInit(priority_queue);

	/* Fake Data, read in from input */
	process->burst_len = 4;
	process->arrival_t = 2;


	/* End Fake Data */

	starter->priority = 4;
	priority_queue->addToPQ(priority_queue,starter);
	printf("First : %d\n",priority_queue->front->priority);


	starter->priority = 3;
	priority_queue->addToPQ(priority_queue,starter);
	printf("Second : %d\n",priority_queue->front->priority);
	printf("Second.Next : %d\n",priority_queue->front->next->priority);


	starter->priority = 1;
	priority_queue->addToPQ(priority_queue,starter);
	printf("Third : %d\n",priority_queue->front->priority);
	printf("Third.Next : %d\n",priority_queue->front->next->priority);

	free(priority_queue);
	free(starter);
	free(process);
	return 1;
}
