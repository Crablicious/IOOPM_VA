/* Dining Philosophers Problem */
/*
Student 1:Adam Wendelin
Student 2:Victoria Catalán
*/
/*
Our assertion says that you have to "own" the fork to use it. Nobody should be able to grab the fork in your hand, while you're about to eat.

We originally had a deadlock when every philosopher grabbed the fork to the right. We solved it by making the philosopher grab the fork with the lowest index instead.

Spin shows no deadlocks anymore. 
*/

#define n 5
int cutlery[n] = -1;


proctype phil(int id) {     
         int left=id; int right = (id +1) % n; 

Think:   
         printf("Philosopher %d is thinking\n", id);     

         if :: right < left;
               atomic{cutlery[right] == -1 -> cutlery[right] = id};
                                     atomic{cutlery[left] == -1 -> cutlery[left] = id}; 
            :: left<right;
               atomic{cutlery[left] == -1 -> cutlery[left] = id}; 
               atomic{cutlery[right] == -1 -> cutlery[right] = id};
         fi;
    
Eat:     assert (cutlery[right] == id && cutlery[left] == id);
         printf("Philosopher %d is eating\n", id);

Stop:	cutlery[left] = -1; cutlery[right] = -1;
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
