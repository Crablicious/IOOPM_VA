/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool think[n], eat[n] = false;
mtype {fork, none};
mtype fork[n];

proctype phil(int id) {     
         int left=id; int right = (id +1) % n; 
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     
Eat:       atomic { think[id] = false; eat[id] = true};
              if :: right < left;
                   atomic{fork[right] == fork -> fork[right] = none};
	           atomic{fork[left] == fork -> fork[left] = none}; 
                 :: left<right;
                   atomic{fork[left] == fork -> fork[left] = none};  
                   atomic{fork[right] == fork -> fork[right] = none};
              fi;
    
          assert (fork[(id + 1) % n] == none && fork[id] == none);
      
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
