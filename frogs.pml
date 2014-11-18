#YOLO!
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
(stones[4]==yellow) && \
(stones[5]==yellow) && \
(stones[6]==yellow) \
)

mtype{none, yellow, red};
mtype stones [STONES];

stones[0] = yellow;
stones[1] = yellow;
stones[2] = yellow;
stones[3] = none;
stones[4] = red;
stones[5] = red;
stones[6] = red;


proctype istaken(byte index){
         if 
         ::index < 0 || index > 6 -> taken = false;
         ::stones[index] == yellow || stones [index] == red -> taken = true;
         ::else -> taken = false; 
         fi
}

proctype jumpy(byte pos){

         run istaken(pos+1);
         if
         ::taken == false -> stones[pos+1] = yellow; stones[pos] = none;
         fi

         run istaken(pos+2);
         if
         ::taken == false -> stones[pos+2] = yellow; stones[pos] = none;
         fi         
}

proctype jumpr(){
         atomic{
         FOR(i,1,7) 
         if
         :: (stones[i] == red && stones[i-1] == none) -> stones[i] = none; stones[i-1] = red
         :: (i != 1  && stones[i] == red && stones[i-2] == none) -> stones[i] = none; stones[i-2] = red
         fi       
         ROF(i,0,STONES)
         }
}

init(){
         
      FOR(i,0,4) jumpy(i) -> 
/* assert ska vara att succes = error */       

}
