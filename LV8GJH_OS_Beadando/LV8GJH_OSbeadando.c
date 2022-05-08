#include <stdlib.h> 
#include <stdio.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h> 

int main() { 

pid_t pid;     						 //létrehozom a pid változót

int pipefd[2];   					 //csővezeték

if(pipe(pipefd) == -1)    				 //ellenőrzöm, hogy a csővezeték létrejött-e
{
   perror("pipe error");
   exit(-1);
}


char buf;                   				 //karakterváltozó, amely a beolvasást segíti majd
char szoveg[32];            				 //ebben tároljuk majd el a konkrét szöveget


pid = fork();               				 //létrehozom a gyermekprocesszt

if (pid != 0)  						 //szülőben vagyunk
{
 close(pipefd[0]);      				 //nem fogunk olvasni, így az olvasás fd-t lezárjuk

 strcpy(szoveg, "Milyen szép nyári napunk van.\0");      

 write(pipefd[1],szoveg, strlen(szoveg));                //megmondjuk, hogy hová, mit és mennyit írjon

 close(pipefd[1]);                                       //bezárjuk az írás fd-t is  

 exit(0);                                                //kilépünk a szülőprocesszből
}

else     						 //gyermekben vagyunk
{
 close(pipefd[1]);					 //bezárjuk az írás fd-t, mert itt nem fogunk írni
 
 int db = 0;                                             //létrehozunk egy számlálót

 while(read(pipefd[0], &buf, 1)>0)			 //beolvassuk a szülő által küldött szöveget arakterenként
{
       db++;                                             //növeljük a számlálót
       printf("%c", buf);                                //kiírjuk az üzenetet karakterenként
      
} 
 printf("\n Ennyi byte-ot olvastam: %d \n", db);	 //kiírjuk, hogy összesen mennyi byte került beolvasásra

 close(pipefd[0]);					 //bezárjuk az olvasás fd-t is, hiszen már erre sem lesz szükségünk

 exit(0); 						 //kilépünk a gyermekprocesszből
}


}
