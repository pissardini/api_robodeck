/*
 * Copyright 2012 - Guilherme Orlandini
 * Author: Guilherme Orlandini (guilherme_orlandini AT bol DOT com DOT br)
 * Date: 02/02/2012 (dd/mm/yyyy)
 *
 * Updates:
 * Author: R.S. Pissardini <rodrigo AT pissardini DOT com> 
 * Date: 04/05/2014 (dd/mm/yyyy)
 * Obs: - Corrections
 * 	- Optimization and standardization of code
 *	- Eliminating strings in favor of other types of variables
 * - MIT License
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <string>

#include "RoboDeck.hh"
#include "RoboDeckMoving.hh"

using namespace std;

bool RoboDeckMoving::lockTranslationWheel(int wheel, int status, RoboDeck &robot){

	//wheel - [0] front-left [1] front-right [2] back-left [3] back-right
	//status - energyze [0] true [1] false

	unsigned char buf[256];
	int size;

  	buf[0] = 0x02;
  	buf[1] = 0x01;
	switch(wheel){
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

  	if(status==1) buf[3] = 0xff;
	else buf[3] = 0x00;

  	cout <<"Sending lockTranslationWheel command."<<endl;

        if (!robot.send(buf,4)){
		cout <<"Could not send lockTranslationWheel command "<< endl;
        }

	if ((size=robot.receive(buf))<0){
          cerr <<"Error: receiving RoboDeck's lockTranslationWheel command."<< endl;
          return false;
        }

	if (buf[0] != 0x82 || buf[1] != 0x01){
		cerr <<"Error: RoboDeck could not respond to lockTranslationWheel command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else{
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return true;
	}
	
}


bool RoboDeckMoving::motorTurn(int wheel,int angle,RoboDeck &robot){
	//wheel - [0] front-left [1] front-right [2] back-left [3] back-right
	//angle - in degrees

	unsigned char buf[256];
	int size;

  	buf[0] = 0x02;
  	buf[1] = 0x02;
	
	switch(wheel){
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
	
	if(angle> -33 && angle < 33) buf[3] = angle;
	else {
		cout <<"Isn't possible turn the wheel to angle informed.";	
		return false;
	}

	cout <<"Sending motorTurn command."<< endl ;

	if (!robot.send(buf,4)){

		cout <<"Could not send motorTurn command "<< endl;
		return false;
        }

	if ((size=robot.receive(buf))<0){
        
		cerr <<"Error: receiving RoboDeck's motorTurn command."<< endl;
		return false;
	}


	if (buf[0] != 0x82 || buf[1] != 0x02){

		cerr <<"Error: RoboDeck could not respond to motorTurn command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else return true;
}


bool RoboDeckMoving::moveRobot(int intensity_H, int intensity_L, RoboDeck &robot){
	unsigned char buf[256];
	unsigned int size = 0;
	buf[0] = 0x03;
	buf[1] = 0x01;
	if(intensity_H < 32768 && intensity_H > -32766 && intensity_L < 32768 && intensity_L > -32766){
		buf[2] = intensity_H;
		buf[3] = intensity_L;
	} else return false;
	if (!robot.send(buf,4)) return false;
	if ((size = robot.receive(buf))<0) return false;
	if (buf[0] != 0x83 || buf[1] != 0x01) return false;
	else return true;
}

bool RoboDeckMoving::motorMove(int side,int intensity_H, int intensity_L, RoboDeck &robot){

	//side = [0] Left [1]Right 
     
	unsigned char buf[256];
	int size;

  	buf[0] = 0x02;
  	buf[1] = 0x03;
	buf[2] = 0xff;  
        
	switch(side){
		case 0:
			buf[2] = 0x00; 
		break;
		case 1:
			buf[2] = 0xff; 
		break;
	}	

	if(intensity_H < 32768 && intensity_H > -32766 && intensity_L < 32768 && intensity_L > -32766){
		buf[3] = intensity_H;
		buf[4] = intensity_L;
	}else {
		cout <<"Is not possible move the robot with the intensity informed.";	
		return false;
	}

	cout <<"Sending moveRobot command."<< endl ;
	
	if (!robot.send(buf,5)){
		cout <<"Could not send moveRobot command "<< endl;
		return false;
	}

	if ((size =robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's moveRobot command."<< endl;
		return false;
	}

	if (buf[0] != 0x82 || buf[1]!= 0x03){
		
		cerr <<"Error: RoboDeck could not respond to moveRobot command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else return true;
}


double RoboDeckMoving::motorGetPeriodLap(int side, RoboDeck &robot){

	//side = [0] Left [1]Right 

	unsigned char buf[256];
	int size;
	double time=0;

  	buf[0] = 0x02;
  	buf[1] = 0x04;
	

	if(side==0) buf[2] = 0x00;  
        else buf[2] = 0xff;

	cout <<"Sending motorGetPeriodLap command."<< endl ;

        if (!robot.send(buf,3)){
		cout <<"Could not send motorGetPeriodLap command "<< endl;
		return time;
	}

	if ((size=robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's motorGetPeriodLap command."<< endl;
		return time;
	}

	if (buf[0] != 0x82 || buf[1] != 0x04){
		cerr <<"Error: RoboDeck could not respond to motorGetPeriodLap command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return time;
	}else{
		time = (buf[3]);
		return time;
	}
}

int RoboDeckMoving::motorGetEncoderLaps(int side, RoboDeck &robot){

	//side = [0] Left [1]Right 

	unsigned char buf[256];
	unsigned int size= 0, laps=0;

  	buf[0] = 0x02;
  	buf[1] = 0x05;

	if(side ==0) buf[2] = 0x00;  
	else buf[2] = 0xff;
	
	cout <<"Sending motorGetEncoderLaps command."<<endl;
	
	if (!robot.send(buf,3)){
		cout <<"Could not send motorGetEncoderLaps command "<<endl;
		return laps;
	}

	if ((size=robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's motorGetEncoderLaps command."<< endl;
		return laps;
	}

	if ( buf[0] != 0x82 || buf[1] != 0x05 ){
		cerr <<"Error: RoboDeck could not respond to motorGetEncoderLaps command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return laps;
	}else{
		laps = (buf[3]);
		return laps;
	}
}

bool RoboDeckMoving::motorResetEncoder(RoboDeck &robot){

	unsigned char buf[256];
	unsigned int size;
	
	buf[0] = 0x02;
	buf[1] = 0x06;

	cout <<"Sending motorResetEncoder command."<<endl;

	if (!robot.send( buf, 2 )){
		cout <<"Could not send motorResetEncoder command "<< endl;
		return false;
	}

	if ( (size = robot.receive( buf )) < 0 ){
		cerr <<"Error: receiving RoboDeck's motorResetEncoder command."<< endl;
		return false;
	}

	if (buf[0]!= 0x82||buf[1] != 0x06 ){
		cerr <<"Error: RoboDeck could not respond to motorResetEncoder command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else return false;

}

bool RoboDeckMoving::motorLock(int side, int status,RoboDeck &robot) {

	//side = [0] Left [1]Right 
	//status =[0] true [1] false

	unsigned char buf[256];
	int size;

  	buf[0] = 0x02;
  	buf[1] = 0x07;

	if(side==0) buf[2] = 0x00;  
	else buf[2] = 0xff;

  	if(status==1) buf[3] = 0xff;
	else buf[3] = 0x00;

  	cout <<"Sending motorLock command."<< endl ;

        if (!robot.send(buf,4)) cout <<"Could not send motorLock command "<< endl;

	if ( (size = robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's motorLock command."<< endl;
		return false;
	}

	if ( buf[0] != 0x82 || buf[1] != 0x07 ){
		cerr <<"Error: RoboDeck could not respond to motorLock command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else{
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return true;
	}
}

bool RoboDeckMoving::turnRobot(int angle,int intensity_H, int intensity_L, RoboDeck &robot){
	//angle - in degrees
	
	unsigned char buf[256];
	register unsigned int size = 0;
  	buf[0] = 0x03;
  	buf[1] = 0x02;

	if(angle > -33 && angle < 33) buf[2] = angle;
	else return false;

	if(intensity_H > -32766 && intensity_H < 32768 && intensity_L > -32766 && intensity_L < 32768){
                buf[3] = intensity_H;
                buf[4] = intensity_L;
	} else return false;

        if (!robot.send(buf,5)) return false;

	if ((size = robot.receive(buf))< 0) return false;

	if ( buf[0] != 0x83 || buf[1] != 0x02) return false;
 	 else return true;
}

bool RoboDeckMoving::strafeRobot(int angle,int intensity_H, int intensity_L, RoboDeck &robot){

	//angle - in degrees
	unsigned char buf[256];
	register unsigned int size;

	buf[0] = 0x03;
  	buf[1] = 0x03;
  
	if(angle > -33 && angle < 33) buf[2] = angle;
	else {
		cout <<"Is not possible turn the wheel to angle informed:";
		return false;
	}

	if(intensity_H < 32768 && intensity_H > -32766 && intensity_L < 32768 && intensity_L > -32766){
		buf[3] = intensity_H;
		buf[4] = intensity_L;
	}else{
		cout <<"Is not possible strafe the robot with the intensity informed.";
		return false;
	}

	cout <<"Sending strafeRobot command."<< endl ;
        
	if (!robot.send(buf,5)){
		cout <<"Could not send strafeRobot command "<< endl;
		return false;
	}

	if ((size=robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's strafeRobot command."<< endl;
		return false;
	}

	if ( buf[0] != 0x83 || buf[1] != 0x03 ){
		cerr <<"Error: RoboDeck could not respond to strafeRobot command." << endl;
		ushort saida = (buf[1]);
		cout <<"Buffers: "<< saida << endl;
		return false;
	}else return true;
}

bool RoboDeckMoving::spinRobot(int side,int intensity_H, int intensity_L, RoboDeck &robot){
	
	//side [0] left [1] right
	unsigned char buf[256];
	register unsigned int size;
	
	buf[0] = 0x03;
	buf[1] = 0x04;
  
	if(side==0) buf[2] = 0x00;
	else buf[2] = 0xff;

	if(intensity_H < 32768 && intensity_H > -32766 && intensity_L < 32768 && intensity_L > -32766){
		buf[3] = intensity_H;
		buf[4] = intensity_L;
	}else {
		cout <<"Is not possible spin the robot with the intensity informed.";	
		return false;
	}

	cout <<"Sending spinRobot command."<< endl;

	if (!robot.send(buf,5)){
		cout <<"Could not send spinRobot command "<< endl;
		return false;
	}

	if ((size=robot.receive(buf))<0){
		cerr <<"Error: receiving RoboDeck's spinRobot command."<< endl;
		return false;
	}

	if ( buf[0] != 0x83 || buf[1] != 0x04 ){
		cerr <<"Error: RoboDeck could not respond to spinRobot command." << endl;
		return false;
	}else return true;
}
