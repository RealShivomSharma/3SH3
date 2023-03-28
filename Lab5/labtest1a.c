/* group 70 
 Eddy Su 400263717
 Shivom Sharma 400332395
 */


#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void){
    
    pid_t pid1,pid2,pid3, pid4, pid5;  //creating pid variables for storage of forking operation parent child relationships

    printf("p1 = %d, parent = %d\n",getpid(), getppid()); //printing of pid for main parent process
    pid1 = fork();  //create p2
    

    if(pid1 == 0){  
        printf("p2 = %d, parent = %d\n",getpid(), getppid()); //printing of pid for p2
    } else{
        wait(NULL); //make p1 wait for its children
    }

    if (pid1 >0){
        pid2 = fork(); //create p3
    }

    if(pid2 == 0 && pid1 >0){
        printf("p3 = %d, parent = %d\n",getpid(), getppid()); //printing of pid for p3
    } else{
        wait(NULL); //make p2 wait for its children
    }

    if (pid2>0){
        pid3 = fork(); //create p4
    }

    if (pid3 == 0){
        printf("p4 = %d, parent = %d\n",getpid(), getppid());//printing of pid for p4
    } else {
        wait(NULL); //make p3 wait for its children
    }

    if (pid1 == 0 && pid4>0){
        pid4 = fork(); //create p5
    }

    if (pid4 == 0){
        printf("p5 = %d, parent = %d\n",getpid(), getppid()); //printing of pid for p5
        pid5 = fork(); //create p6
    } else {
        wait(NULL);//make p4 wait for its children
    }

    if (pid5 == 0){
        printf("p6 = %d, parent = %d\n",getpid(), getppid());//printing of pid for p6
    } else {
        wait(NULL);//make p5 wait for its children
    }

    

}
