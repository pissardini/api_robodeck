/*
 * Copyright 2012 - Guilherme Orlandini
 * Author: Guilherme Orlandini (guilherme_orlandini AT bol DOT com DOT br)
 * Header- class RoboDeckInfo
 * Date: 03/02/2012 (dd/mm/yyyy)
 * Updates:
 * Author: R.Pissardini <rodrigo AT pissardini DOT com>
 * Date: 31/01/2013 (dd/mm/yyyy)
 * Obs: - Added batteryLevel
 * 	    - Include C++ libraries for C functions
        - Standartization of code 
        - MIT License
 */

#include <cstdlib> 
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>

#include "RoboDeckInfo.hh"
#include "RoboDeck.hh"

using namespace std;

std::stringstream out;

/*** Protocol Version ***/

std::string RoboDeckInfo::getRobotProtocolVersion(RoboDeck &robot){

	unsigned char buf[256];
	int size = 0, vout = 0;
	string vreturn;

	// Build command.
  buf[0] = 0x00;
  buf[1] = 0x00;

  if (!robot.send(buf,2)) cout <<"\nCould not send getRobotProtocolVersion command "<< endl;
    
	if ((size=robot.receive(buf))<0) cerr <<"\nError: getting getRobotProtocolVersion command."<< endl;

	if (buf[0]!=0x80 || buf[1]!=0x00){
    cerr <<"\nError: RoboDeck could not respond to getRobotProtocolVersion command." << endl;
  }else{
 		
		vout = (buf[2]);
		out << vout;
		vreturn = out.str();
		out.str("");
		vreturn = vreturn + ".";
		vout = (buf[3]);
		out << vout;
		vreturn = vreturn + out.str();
		out.str("");	
		vreturn = vreturn + ".";
		vout = (buf[4]);
		out << vout;
		vreturn = vreturn + out.str();
	}
	
	return(vreturn);
}

/*** Open Connection ***/

int RoboDeckInfo::openConnection(std::string host, std::string port, RoboDeck &robot){
	// Connect to MAP
	if (!robot.openConnection(host,port)){
		cout <<"Could not connect to Map."<< endl;
		return (1);
	} else return (0);
}

/*** Open Session ***/

int RoboDeckInfo::openSession(RoboDeck &robot){

	unsigned char buf[256];
	int size;
  	
	// Basic command header (ascii hex representations).
	robot.setRobot(0x0001);  // Robot ID.
	robot.setController(0x0002);  // Controller ID
	robot.setSession(0x0000);  // Session ID (0 == no session).
	
  // Build command.
	buf[0] = 0x01;
	buf[1] = 0x01;
	cout <<"\nSending open session command."<< endl;

	if (!robot.send(buf,2)) return(1);
	

	// Read RoboDeck's opened session ID.
	if ((size=robot.receive(buf))<0) cerr <<"\nError: receiving RoboDeck's openSession response."<< endl;
	
	if (buf[0]!=0x81 || buf[1]!=0x01) return(1);

	ushort session = (buf[2] << 8) | buf[3];
	robot.setSession( session );
	cout <<"\nSession opened: "<< session <<endl;
	return (0);
}

/*** Close Session ***/

int RoboDeckInfo::closeSession(RoboDeck &robot){
  
	unsigned char buf[256];
	int size;

	// Build command.
	buf[0] = 0x01;
	buf[1] = 0x02;
	cout<<"\nSending close session command."<<endl;

	if (!robot.send(buf,2)) return (1);

  	// Wait for RoboDeck's response.
	if ((size=robot.receive(buf))<0) return (1);

	// Validates response.
	if (buf[0]!= 0x81 || buf[1]!=0x02) return (1);

	cout<<"\nSession successfully closed."<< endl;
}

/*** Battery Level ***/

int RoboDeckInfo::batteryLevel (RoboDeck &robot){
	unsigned char buf[256];
	int size;

	buf[0] = 0x03;
	buf[1] = 0x17;

	if (!robot.send(buf,2)){
		cout <<"\nCould not send getRobotProtocolVersion command "<< endl;
	}
    
	if ((size = robot.receive(buf))<0){
		cerr <<"\nError: getting getRobotProtocolVersion command."<< endl;
	}

	ushort charge= buf[2];
	return int(charge);
}
