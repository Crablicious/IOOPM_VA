/*
Student1: Adam Wendelin
Student2: Victoria Catalan
*/

int waterLevel = 100;
bool userWants, outputOpen, inputOpen;
bool sensorUpdate;

active proctype output(){

do
	:: atomic{(outputOpen && userWants && sensorUpdate) -> waterLevel--; sensorUpdate = false}; 

	:: else->skip;
od	 
}


active proctype input(){

do
	:: atomic{(inputOpen && sensorUpdate) -> waterLevel++; sensorUpdate = false};

	:: else->skip;
od
}

active proctype sensor(){
do
	:: atomic{waterLevel == 40-> outputOpen = false; inputOpen = true; sensorUpdate = true};

	:: atomic{waterLevel == 100 -> outputOpen = true; inputOpen = false; sensorUpdate = true};

	::atomic{else->sensorUpdate = true};
od
}

active proctype user(){
do
	::userWants = true;

	::userWants = false;
od
}

proctype monitor(){
do
	::assert(waterLevel<= 100 && waterLevel >= 40);
od
}

init{
run monitor();
}