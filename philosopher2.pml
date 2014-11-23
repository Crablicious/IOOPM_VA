/* Dining Philosophers Problem */
/*
Student 1:Adam Wendelin
Student 2:Victoria Catalán
*/

 

#define n 5
bool think[n], eat[n] = false;
mtype {fork, none};
mtype cutlery[n] = fork;

proctype phil(int id) {     
         int left=id; int right = (id +1) % n; 
Think:    atomic {eat[id] = false; think[id] = true};
          printf("Philosopher %d is thinking\n", id);     

              if :: right < left;
                   atomic{cutlery[right] == fork -> cutlery[right] = none};
	           atomic{cutlery[left] == fork -> cutlery[left] = none}; 
                 :: left<right;
                   atomic{cutlery[left] == fork -> cutlery[left] = none};  
                   atomic{cutlery[right] == fork -> cutlery[right] = none};
              fi;
    
Eat:     assert (cutlery[right] == none && cutlery[left] == none);
         atomic { think[id] = false; eat[id] = true};
         printf("Philosopher %d is eating\n", id);

Done:	cutlery[left] = fork; cutlery[right] = fork;
        goto Think;
}

proctype monitor(){
         do
         ::assert(think[n]==true || eat[n]==true);
        od
}      

init{
  	int i = 0;
        do 
	:: i>= n -> break 
	:: else ->  run phil(i);
                  run monitor();      
                            i++
	od
      
}
