#define STONES 7
byte i;
#define FOR(i,l,h) i = l; do::i < h->
#define ROF(i,l,h) ;i++ :: i>= h -> break od

bool canjump;
bool taken;


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
mtype stones [STONES];



proctype jumpy(byte pos){
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
         od         
}

proctype jumpr(byte pos){
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
         od   
}

proctype monitor(){
        do
        ::assert(!success);
        od
}       

init{
        atomic{
        stones[0] = yellow;
        stones[1] = yellow;
        stones[2] = yellow;
        stones[3] = none;
        stones[4] = red;
        stones[5] = red;
        stones[6] = red;
               
        run jumpy(0);
        run jumpy(1);
        run jumpy(2);
        run jumpr(4);
        run jumpr(5);
        run jumpr(6);
        
        run monitor();
        }
}