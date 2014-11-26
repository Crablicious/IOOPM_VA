/* Peterson's solution to the mutual exclusion problem - 1981 */
/*
Student 1: Adam Wendelin
Student 2: Victoria Catalan
*/

#define true	1
#define false	0
bool flag[2];
bool turn;
#define flag0 flag[0]
#define flag1 flag[1]

active [2] proctype user()
{	
	flag[_pid] = true;   /*  line 8 */
	turn = _pid;
	(flag[1-_pid] == false || turn == 1-_pid);
crit:	skip;	/* critical section - line 11 */
	flag[_pid] = false
}

never  {    /* [](flag0-><>!flag0)&&(flag1-><>!flag1) */
T0_init:
        do
        :: (! ((flag0)) && ! ((flag1))) -> goto accept_S172
        :: (! ((flag0))) -> goto T1_S173
        :: (! ((flag1))) -> goto T0_S172
        :: (1) -> goto T0_init
        od;
accept_S172:
        do
        :: (1) -> goto T0_S172
        od;
T1_S173:
        do
        :: (! ((flag1))) -> goto accept_S172
        :: (1) -> goto T1_S173
        od;
T0_S172:
        do
        :: (! ((flag0))) -> goto accept_S172
        :: (1) -> goto T0_S172
        od;
}
