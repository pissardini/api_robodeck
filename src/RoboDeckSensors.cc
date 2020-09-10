/*

 Copyright (c) 2014 R.S. Pissardini <rodrigo AT pissardini DOT com>  

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <string>
#include "RoboDeck.hh"
#include "RoboDeckSensors.hh"

using namespace std; 

using std::string;


double *RoboDeckSensors::readInfraredSensorLowLevel(int position, RoboDeck &robot){

	unsigned char buf[256];
	unsigned int size; 
	double *distanceNotLinear;
	distanceNotLinear = (double*) malloc (2 * sizeof(double));

	buf[0] = 0x02;
	buf[1] = 0x08;
	buf[2] = (unsigned char)position;

	if (!robot.send(buf,3)) cout <<"Could not send readInfraredSensorLowLevel command "<< endl;

	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting readInfraredSensorLowLevel command."<< endl;
	}

	ushort measurementH = buf[2];
	ushort measurementL = buf[3];
	distanceNotLinear[0] = (double)measurementH;
	distanceNotLinear[1] = (double)measurementL;

	return distanceNotLinear; //return measurementH and measurementL 
} 

double *RoboDeckSensors::readInfraredSensorHighLevel(int position,RoboDeck &robot) {

	unsigned char buf[256];
	int size; 
	double *distance;

	distance = (double*) malloc (2 * sizeof(double));
	buf[0] = 0x03;
	buf[1] = 0x05;

	switch(position){ 
		case 0: 
			buf[2] = 0x00; 
		break;
		case 1: 
			buf[2] = 0x01; 
		break;
		case 2: 
			buf[2] = 0x02; 
		break;
		case 3: 
			buf[2] = 0x03; 
		break;
	}

	if (!robot.send(buf,3)) cout <<"Could not send readInfraredSensorHighLevel command. "<< endl;
    
	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting getRobotProtocolVersion readInfraredSensorHighLevel command."<< endl;
	}

	ushort distH = buf[2];
	ushort distL = buf[3];
	distance[0] = (double)distH;
	distance[1] = (double)distL;
	return distance; //return distanceH and distanceL

} 

double *RoboDeckSensors::readUltrasonicSensor(int position, RoboDeck &robot){

	unsigned char buf[256];
	int size; 
	double *distance;
	distance = (double*) malloc (2 * sizeof(double));

	buf[0] = 0x03;
	buf[1] = 0x06;
	buf[2] = (unsigned char) position;

	if (!robot.send(buf,3)) cout <<"Could not send readUltrasonicSensor command "<< endl;

    
	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting readUltrasonicSensor command."<< endl;
  }
  
  ushort distH = buf[2];
	ushort distL = buf[3];

	distance[0] = (double)distH;
	distance[1] = (double)distL;

	return distance; //return distanceH and distanceL
}

double *RoboDeckSensors::readUltrasonicLumi(int position, RoboDeck &robot){

	unsigned char buf[256];
	int size; 
	double *lumi;
	lumi = (double*) malloc (1 * sizeof(double));

	buf[0] = 0x03;
	buf[1] = 0x07;
	buf[2] = (unsigned char) position;

	if (!robot.send(buf,3)) cout <<"Could not send readUltrasonicLumi command "<< endl;
    
	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting readUltrasonicLumi command."<< endl;
	}

  	ushort lum = buf[2];
	lumi[0] = (double) lum;
	return lumi;
}

double *RoboDeckSensors::readTempAndHumidity(RoboDeck &robot) {

	unsigned char buf[256];
	int size; 
	double *temperatureHumidity;
	temperatureHumidity = (double*) malloc (4 * sizeof(double));

	buf[0] = 0x02;
	buf[1] = 0x0A;

	if (!robot.send(buf,2)) cout <<"Could not send readTempAndHumidity command "<<endl;

	if ((size=robot.receive(buf))<0){
		cerr <<"Error: getting readTempAndHumidity command."<<endl;
	}

	ushort tempH  = buf[2];
	ushort tempL  = buf[3];
	ushort humidH = buf[4];
	ushort humidL = buf[5];

	temperatureHumidity[0] = (double) tempH ;
	temperatureHumidity[1] = (double) tempL ;
	temperatureHumidity[2] = (double) humidH ;
	temperatureHumidity[3] = (double) humidL ;

	return temperatureHumidity; // return temperatureH, temperaturL,humidityH and humidityL
} 
