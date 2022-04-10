#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int status;

	//Létezõ:
	status=system("ls");

	if(status < 0)
		perror("system() error");

	else if(WIFEXITED(status))
		printf("Normalis befejezodes, visszaadott ertek: %d\n", WEXITSTATUS(status));

	else
		printf("Nem normalis befejezodes\n");

	//Nem létezõ
	status=system("valami");

	if(status < 0)
		perror("system() error");

	else if(WIFEXITED(status))
		printf("Normalis befejezodes, visszaadott ertek: %d\n ", WEXITSTATUS(status));

	else
		printf("Nem normalis befejezodes\n");

	exit(0);

}
