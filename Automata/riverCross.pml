/*
Student1: Adam Wendelin
Student2: Victoria Catalan
*/

/* INVARIANT: Both right and left are structured like this: (farmer, wolf, sheep, cabbage) */

mtype{farmer, wolf,sheep, cabbage, none};
mtype right[4] = none;
mtype left[4];

#define success (\
(right[0]==farmer) && \
(right[1]==wolf) && \
(right[2]==sheep) && \
(right[3]==cabbage) && \
(left[0]==none) && \
(left[1]==none) && \
(left[2]==none) && \
(left[3]==none) \
)


proctype rightCross(){
do
	::(right[0] == farmer && right[1] == wolf && (right[2] != sheep || right[3] != cabbage)) -> 
		    right[0] = none; right[1] = none;
		    left[0] = farmer; left[1] = wolf; 

	::(right[0] == farmer && right[2] == sheep) -> 
		    right[0] = none; right[2] = none;
		    left[0] = farmer; left[2] = sheep; 

	::(right[0] == farmer && right[3] == cabbage && (right[1] != wolf || right[2] != sheep)) -> 
		    right[0] = none; right[3] = none;
		    left[0] = farmer; left[3] = cabbage; 

	::right[0] == farmer -> right[0] = none; left[0] = farmer;

	::else->skip; 
od
}

proctype leftCross(){
do
	::(left[0] == farmer && left[1] == wolf && (left[2] != sheep || left[3] != cabbage)) -> 
		    left[0] = none; left[1] = none;
		    right[0] = farmer; right[1] = wolf; 

	::(left[0] == farmer && left[2] == sheep) -> 
		    left[0] = none; left[2] = none;
		    right[0] = farmer; right[2] = sheep; 

	::(left[0] == farmer && left[3] == cabbage && (left[1] != wolf || left[2] != sheep)) -> 
		    left[0] = none; left[3] = none;
		    right[0] = farmer; right[3] = cabbage; 

	::left[0] == farmer -> left[0] = none; right[0] = farmer; 

	::else->skip;
od
}

proctype monitor(){
        do
        ::assert(!success);
        od
}       

init{
left[0] = farmer; 
left[1] = wolf;
left[2] = sheep;
left[3] = cabbage;
run leftCross();
run rightCross();
run monitor();
}
