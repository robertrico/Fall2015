/* Robert Rico */

#include "consumer.h"

int main()
{
	const char *name = SHM_NAME; // Name of shared memory object to be passed to shm_open
	int bufSize; // Bounded buffer size
	int itemCnt; // Number of items to be consumed

	int shm_fd; // Shared Memory File Descriptor

	// Write code here to create a shared memory block and map it to gShmPtr
	// Use the above name
	// **Extremely Important: map the shared memory block for both reading and writing 
	// Use PROT_READ | PROT_WRITE
	shm_fd = shm_open(name, O_RDWR , 0666);
	gShmPtr = mmap(0,SHM_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);

	// Write code here to read the four integers from the header of the shared memory block 
	// These are: bufSize, itemCnt, in, out
	// Just call the functions provided below like this:
	bufSize = GetBufSize();
	itemCnt = GetItemCnt();

	// Write code here to check that the consumer has read the right values: 
	printf("Consumer reading: bufSize = %d\n",bufSize);
	printf("Consumer reading: itemCnt = %d\n",itemCnt);
	printf("Consumer reading: in = %d\n",GetIn());
	printf("Consumer reading: out = %d\n",GetOut());

	// Write code here to consume all the items produced by the producer
	// Use the functions provided below to get/set the values of shared variables in, out, bufSize
	// Use the provided function ReadAtBufIndex() to read from the bounded buffer 	
	// **Extremely Important: Remember to set the value of any shared variable you change locally
	// Use the following print statement to report the consumption of an item:
	// printf("Consuming Item %d with value %d at Index %d\n", i, val, out);
	// where i is the item number, val is the item value, out is its index in the bounded buffer
	int i;
	for(i=0;i < GetItemCnt(); i++){
		while(GetIn() == GetOut())
			;
		printf("Consuming Item %d with value %d at Index %d\n", i+1, ReadAtBufIndex(GetOut()), GetOut());
		SetOut((GetOut()+1) % GetBufSize());
	}


	// remove the shared memory segment 
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
