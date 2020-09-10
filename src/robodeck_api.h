/* Copyright (c) 2014 R.S. Pissardini <rodrigo AT pissardini DOT com>

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

#ifndef _ROBODECKAPI_H_
#define _ROBODECKAPI_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "../iniparser/iniparser/src/iniparser.h" //required library

#include "RoboDeckMoving.hh"
#include "RoboDeckInfo.hh"
#include "RoboDeckLocal.hh"
#include "RoboDeckCollision.hh"
#include "RoboDeckSensors.hh"

#define VERSION_MAJOR	"0" //Global Version- 0->infinite
#define VERSION_MINOR	"1" //Production Version- 1- Alpha 2-Beta 3-Release Candidate 4-Public Release
#define VERSION_RELEASE	"0" //Specific Changes - 0->infinite
#define VERSION_DATE	"June 1, 2014" //Date in MM DD,YYYY

#define VERSION "ROBODECK API " VERSION_MAJOR "." VERSION_MINOR "." VERSION_RELEASE \
	" -[ " VERSION_DATE " ] "

#define AUTHORS	"Copyright (C) 2014 R. Pissardini\
		 		 Original source by G.ORLANDINI"
#define HEADER VERSION "\n" AUTHORS "\n"

#define m_clear() if (system("clear")==0) printf("\n");
#define m_error(p,f,e) printf("[Error] %s : %s : %s \n",p,f,e) //state - function - error
#define m_process(p,f,a) printf("[Process] %s : %s : %s \n",p,f,a) //state - function - action


/***Global Variables**********************/

char *ip, *port, *password, *id;
double width, height, lenght, weight, \
       staticsafetydistance, dynamicsafetydistance,distlataxes,distfrontaxes,\
       relationdistanceintensity, energylim, maxvelocity, datetime, weightlim,\
       sensorlimit,maxhumidity, minhumidity,maxtemp,mintemp,maxsteer;
unsigned short category, classvehicle;


RoboDeckMoving roboDeckMoving;
RoboDeckInfo roboDeckInfo;
RoboDeckLocal roboDeckLocal;
RoboDeckCollision roboDeckCollision;
RoboDeckSensors roboDeckSensors;
RoboDeck robo;

//*******CONNECTION FUNCTIONS******************************/

unsigned short connect_api (void);
unsigned short test_api (void);
void disconnect_api (void);

//*******VARIABLES ACCESS FUNCTIONS************************/

char* ip_api(void);
char* port_api(void);
char* password_api(void);
char* id_api(void);
double width_api(void);
double height_api(void);
double lenght_api(void);
double  weight_api(void);
double  staticsafetydistance_api(void);
double  dynamicsafetydistance_api(void);
double  distlataxes_api(void);
double  distfrontaxes_api(void);
double  relationdistanceintensity_api(void);
double  energylim_api(void);
double  maxvelocity_api(void);
double  datetime_api(void);
double  weightlim_api(void);
double  sensorlimit_api(void);
double  maxhumidity_api(void);
double  minhumidity_api(void);
double  maxtemp_api(void);
double  mintemp_api(void);
unsigned short  category_api(void);
unsigned short  classvehicle_api(void);

//*******BASIC FUNCTIONS**************************/

unsigned short collision_api(void);
unsigned short battery_api(void);
double *compass_api(void);
double *acceletometer_api(void);
double *gps_api(void);
double **infrared_api(void);
double **ultrasonic_api(void);
double **ultrasoniclumi_api(void);
double *temperature_humidity_api(void);
void lock_translation_api(int wheel, int status);
void motor_turn_api(int wheel, int angle);
void motor_move_api(int side,int intensity_H, int intensity_L);
double get_period_api(int side);
double get_encoder_api(int side);
void reset_encoder_api(void);
void motor_lock_api(int side,int status);
void move_api(int intensity_H, int intensity_L);
void turn_api(int angle,int intensity_H, int intensity_L);
void strafe_api(int angle,int intensity_H, int intensity_L);
void spin_api(int side, int intensity_H, int intensity_L);


//*******COMBINED FUNCTIONS*************************/

double** collision_combined_api(void);
void move_combined_api (double steer, double distance);
void stop_api (void);

#endif


unsigned short connect_api(){ //Connection with robotic platform
	unsigned short connect = 0;
	m_clear();
	dictionary  * ini ;
	ini = iniparser_load("conf/robodeck_config.ini");
	iniparser_dump(ini, stdout);
	if (!ini) {
		m_error("Connection","Connect","Cannot parse .ini file");
        	return (1);
    	}

	//Loading variables of .ini

	ip = iniparser_getstring(ini, "configuration:ip", NULL);
	password = iniparser_getstring(ini, "configuration:port", NULL);
	id = iniparser_getstring(ini, "configuration:id", NULL);
	width = iniparser_getdouble(ini, "configuration:width", -1.0);
	height= iniparser_getdouble(ini, "configuration:height",-1.0);
	lenght= iniparser_getdouble(ini, "configuration:lenght",-1.0);
	weight= iniparser_getdouble(ini, "configuration:weight",-1.0);
	staticsafetydistance= iniparser_getdouble(ini, "configuration:staticsafetydistance", -1.0);
	dynamicsafetydistance=iniparser_getdouble(ini, "configuration:dynamicsafetydistance", -1.0);
	distlataxes= iniparser_getdouble(ini, "configuration:distlataxes", -1.0);
	distfrontaxes= iniparser_getdouble(ini, "configuration:distfrontaxes", -1.0);
	relationdistanceintensity= iniparser_getdouble(ini, "configuration:relationdistanceintensity", -1.0);
	energylim = iniparser_getdouble(ini, "configuration:energylim", -1.0);
	maxvelocity= iniparser_getdouble(ini, "configuration:maxvelocity", -1.0);
	datetime= iniparser_getdouble(ini, "configuration:datetime", -1.0);
	category= iniparser_getint(ini, "configuration:category", -1);
	classvehicle= iniparser_getint(ini, "configuration:classvehicle", -1);
	weightlim= iniparser_getdouble(ini, "configuration:weightlim", -1.0);
	sensorlimit= iniparser_getdouble(ini, "configuration:sensorlimit", -1.0);
	maxhumidity = iniparser_getdouble(ini, "configuration:maxhumidity", -1.0);
	minhumidity = iniparser_getdouble(ini, "configuration:minhumidity", -1.0);
	maxtemp= iniparser_getdouble(ini, "configuration:maxtemp", -1.0);
	mintemp= iniparser_getdouble(ini, "configuration:mintemp", -1.0);
	maxsteer= iniparser_getdouble(ini, "configuration:maxsteer", -1.0);

	iniparser_freedict(ini);

	//Initializing
	m_clear();
	printf(HEADER);

	printf("Vehicle ID: %s\n",id_api());

	if (ip && port){
		if (roboDeckInfo.openConnection(ip,port,robo)==0){
			if (roboDeckInfo.openSession(robo)==0){
				connect = test_api();
			} else m_error("Connection","Session","Cannot open session with robot.");
		}else m_error("Connection","Connect","Cannot connect with the robotic platform.");
	}

	m_clear();
	return connect;
}

unsigned short test_api(){ //Testing the sensors of robotic platform
	double *double_test_api = NULL;
	int int_sensors_api = 0;
	int flag = 0;

	m_process("Connection","Testing","Analyzing the sensors and integrity of data.");
	double_test_api = roboDeckLocal.readAccelerometer(robo);
	printf("Accelerometer\t\t\t\t\t\t");
	if (double_test_api!= NULL){
		printf("[OK]\n");
		int_sensors_api++;
	}
	else printf("[FAIL]\n");

	double_test_api = NULL;
	printf("Compass\t\t\t\t\t\t\t");
	double_test_api = roboDeckLocal.readCompass(robo);
	if (double_test_api!=NULL){
		printf("[OK]\n");
		int_sensors_api++;
	}else printf("[FAIL]\n");

	double_test_api = NULL;
	printf("GPS\t\t\t\t\t\t\t");
	double_test_api = roboDeckLocal.readGPSGet(robo);
	if (double_test_api!=NULL){
		printf("[OK]\n");
		int_sensors_api++;
	} else printf("[FAIL]\n");

	flag = 0;
	while (flag<2){
		double_test_api = NULL;
		double_test_api = roboDeckSensors.readInfraredSensorHighLevel(flag,robo);
		printf("Infrared-%i\t\t\t\t\t\t", flag);
		if (double_test_api!=NULL){
			printf("[OK]\n");
			int_sensors_api++;
		}else printf("[FAIL]\n");
		flag++;
	}
	double_test_api = NULL;
	double_test_api = roboDeckSensors.readTempAndHumidity(robo);
	printf("Temperature and Humidity\t\t\t\t");
	if (double_test_api!=NULL){
		printf("[OK]\n");
		int_sensors_api++;
	}else printf("[FAIL]\n");

	double_test_api = NULL;
	flag = 0;
	while (flag<4){
		double_test_api = roboDeckSensors.readUltrasonicSensor(flag, robo);
		printf("Ultrasonic -%i\t\t\t\t\t\t", flag);
		if (double_test_api!=NULL){
			printf("[OK]\n");
			int_sensors_api++;
		}else printf("[FAIL]\n");
		flag++;
	}

	double_test_api = NULL;
	flag = 0;
	while (flag<4){
		double_test_api = roboDeckSensors.readUltrasonicLumi(flag, robo);
		printf("Ultrasonic-Lumi -%i\t\t\t\t\t", flag);
		if (double_test_api!=NULL){
			printf("[OK]\n");
			int_sensors_api++;
		}
		else printf("[FAIL]\n");
		flag++;
	}

	int int_battery_api = battery_api ();
	printf ("Battery Level\t\t\t\t\t\t %i", int_battery_api);
	m_process("Connection","Connect","Loading System");

	unsigned int counter_api = 10;
	if (int_battery_api< int (energylim * 100) || int_sensors_api < 4) {
		m_error("Connection","Testing","Insufficient resources for operation");
		while (counter_api!=0){
			printf("Closing system in %i seconds\n",counter_api);
			sleep (1);
			counter_api--;
		}
		m_process("Connection","Connect","Shutdown");
		return(1);
	}
	return(0);
}

void disconnect_api(){
	if (roboDeckInfo.closeSession(robo)==1) m_error("Disconnection","Session","Could not close session with robot");
}

//Getting variables

char* ip_api(){return ip;}
char* port_api(){return port;}
char* password_api(){return password;}
char* id_api(){return id;}
double width_api(){return width;}
double height_api(){return height;}
double lenght_api(){return lenght;}
double  weight_api(){return  weight;}
double  staticsafetydistance_api(){return  staticsafetydistance;}
double  dynamicsafetydistance_api(){return  dynamicsafetydistance;}
double  distlataxes_api(){return  distlataxes;}
double  distfrontaxes_api(){return  distfrontaxes;}
double  relationdistanceintensity_api(){return  relationdistanceintensity;}
double  energylim_api(){return  energylim;}
double  maxvelocity_api(){return  maxvelocity;}
double  datetime_api(){return  datetime;}
double  weightlim_api(){return  weightlim;}
double  sensorlimit_api(){return  sensorlimit;}
double  maxhumidity_api(){return  maxhumidity;}
double  minhumidity_api(){return  minhumidity;}
double  maxtemp_api(){return  maxtemp;}
double  mintemp_api(){return  mintemp;}
unsigned short  category_api(){return  category;}
unsigned short  classvehicle_api(){return  classvehicle;}

//Basic functions

unsigned short collision_api(){ return roboDeckCollision.collisionDetection(robo);}

unsigned short battery_api(){return roboDeckInfo.batteryLevel(robo);}

double *compass_api(){return  roboDeckLocal.readCompass(robo);}

double *acceletometer_api(){return roboDeckLocal.readAccelerometer(robo);}

double *gps_api(){return roboDeckLocal.readGPSGet(robo);}

double **infrared_api(){
	double **infrared = NULL;
	infrared = (double **) calloc(4, sizeof(double *));
	infrared[0] = roboDeckSensors.readInfraredSensorHighLevel(0,robo);
	infrared[1] = roboDeckSensors.readInfraredSensorHighLevel(1,robo);
	infrared[2] = roboDeckSensors.readInfraredSensorHighLevel(2,robo);
	infrared[3] = roboDeckSensors.readInfraredSensorHighLevel(3,robo);
	return infrared;
}

double **ultrasonic_api(){
	double **ultrasonic = NULL;
	ultrasonic = (double **) calloc(4, sizeof(double *));
	ultrasonic[0] = roboDeckSensors.readUltrasonicSensor(0,robo);
	ultrasonic[1] = roboDeckSensors.readUltrasonicSensor(1,robo);
	ultrasonic[2] = roboDeckSensors.readUltrasonicSensor(2,robo);
	ultrasonic[3] = roboDeckSensors.readUltrasonicSensor(3,robo);
	return ultrasonic;
}

double **ultrasoniclumi_api(){
	double **ultrasonic = NULL;
	ultrasonic = (double **) calloc(4, sizeof(double *));
	ultrasonic[0] = roboDeckSensors.readUltrasonicLumi(0,robo);
	ultrasonic[1] = roboDeckSensors.readUltrasonicLumi(1,robo);
	ultrasonic[2] = roboDeckSensors.readUltrasonicLumi(2,robo);
	ultrasonic[3] = roboDeckSensors.readUltrasonicLumi(3,robo);
	return ultrasonic;
}

double *temperature_humidity_api(){return roboDeckSensors.readTempAndHumidity(robo);}

void lock_translation_api(int wheel, int status){roboDeckMoving.lockTranslationWheel(wheel, status, robo);}

void motor_turn_api(int wheel, int angle){roboDeckMoving.motorTurn(wheel, angle, robo);}

void motor_move_api(int side,int intensity_H, int intensity_L){
	roboDeckMoving.motorMove(side,intensity_H,intensity_L, robo);
}

double get_period_api(int side){return roboDeckMoving.motorGetPeriodLap(side, robo);}

double get_encoder_api(int side){return roboDeckMoving.motorGetEncoderLaps(side, robo);}

void reset_encoder_api(){roboDeckMoving.motorResetEncoder(robo);}

void motor_lock_api(int side,int status){roboDeckMoving.motorLock(side,status,robo);}

void move_api(int intensity_H, int intensity_L){roboDeckMoving.moveRobot(intensity_H, intensity_L,robo);}

void turn_api(int angle,int intensity_H, int intensity_L){roboDeckMoving.turnRobot(angle,intensity_H,intensity_L,robo);}

void strafe_api(int angle,int intensity_H, int intensity_L){roboDeckMoving.strafeRobot(angle,intensity_H,intensity_L,robo);}

void spin_api(int side, int intensity_H, int intensity_L){roboDeckMoving.spinRobot(side,intensity_H,intensity_L,robo);}

//Combined functions

double** collision_combined_api(){

	double *result = NULL, **collision = NULL, num_sensors = 0.0;
	unsigned int i = 0;

	collision = (double **)calloc (8, sizeof(double *));

	for (i=0; i<8; i++) {
		collision[i]= (double *) calloc(4, sizeof(double));
	}

	result  = roboDeckSensors.readUltrasonicSensor(0, robo);
	if (result) {
		collision[0][0] = result[1]/100;
		collision[0][1] = 0.0;
		collision[0][2] = 45.0;
		collision[0][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[0][0] = 0.0;
		collision[0][1] = 0.0;
		collision[0][2] = 0.0;
		collision[0][3] = 0.0;
	}

	result  = roboDeckSensors.readUltrasonicSensor(1, robo);
	if (result) {
		collision[1][0] = result[1]/100;
		collision[1][1] = 270.0;
		collision[1][2] = 45.0;
		collision[1][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[1][0] = 0.0;
		collision[1][1] = 0.0;
		collision[1][2] = 0.0;
		collision[1][3] = 0.0;
	}

	result  = roboDeckSensors.readUltrasonicSensor(2, robo);
	if (result) {
		collision[2][0]= result[1]/100;
		collision[2][1] = 90.0;
		collision[2][2] = 45.0;
		collision[2][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[2][0]=  0.0;
		collision[2][1] = 0.0;
		collision[2][2] = 0.0;
		collision[2][3] = 0.0;
	}

	result  = roboDeckSensors.readUltrasonicSensor(3, robo);
	if (result) {
		collision[3][0]= result[1]/100;
		collision[3][1] = 180.0;
		collision[3][2] = 45.0;
		collision[3][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[3][0]= 0.0;
		collision[3][1] = 0.0;
		collision[3][2] = 0.0;
		collision[3][3] = 0.0;
	}

	//Infrared

	result  = roboDeckSensors.readInfraredSensorHighLevel(0, robo);
	if (result) {
		collision[4][0] = result[0]/100;
		collision[4][1] = 45.0;
		collision[4][2] = 5.0;
		collision[4][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[4][0] = 0.0;
		collision[4][1] = 0.0;
		collision[4][2] = 0.0;
		collision[4][3] = 0.0;
	}

	if (result) {
		collision[5][0] = result[1]/100;
		collision[5][1] = 315.0;
		collision[5][2] = 5.0;
		collision[5][3] = 0.0;
		num_sensors=num_sensors + 1.0;
	}
	else {
		collision[5][0] = 0.0;
		collision[5][1] = 0.0;
		collision[5][2] = 0.0;
		collision[5][3] = 0.0;
	}

	result  = roboDeckSensors.readInfraredSensorHighLevel(1, robo);

	if (result) {
		collision[6][0] = result[0]/100;
		collision[6][1] = 270.0;
		collision[6][2] = 5.0;
	}
	else {
		collision[6][0] = 0.0;
		collision[6][1] = 0.0;
		collision[6][2] = 0.0;
	}

	if (result) {
		collision[7][0]= result[1]/100;
		collision[7][1] = 180.0;
		collision[7][2] = 5.0;
	}
	else {
		collision[7][0] = 0.0;
		collision[7][1] = 0.0;
		collision[7][2] = 0.0;
	}

	for (i=0;i<int(num_sensors);i++){
		collision[i][3] = num_sensors;
	}
	return collision;
}


/*Movement */

void move_combined_api (double steer, double distance){
	if (fabs(steer)==0.0) {
		roboDeckMoving.moveRobot(int(distance * relationdistanceintensity), 0, robo);
		sleep(2);
	}else{
		roboDeckMoving.turnRobot(int(steer),int(distance * relationdistanceintensity), 0, robo);
		sleep(2);
	}
}

void stop_api (){
	roboDeckMoving.moveRobot(0, 0, robo);
	sleep(1);
}
