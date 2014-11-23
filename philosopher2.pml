/* Dining Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5
bool pthink[n], peat[n] = false;
mtype{fork, none};
mtype cutlery [n];

proctype phil(int id) {
        do :: int right = id; int left = (id + 1) % n;

Think:   atomic { peat[id] = false; pthink[id] = true};
         printf("Philosopher %d is thinking\n", id);     

              if :: left<right;
                   atomic{cutlery[left] == fork -> cutlery[left] == none};
	           atomic{cutlery[right] == fork -> cutlery[right] == none}; 
                 :: right<left;
                   atomic{cutlery[right] == fork -> cutlery[right] == none};  
                   atomic{cutlery[left] == fork -> cutlery[left] == none};
              fi;

              
Eat:     assert (cutlery[left] == none && cutlery[right]==none);
         atomic { pthink[id] = false; peat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	cutlery[right] = fork; cutlery[left] = fork;
        od;
}

init{
  	int j = 0;
        
        do 
	:: j == n -> break
	:: else -> 	cutlery[j] = fork;
			j++
	od

	int i = 0;
	do 
	:: i >= n -> break
	:: else -> 	run phil(i);
			i++
	od
}
