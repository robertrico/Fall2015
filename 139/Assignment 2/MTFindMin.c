#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <semaphore.h>
#include <stdbool.h>

#define MAX_SIZE 100000000
#define MAX_THREADS 16
#define RANDOM_SEED 62574
#define MAX_RANDOM_NUMBER 1000

// Global variables
long gRefTime; //For timing
int gData[MAX_SIZE]; //The array that will hold the data

int gThreadCount; //Number of threads
int gDoneThreadCount; //Number of threads that are done at a certain point. Whenever a thread is done, it increments this. Used with the semaphore-based solution
int gThreadMin[MAX_THREADS]; //The minimum value found by each thread
bool gThreadDone[MAX_THREADS]; //Is this thread done? Used when the parent is continually checking on child threads

// Semaphores
sem_t completed; //To notify parent that all threads have completed or one of them found a zero
sem_t mutex; //Binary semaphore to protect the shared variable gDoneThreadCount

int SqFindMin(int size); //Sequential FindMin (no threads)
void *ThFindMin(void *param); //Thread FindMin but without semaphores 
void *ThFindMinWithSemaphore(void *param); //Thread FindMin with semaphores 
int SearchThreadMin(); // Search all thread minima to find the minimum value found in all threads 
void GenerateInput(int size, int indexForZero); //Generate the input array 
void CalculateIndexes(int arraySize, int thrdCnt, int indexes[MAX_THREADS][3]); //Calculate the indexes to divide the array into T divisions, one division per thread
void resetAll();
int GetRand(int min, int max);//Get a random number between min and max

//Timing functions
long GetMilliSecondTime(struct timeb timeBuf);
long GetCurrentTime(void);
void SetTime(void);
long GetTime(void);

int main(int argc, char *argv[]){

	pthread_t tid[MAX_THREADS];  
	pthread_attr_t attr[MAX_THREADS];
	int indexes[MAX_THREADS][3];
	int i, indexForZero, arraySize, min;

	// Code for parsing and checking command-line arguments
	if(argc != 4){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}
	if((arraySize = atoi(argv[1])) <= 0 || arraySize > MAX_SIZE){
		fprintf(stderr, "Invalid Array Size\n");
		exit(-1);				
	}
	gThreadCount = atoi(argv[2]);				
	if(gThreadCount > MAX_THREADS || gThreadCount <=0){
		fprintf(stderr, "Invalid Thread Count\n");
		exit(-1);				
	}
	indexForZero = atoi(argv[3]);
	if(indexForZero < -1 || indexForZero >= arraySize){
		fprintf(stderr, "Invalid index for zero!\n");
		exit(-1);
	}

    GenerateInput(arraySize, indexForZero);

    CalculateIndexes(arraySize, gThreadCount, indexes); 

	// Code for the sequential part
	SetTime();
	min = SqFindMin(arraySize);
	printf("Sequential search completed in %ld ms. Min = %d\n", GetTime(), min);
	
	// Threaded with parent waiting for all child threads
	SetTime();

	// Write your code here
	// Initialize threads, create threads, and then let the parent wait for all threads using pthread_join
	// The thread start function is ThFindMin
	// Don't forget to properly initialize shared variables 
	for(i = 0; i < gThreadCount; i++){
		pthread_attr_init(&attr[i]);
		if(pthread_create(&tid[i], &attr[i], ThFindMin, &indexes[i])) {
			fprintf(stderr, "Error creating thread\n");
			return 1;

		}
	}

	for(i = 0; i < gThreadCount; i++){
		if(pthread_join(tid[i], NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 1;
		}
	}

    min = SearchThreadMin();
	printf("Threaded FindMin with parent waiting for all children completed in %ld ms. Min = %d\n", GetTime(), min);

	// Multi-threaded with busy waiting (parent continually checking on child threads)  
	SetTime();

	// Write your code here
	// Initialize threads, create threads, and then make the parent continually check on all child threads
	// The thread start function is ThFindMin
	// Don't forget to properly initialize shared variables 
	for(i = 0; i < gThreadCount; i++){
		pthread_attr_init(&attr[i]);
		if(pthread_create(&tid[i], &attr[i], ThFindMin, &indexes[i])) {
			fprintf(stderr, "Error creating thread\n");
			return 1;

		}
	}

	int j;
	for(j = 0; j < gThreadCount; j++){
		gThreadDone[j] = false;
	}
	while(1){
		bool thrdsComplete = true;
		for(j = 0; j < gThreadCount; j++){
			thrdsComplete = thrdsComplete && gThreadDone[j];
		}
		if(thrdsComplete){
			break;
		}
	}
	
	
    min = SearchThreadMin();
	printf("Threaded FindMin with parent continually checking on children completed in %ld ms. Min = %d\n", GetTime(), min);
	

	// Multi-threaded with semaphores  
	SetTime();

    // Write your code here
	// Initialize threads, create threads, and then make the parent wait on the "completed" semaphore 
	// The thread start function is ThFindMinWithSemaphore
	// Don't forget to properly initialize shared variables and semaphores using sem_init 
	sem_init(&completed,0,1);
	sem_init(&mutex,0,1);
	for(i = 0; i < gThreadCount; i++){
		pthread_attr_init(&attr[i]);
		if(pthread_create(&tid[i], &attr[i], ThFindMinWithSemaphore, &indexes[i])) {
			fprintf(stderr, "Error creating thread\n");
			//return 1;

		}
	}
	sem_wait(&completed);

	min = SearchThreadMin();
	printf("Threaded FindMin with parent waiting on a semaphore completed in %ld ms. Min = %d\n", GetTime(), min);
}

int SeqFind(int start, int end){
	int i, smallest=MAX_RANDOM_NUMBER+1;
	for(i=start; i <= end; i++){
		if(gData[i] < smallest){
			smallest = gData[i];
		}	
	}
	return smallest;
}
// Write a regular sequential function to search for the minimum value in the array gData
int SqFindMin(int size) {
	return SeqFind(0,size-1);
}

// Write a thread function that searches for the minimum value in one division of the array
// When it is done, this function should put the minimum in gThreadMin[threadNum] and set gThreadDone[threadNum] to true    
void* ThFindMin(void *param) {
	int threadNum = ((int*)param)[0];
	int startIndex = ((int*)param)[1];
	int endIndex = ((int*)param)[2];
	gThreadMin[threadNum] = SeqFind(startIndex,endIndex);
	gThreadDone[threadNum] = true;
	return NULL;
}

// Write a thread function that searches for the minimum value in one division of the array
// When it is done, this function should put the minimum in gThreadMin[threadNum]
// If the minimum value in this division is zero, this function should post the "completed" semaphore
// If the minimum value in this divison is not zero, this function should increment gDoneThreadCount and
// post the "completed" semaphore if it is the last thread to be done
// Don't forget to protect access to gDoneThreadCount with the "mutex" semaphore     
void* ThFindMinWithSemaphore(void *param) {
	int threadNum = ((int*)param)[0];
	int startIndex = ((int*)param)[1];
	int endIndex = ((int*)param)[2];
	gThreadMin[threadNum] = SeqFind(startIndex,endIndex);
	if(gThreadMin[threadNum] == 0){
		sem_post(&completed);
	}
	sem_wait(&mutex);
	gDoneThreadCount++;
	sem_post(&mutex);
	if(gDoneThreadCount == gThreadCount){
		sem_post(&completed);
	}
	return NULL;
}

int SearchThreadMin() {
    int i, min = MAX_RANDOM_NUMBER + 1;
	
    for(i =0; i<gThreadCount; i++) {
		if(gThreadMin[i] == 0)
				return 0;
		if(gThreadDone[i] == true && gThreadMin[i] < min)
			min = gThreadMin[i];
	}
	return min;
}

// Write a function that fills the gData array with random numbers between 1 and MAX_RANDOM_NUMBER
// If indexForZero is valid and non-negative, set the value at that index to zero 
void GenerateInput(int size, int indexForZero) {
	printf("Filling Array...\n");
	int i;
	SetTime();
	for(i=0; i < size; i++){
		if(indexForZero > 0 && indexForZero == i){
			gData[i] = 0;
		}else{
			gData[i] = GetRand(1,MAX_RANDOM_NUMBER);
		}	
	}
	printf("%d\r",i);
	printf("Array Fill took %lu ms \n",GetTime());
}

// Write a function that calculates the right indexes to divide the array into thrdCnt equal divisions
// For each division i, indexes[i][0] should be set to the division number i
// indexes[i][1] should be set to the start index, and indexes[i][2] should be set to the end index 
void CalculateIndexes(int arraySize, int thrdCnt, int indexes[MAX_THREADS][3]) {
	int i,start=0,indCount = (arraySize / thrdCnt);
	for(i=0; i < thrdCnt; i++){
		indexes[i][0] = i;
		indexes[i][1] = start;
		indexes[i][2] = start+indCount-1;
		start = indexes[i][2] + 1;
	}

}

// Get a random number in the range [x, y]
int GetRand(int x, int y) {
    int r = rand();
    r = x + r % (y-x+1);
    return r;
}

long GetMilliSecondTime(struct timeb timeBuf){
	long mliScndTime;
	mliScndTime = timeBuf.time;
	mliScndTime *= 1000;
	mliScndTime += timeBuf.millitm;
	return mliScndTime;
}

long GetCurrentTime(void){
	long crntTime=0;
	struct timeb timeBuf;
	ftime(&timeBuf);
	crntTime = GetMilliSecondTime(timeBuf);
	return crntTime;
}

void SetTime(void){
	gRefTime = GetCurrentTime();
}

long GetTime(void){
	long crntTime = GetCurrentTime();
	return (crntTime - gRefTime);
}
void resetAll(){
}

