#include "p_q.h"
#include <stdbool.h>

void execute(struct p_queue* queue, struct algorithm* algorithm);
int RR(struct p_queue* queue,int time_quantum);
int SJF(struct p_queue* queue,int time_quantum);
void recalculate_queue(struct p_queue* queue);
struct p_queue_node* checkForArrivals(struct p_queue* queue,int t,struct p_queue_node* cur_node);
