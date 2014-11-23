/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool think[n], eat[n] = false;
mtype {fork, none};
mtype fork[n] = fork;

proctype phil(int id) {     
         int left=id; int right = (id +1) % n; 
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     

              if :: right < left;
                   atomic{fork[right] == fork -> fork[right] = none};
	           atomic{fork[left] == fork -> fork[left] = none}; 
                 :: left<right;
                   atomic{fork[left] == fork -> fork[left] = none};  
                   atomic{fork[right] == fork -> fork[right] = none};
              fi;
    
Eat:     assert (fork[right] == none && fork[left] == none);
         atomic { think[id] = false; eat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	fork[left] = fork; fork[right] = fork;
        goto Think;
}

init{
  	int i = 0;
        do 
	:: i>= n -> break 
	:: else ->  run phil(i);
                            i++
	od
}
