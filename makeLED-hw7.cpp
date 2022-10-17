/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*  
*    This program uses USR LED 3 and can be executed in five ways:
*         ./makeLED-hw7 on
*         ./makeLED-hw7 off
*         ./makeLED-hw7 flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         ./makeLED-hw7 status (get the trigger status)
*
*     As for blink command
*     	  ./makeLED-hw7 blink 3
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   string blink = "blink";
  
   
   if(argc==1){
	cout << "Usage is makeLED and one of: " << endl;
	cout << "    on, off, flash, blink or status" << endl;
	cout << "e.g. makeLED-hw7 flash" << endl;
	cout << "As for blink command" << endl;
	cout << "need one more argument for number of blinks" << endl;
	cout << "e.g. makeLED-hw7 blink 3" << endl;
	return 2;
    }

   else if(argc!=2 && strcmp(argv[1],"blink") != 0){
	cout << argv[1] << endl;
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash, blink  or status" << endl;
	cout << " e.g. makeLED-hw7 flash" << endl;
	cout << "As for blink command" << endl;
	cout << "need one more argument for number of blinks" << endl;
	cout << "e.g. makeLED-hw7 blink 3" << endl;
        return 2;
   }

   else if(argc!=3 && strcmp(argv[1],"blink") == 0){
	cout << "Invalid number of arguments" << endl;
	cout << "Usage is blink" << endl;
	cout << "e.g. makeLED-hw7 blink 3" << endl;
	return 3;
    }

   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="blink"){
	cout << "BLinking the LED" << endl;
	removeTrigger();
	string cmd2(argv[2]);
	int count = stoi(cmd2);
	for (int i = count; i > 0; i--){
		writeLED("/brightness", "1");
		sleep(1);
		writeLED("/brightness", "0");
		sleep(1);
	}
	
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
