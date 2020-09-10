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
#include "RoboDeckLocal.hh"

using namespace std;

double *RoboDeckLocal::readCompass (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *angle;

	angle = (double*) malloc (2 * sizeof(double));
	buf[0] = 0x03;
  	buf[1] = 0x08;
	
	if (! robot.send(buf,2)) cout <<"Could not send readCompass command."<< endl;
    
	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting readCompass command."<< endl;
	}

	ushort angleH= buf[2];
	ushort angleL= buf[3];
	angle[0] = (double)angleH;
	angle[1] = (double)angleL;

	return angle; //return angleH and angleL
}

double *RoboDeckLocal::readAccelerometer (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *accelerometer;

	accelerometer = (double*) malloc (6 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x09;
	
	if (! robot.send(buf,2)) cout <<"Could not send readAccelerometer command."<< endl;

	if ((size =robot.receive(buf))<0){
		cerr <<"Error: getting readAccelerometer command."<< endl;
	}
	ushort xH= buf[2];
	ushort xL= buf[3];
	ushort yH= buf[4];
	ushort yL= buf[5];
	ushort zH= buf[6];
	ushort zL= buf[7];
	
	accelerometer[0] = xH;
	accelerometer[1] = xL;
	accelerometer[2] = yH;
	accelerometer[3] = yL;
	accelerometer[4] = zH;
	accelerometer[5] = zL;

	return accelerometer; //return xH,xL,yH,yL,zH,zL

}

void RoboDeckLocal::readGPSInfo (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	
	buf[0] = 0x03;
  	buf[1] = 0x0C;

	if (!robot.send(buf,2)) cout <<"Could not send readGPSInfo command "<< endl;

	if ((size = robot.receive(buf))< 0){
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}

	ushort hard= buf[2];
	ushort firm= buf[3];

	cout <<"GPS Info:Hard: "<< hard <<" - Firm: "<< firm << endl;
}

int *RoboDeckLocal::readGPSValidate (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	int *gpsvalidate;

	gpsvalidate = (int*) malloc (1 * sizeof(int));

	buf[0] = 0x03;
  	buf[1] = 0x0D;

	if (! robot.send(buf,2)) cout <<"Could not send readGPSValidate command "<< endl;

	if ((size = robot.receive(buf)) < 0){
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}

	ushort data= buf[2];
	gpsvalidate[0] = int(data);
	return gpsvalidate; //return 0 or 1
}

int *RoboDeckLocal::readGPSSatellite (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	int *gpsnrsatellite;

	gpsnrsatellite = (int*) malloc (1 * sizeof(int));

	buf[0] = 0x03;
  	buf[1] = 0x0E;

	if (! robot.send(buf,2)) cout <<"Could not send readGPSSatellite command "<< endl;

	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}
        
	ushort data= buf[2];
	gpsnrsatellite[0] = int(data);

	return gpsnrsatellite; //return nr. satellites
}

double *RoboDeckLocal::readGPSTime (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpstime;

	gpstime = (double*) malloc (3 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x0F;

	if (! robot.send(buf, 2)) cout <<"Could not send readGPSTime command "<< endl;

	if ((size = robot.receive(buf))< 0){
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}

        ushort hour= buf[2];
	ushort min= buf[3];
	ushort sec= buf[4];

	gpstime[0] = double(hour);
	gpstime[1] = double(min);
	gpstime[2] = double(sec);

	return gpstime; //return hour, min, sec
}

double *RoboDeckLocal::readGPSDate (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpsdate;

	gpsdate = (double*) malloc (3 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x10;

	if (! robot.send(buf,2)) cout <<"Could not send readGPSDate command "<< endl;

	if ((size = robot.receive(buf)) < 0){
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}

	ushort year= buf[2];
	ushort month= buf[3];
	ushort day= buf[4];

	gpsdate[0] = double(year);
	gpsdate[1] = double(month);
	gpsdate[2] = double(day);

	return gpsdate; //return year,month and day
}

double *RoboDeckLocal::readGPSLatitude (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpslatitude = NULL;

	gpslatitude = (double*) malloc (7 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x11;

	if (! robot.send(buf,2)) cout <<"Could not send getRobotProtocolVersion command "<< endl;

	if ((size = robot.receive(buf)) < 0) {
		cerr <<"Error: getting getRobotProtocolVersion command."<< endl;
	}
	
	ushort r1	= buf[0];
	ushort r2	= buf[1];
        ushort deg	= buf[2];
	ushort min	= buf[3];
	ushort fracH	= buf[4];
	ushort fracL	= buf[5];
	ushort dir	= buf[6];

	gpslatitude[0] = double(r1);
	gpslatitude[1] = double(r2);
	gpslatitude[2] = double(deg);
	gpslatitude[3] = double(min);
	gpslatitude[4] = double(fracH);
	gpslatitude[5] = double(fracL);
	gpslatitude[6] = double(dir);

	return gpslatitude;
}

double *RoboDeckLocal::readGPSLongitude (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpslongitude;

	gpslongitude = (double*) malloc (7 * sizeof(double));

	buf[0] = 0x03;
  buf[1] = 0x12;

	if (! robot.send(buf, 2)) cout <<"Could not send readGPSLongitude command "<< endl;
  
	if ((size = robot.receive(buf)) < 0){
		cerr <<"Error: getting readGPSLongitude command."<< endl;
	}

	ushort r1	= buf[0];
	ushort r2	= buf[1];
        ushort deg	= buf[2];
	ushort min	= buf[3];
	ushort fracH	= buf[4];
	ushort fracL	= buf[5];
	ushort dir	= buf[6];

	gpslongitude[0] = double(r1);
	gpslongitude[1] = double(r2);
	gpslongitude[2] = double(deg);
	gpslongitude[3] = double(min);
	gpslongitude[4] = double(fracH);
	gpslongitude[5] = double(fracL);
	gpslongitude[6] = double(dir);

	return gpslongitude;
}

double *RoboDeckLocal::readGPSAltitude (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpsaltitude;

	gpsaltitude = (double*) malloc (2 * sizeof(double));

	buf[0] = 0x03;
  buf[1] = 0x13;

	if (! robot.send( buf, 2)) cout <<"Could not send readGPSAltitude command "<< endl;
   
	if ((size = robot.receive(buf)) < 0){
		cerr <<"Error: getting readGPSAltitude command."<< endl;
	}
        
	ushort dmH	= buf[2];
	ushort dmL	= buf[3];

	gpsaltitude[0] = double(dmH);
	gpsaltitude[1] = double(dmL);


	return gpsaltitude;
}

double *RoboDeckLocal::readGPSHead (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpshead;

	gpshead = (double*) malloc (2 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x15;

	if (! robot.send( buf, 2 ) ) cout <<"Could not send readGPSHead command "<< endl;
    
	if ((size = robot.receive(buf)) < 0 ){
		cerr <<"Error: getting readGPSHead command."<< endl;
	}
        
	ushort dirH	= buf[2];
	ushort dirL	= buf[3];

	gpshead[0] = double(dirH);
	gpshead[1] = double(dirL);

	return gpshead;
}

double *RoboDeckLocal::readGPSGet (RoboDeck &robot){

	unsigned char buf[256];
	int size;
	double *gpsget;

	gpsget = (double*) malloc (10 * sizeof(double));

	buf[0] = 0x03;
  	buf[1] = 0x16;

	if ( ! robot.send( buf,2) ) cout <<"Could not send readGPSGet command "<< endl;
    
	if ((size = robot.receive(buf)) < 0 ){
		cerr <<"Error: getting readGPSGet command."<< endl;
	}
	
	ushort hardf	= buf[2];
	ushort val	= buf[3];
        ushort sats	= buf[4];
	ushort time	= buf[5];
        ushort date	= buf[6];
	ushort lat	= buf[7];
        ushort lon	= buf[8];
	ushort alt	= buf[9];
        ushort speed	= buf[10];
	ushort head	= buf[11];

	gpsget[0] = double(hardf);
	gpsget[1] = double(val);
	gpsget[2] = double(sats);
	gpsget[3] = double(time);
	gpsget[4] = double(date);
	gpsget[5] = double(lat);
	gpsget[6] = double(lon);
	gpsget[7] = double(alt);
	gpsget[8] = double(speed);
	gpsget[9] = double(head);

	return gpsget;
}
