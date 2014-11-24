/*
Students:
Adam Wendelin
Victoria Catalan
*/

#define success (\
(stones[0]==red) && \
(stones[1]==red) && \
(stones[2]==red) && \
(stones[3]==none) && \
(stones[4]==yellow) && \
(stones[5]==yellow) && \
(stones[6]==yellow) \
)

mtype{none, yellow, red};
mtype stones [7];



proctype jumpY(byte pos){
         do
         :: atomic{
            (pos < 6) && (stones[pos+1] == none) -> 
            stones[pos+1] = yellow; 
            stones[pos] = none; 
            pos++;
            } 
         :: atomic{
            (pos < 5) && (stones[pos+2] == none) -> 
            stones[pos+2] = yellow; 
            stones[pos] = none; 
            pos = pos+2;
            }
          :: else -> skip;
         od         
}

proctype jumpR(byte pos){
         do
         :: atomic{
            (pos > 0) && (stones[pos-1] == none) -> 
            stones[pos-1] = red; 
            stones[pos] = none; 
            pos--;
            } 
         :: atomic{
            (pos > 1) && (stones[pos-2] == none) -> 
            stones[pos-2] = red; 
            stones[pos] = none; 
            pos = pos-2;
            }
         :: else -> skip; 
         od   
}

proctype monitor(){
        do
        ::assert(!success);
        od
}       

init{
        
        stones[0] = yellow;
        stones[1] = yellow;
        stones[2] = yellow;
        stones[3] = none;
        stones[4] = red;
        stones[5] = red;
        stones[6] = red;
               
        run jumpY(0);
        run jumpY(1);
        run jumpY(2);
        run jumpR(4);
        run jumpR(5);
        run jumpR(6);
        
        run monitor();
        
}