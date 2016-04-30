#include "sched.h"

/**/
int main(int argc, char* args[])
{
	//testQ();
	if(argc < 1){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}

	struct p_queue* priority_queue = malloc(sizeof(struct p_queue));
	*priority_queue = (struct p_queue) {0 , 0 , 0};
	pQueueInit(priority_queue);
	struct algorithm** alg = malloc(4*sizeof(struct algorithm*));
	int process_count = 0;

	FILE *fp;
	size_t len = 0;
	ssize_t read;
	char* line = NULL;
	fp = fopen(args[1],"r");

	if (fp == NULL)
		exit(EXIT_FAILURE);

	read = getline(&line,&len,fp);

	char* alg_info;
	alg_info = strtok(line," ");

	int i = 0;
	for(i=0;i<4;i++){
		alg[i] = malloc(sizeof(struct algorithm));
		*alg[i] =(struct algorithm) { 0 ,0 ,0};
		alg[i]->name = malloc(strlen(alg_info));
		strcpy(alg[i]->name,alg_info);

		int rr = strcmp(alg_info,"RR");
		if(rr == 0){
			alg_info = strtok (NULL, " ");
			alg[i]->time_quantum = atoi(alg_info);
		}
		alg_info = strtok (NULL, " ");
	}

	if((read = getline(&line,&len,fp)) != -1){
		process_count = atoi(line);
	}else{
		exit(-1);
	}
	char process_info[process_count+1][8];
	int process_added[process_count];

	int j;
	for(j=0; j < process_count; j++){
		if((read = getline(&line, &len, fp)) != -1){
			strncpy(process_info[j],line,strlen(line));
			process_info[j][8] = '\0';
			process_added[j] = 0;
		}
	}
	fclose(fp);

	j = 0;

	char *pch;
	int ready = 0;
    while (!ready) {
		struct process new_process = (struct process) {0,0,0,0};

		char tmp[sizeof(char)*8];
		strcpy(tmp,process_info[j]);

		pch = strtok(tmp," ");
		new_process.num = atoi(pch);
		pch = strtok (NULL, " ");
		new_process.arrival_t = atoi(pch);
		pch = strtok (NULL, " ");
		new_process.burst_len = atoi(pch);
		new_process.time_remaining = new_process.burst_len;
		pch = strtok (NULL, " ");

		struct p_queue_node node = (struct p_queue_node) {0,0,0,0};
		node.priority = atoi(pch);
		node.process = &new_process;
		priority_queue->addToPQ(priority_queue,&node);
		process_added[j] = 1;
		int k;
		for(k=0; k < process_count; k++){
			ready = 1 && process_added[k];
		}
		j = ((j+1) % process_count);
    }

	int o;
	for(o = 0; o < 4; o++){
		execute(priority_queue,alg[o]);
	}
	free(alg);
	free(priority_queue);

}

void execute(struct p_queue* queue, struct algorithm* algorithm)
{
	printf("Executing using %s algorithm\n",algorithm->name);

	int cmp = strcmp(algorithm->name,"RR");
	if(cmp == 0){
		printf("Time %d has passed\n",RR(queue,algorithm->time_quantum));
	}
	cmp = strcmp(algorithm->name,"SJF");
	if(cmp == 0){
		printf("Time %d has passed\n",SJF(queue,algorithm->time_quantum));
	}
}

int RR(struct p_queue* queue,int time_quantum)
{
	struct p_queue_node *p_node;
	p_node = queue->front;
	int time = 0;
	int done[queue->element_count];
	int i,j,k;
	for(i = 0; i < queue->element_count; i++){
		done[i] = 0;
	}
	

	j = 0;
	while(p_node != NULL){
		

		if(!done[j]){
			printf("Process %d arrived gets CPU\n",p_node->process->num);
			printf("Process Time Remaining %d\n",p_node->process->time_remaining = p_node->process->time_remaining - time_quantum);
			if(p_node->process->time_remaining <= 0){
				done[j] = 1;
			}


			k = 1;
			for(i = 0; i < queue->element_count; i++){
				k = k && done[i];
			}

			if(k){
				break;
			}else{
				p_node = p_node->next;
			}


			time++;
		}else{
			p_node = p_node->next;
		}

		j++;
		if(j == queue->element_count){
			p_node = queue->front;
			j = 0;
		}
	}


	return time;
}



struct p_queue_node* checkForArrivals(struct p_queue* queue,int t,struct p_queue_node* cur_node)
{
	struct p_queue_node *p_node;
	p_node = queue->front;

	while(p_node != NULL){
		if(p_node->next != NULL && p_node->next->process->arrival_t > t && p_node->next->process->time_remaining < p_node->process->time_remaining){
			p_node = p_node->next;
			break;
		}else{
			p_node = p_node->next;
		}
	}

	return p_node;
}

int SJF(struct p_queue* queue,int time_quantum)
{
	struct p_queue_node *p_node;
	p_node = queue->front;
	int time = 0;

	p_node = checkForArrivals(queue,time,p_node);
	time++;

	while(p_node == NULL){
		p_node = checkForArrivals(queue,time,p_node);
		time++;
	}

	while(p_node != NULL){
		if(p_node != NULL){
			printf("Time is %d\n",time);

			int cpu_time;
			for(cpu_time = 0; cpu_time < p_node->process->burst_len; cpu_time++){
				p_node->process->time_remaining--;
				time++;
			}
			printf("CPU had Process %d for %d\n",p_node->process->num,cpu_time);
			removeIt(p_node);
			printf("Time is %d\n",time);
		}
		p_node = checkForArrivals(queue,time,p_node);
	}


	return time;
}
