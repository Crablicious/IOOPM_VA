/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool think[n], eat[n] = false;
int fork[n] = -1;

proctype phil(int id) {
       int right = id; int left = (id + 1) % n;
     
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     

              if :: (id + 1) <id;
                   atomic{fork[id +1 ] == -1 -> fork[id + 1] == id};
	           atomic{fork[id] == -1 -> fork[id] == id}; 
                 :: id<id + 1;
                   atomic{fork[id] == -1 -> fork[id] == id};  
                   atomic{fork[id + 1] == -1 -> fork[id + 1] == id};
              fi;
    
Eat:     assert (fork[id + 1] == id && fork[id]==id);
         atomic { think[id] = false; eat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	fork[id] = -1; fork[id + 1] = -1;
        goto Think;
}

init{
  	int i = 0;
	do 
	:: (i!= n) -> 
	   {run phil(i); j++}
	:: (i==n) -> break
	od
}
