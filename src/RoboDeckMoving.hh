/*
 * Copyright 2012 - Guilherme Orlandini
 * Author: Guilherme Orlandini (guilherme_orlandini AT bol DOT com DOT br)
 * Header class Robodeck Moving
 * Date: 03/02/2012 (dd/mm/yyyy)
 *
 * Updates:
 * Author: R.S. Pissardini
 * Date: 04/05/2014 (dd/mm/yyyy)
 * Obs: -Corrections
 *      -Optimization and standardization of code
 *      -MIT License.
 */

#include <string>
#include "RoboDeck.hh"

class RoboDeckMoving {

  public:
		bool lockTranslationWheel(int wheel, int status,RoboDeck &robot);
		bool motorTurn(int wheel, int angle, RoboDeck &robot);
		bool motorMove(int side,int intensity_H, int intensity_L, RoboDeck &robot);  
		double motorGetPeriodLap(int side, RoboDeck &robot);
		int motorGetEncoderLaps(int side, RoboDeck &robot);
		bool motorResetEncoder(RoboDeck &robot);
		bool motorLock(int side, int status,RoboDeck &robot);
		bool moveRobot(int intensity_H, int intensity_L, RoboDeck &robot);
		bool turnRobot(int angle, int intensity_H, int intensity_L,RoboDeck &robot);
		bool strafeRobot(int angle, int intensity_H, int intensity_L,RoboDeck &robot);
		bool spinRobot(int side, int intensity_H, int intensity_L,RoboDeck &robot);

};
