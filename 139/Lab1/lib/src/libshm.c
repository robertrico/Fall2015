#include "libshm.h"

void InitShm(int bufSize, int itemCnt)
{
    int in = 0;
    int out = 0;
	const char *name = SHM_NAME; // Name of shared memory object to be passed to shm_open

     // Write code here to create a shared memory block and map it to gShmPtr
	 // Use the above name.
	 // **Extremely Important: map the shared memory block for both reading and writing 
	 // Use PROT_READ | PROT_WRITE

	int shm_fd;

	shm_fd = shm_open(name, O_CREAT | O_RDWR , 0666);


	ftruncate(shm_fd,SHM_SIZE);

	gShmPtr = mmap(0,SHM_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
	
	// Write code here to set the values of the four integers in the header
    // Just call the functions provided below, like this
    SetBufSize(bufSize); 	
	SetItemCnt(itemCnt);
	SetIn(in);
	SetOut(out);
       
	   
}

// Set the value of shared variable "bufSize"
void SetBufSize(int val)
{
        SetHeaderVal(0, val);
}

// Set the value of shared variable "itemCnt"
void SetItemCnt(int val)
{
        SetHeaderVal(1, val);
}

// Set the value of shared variable "in"
void SetIn(int val)
{
        SetHeaderVal(2, val);
}

// Set the value of shared variable "out"
void SetOut(int val)
{
        SetHeaderVal(3, val);
}

// Set the value of the ith value in the header
void SetHeaderVal(int i, int val)
{
        void* ptr = gShmPtr + i*sizeof(int);
        memcpy(ptr, &val, sizeof(int));
}

// Get the value of shared variable "bufSize"
int GetBufSize()
{       
        return GetHeaderVal(0);
}

// Get the value of shared variable "itemCnt"
int GetItemCnt()
{
        return GetHeaderVal(1);
}

// Get the value of shared variable "in"
int GetIn()
{
        return GetHeaderVal(2);
}

// Get the value of shared variable "out"
int GetOut()
{             
        return GetHeaderVal(3);
}

// Get the ith value in the header
int GetHeaderVal(int i)
{
        int val;
        void* ptr = gShmPtr + i*sizeof(int);
        memcpy(&val, ptr, sizeof(int));
        return val;
}

// Write the given val at the given index in the bounded buffer 
void WriteAtBufIndex(int indx, int val)
{
        // Skip the four-integer header and go to the given index 
        void* ptr = gShmPtr + 4*sizeof(int) + indx*sizeof(int);
	    memcpy(ptr, &val, sizeof(int));
}

// Read the val at the given index in the bounded buffer
int ReadAtBufIndex(int indx)
{
        int val;

        // Skip the four-integer header and go to the given index
        void* ptr = gShmPtr + 4*sizeof(int) + indx*sizeof(int);
        memcpy(&val, ptr, sizeof(int));
        return val;
}

// Get a random number in the range [x, y]
int GetRand(int x, int y)
{
	int r = rand();
	r = x + r % (y-x+1);
    return r;
}
