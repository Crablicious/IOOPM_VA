/* Dinning Philosophers Problem */
/*
Student 1:
Student 2:
*/

 

#define n 5

mtype{fork, none};
mtype cutlery [n];

proctype phil(int id) {
	do 
	:: 	printf("Philosopher %d is thinking\n", id);
		/* ... */
        
        if
            :: 	(id-1) == -1 -> (cutlery[n-1] == fork); cutlery[n-1] == none;
            :: 	else -> (cutlery[id-1] == fork); cutlery[id-1] == none;
        fi
          
          //Plockar sin högra gaffel
        
        (cutlery[id] == fork);
        cutlery[id] == none;
        
	   	printf("Philosopher %d is eating\n", id);
		cutlery[id] = fork; cutlery[id-1] = fork;
                /* ... Släpper gaffeln */ 
	od 
}

init{
  	int j = 0;
	do 
	:: j = n -> break
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
