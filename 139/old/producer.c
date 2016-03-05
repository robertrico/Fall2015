#include "shared.h"
#include "producer.h"

int main(int argc, char *argv[])
{

	pid_t pid;
	pid = fork();

	if(pid <0)
		ERR("Fork Failed");
	
	if(pid == 0){
		execlp("./consumer","consumer",NULL);
	}else{
		consumer();
		wait(NULL);
		printf("Child Processed\n");
	}	
	
	return 0;
}

int consumer()
{
	printf("I just produced.\n");
	return 0;
}
