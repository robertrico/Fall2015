#include "producer.h"

int main(int argc, char* argv[])
{
    pid_t pid;
    int bufSize; // Bounded buffer size
    int itemCnt; // Number of items to be produced
    int randSeed; // Seed for the random number generator 

    if(argc != 4){
		printf("Invalid number of command-line arguments\n");
		exit(1);
    }
	bufSize = atoi(argv[1]);
	itemCnt = atoi(argv[2]);
	randSeed = atoi(argv[3]);

    // Function that creates a shared memory segment and initializes its header
    InitShm(bufSize, itemCnt);        

	/* fork a child process */ 
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		exit(1);
	}
	else if (pid == 0) { /* child process */
		printf("Launching Consumer \n");
		execlp("./bin/consumer","consumer",NULL);
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		printf("Starting Producer\n");
		
		// The function that actually implements the production
        Producer(bufSize, itemCnt, randSeed);
		
		printf("Producer done and waiting for consumer\n");
		wait(NULL);		
		printf("Consumer Completed\n");
	}
    
    return 0;
}



void Producer(int bufSize, int itemCnt, int randSeed)
{
    int in = 0;
    int out = 0;
        
    srand(randSeed);

	WriteAtBufIndex(5,101);
    // Write code here to produce itemCnt integer values in the range [0-100]
    // Use the functions provided below to get/set the values of shared variables "in" and "out"
    // Use the provided function WriteAtBufIndex() to write into the bounded buffer 	
	// Use the provided function GetRand() to generate a random number in the specified range
    // **Extremely Important: Remember to set the value of any shared variable you change locally
	// Use the following print statement to report the production of an item:
	// printf("Producing Item %d with value %d at Index %d\n", i, val, in);
	// where i is the item number, val is the item value, in is its index in the bounded buffer
    
	printf("Producer Completed\n");
}

