/* Peterson's solution to the mutual exclusion problem - 1981 */
/*
Student 1:
Student 2:
*/

#define true	1
#define false	0
bool flag[2];
bool turn;
byte counter;

active [2] proctype user()
{	
	flag[_pid] = true;   /*  line 8 */
	turn = _pid;
	(flag[1-_pid] == false || turn == 1-_pid);
        counter++
        crit: assert(counter == 1);	/* critical section - line 11 */
        counter--
	flag[_pid] = false
}

/*proctype Monitor(){*/
        /*atomic{ */
                /*assert(!((flag[1] == false || turn == 1) && (flag[0] == false || turn == 0))) */
      /*  }*/
/*}*/

/*init{*/
       /* run Monitor();*/
/*}*/