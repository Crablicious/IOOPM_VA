/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool think[n], eat[n] = false;
mtype{fork, none};
mtype fork[n];

proctype phil(int id) {     
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     

              if :: ((id + 1) % n) <id;
                   atomic{fork[(id +1) % n] == fork -> fork[(id + 1) % n] = none};
	           atomic{fork[id] == fork -> fork[id] = none}; 
                 :: id<((id + 1) % n%);
                   atomic{fork[id] == fork -> fork[id] = none};  
                   atomic{fork[(id + 1) % n] == fork -> fork[(id + 1) % n] = none};
              fi;
    
Eat:     assert (fork[(id + 1) % n] == none && fork[id] == none);
         atomic { think[id] = false; eat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	fork[id] = fork; fork[(id + 1) % n] = fork;
        goto Think;
}

init{
  	int i = 0;
	atomic{do 
	       :: (i!= n) -> 
	           {run phil(i); i++}
	       :: (i==n) -> break
	       od
}
