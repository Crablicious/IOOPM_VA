/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool think[n], eat[n] = false;
int fork[n] = -1;

proctype phil(int id) {     
         int left=id; int right = (id +1) % n; 
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     

              if :: right < left;
                   atomic{fork[right] == -1 -> fork[right] = id};
	           atomic{fork[left] == -1 -> fork[left] = id}; 
                 :: left<right;
                   atomic{fork[left] == -1 -> fork[left] = id};  
                   atomic{fork[right] == -1 -> fork[right] = id};
              fi;
    
Eat:     assert (fork[right] == id && fork[left] == id);
         atomic { think[id] = false; eat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	fork[left] = -1; fork[right] = -1;
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
