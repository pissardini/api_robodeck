/*
 * Copyright 2012 - Guilherme Orlandini
 * Author: Guilherme Orlandini (guilherme_orlandini AT bol DOT com DOT br)
 * Header- class RoboDeckInfo
 * Date: 03/02/2012 (dd/mm/yyyy)
 * Updates:
 * Author: R.Pissardini <rodrigo AT pissardini DOT com>
 * Date: 31/01/2013 (dd/mm/yyyy)
 * Obs: -Added batteryLevel
        -Updates in MIT License
	-Changes in the return
 */

#include <string>
#include "RoboDeck.hh"

using std::string;

class RoboDeckInfo{
	public: 
  		int openConnection(std::string host,std::string port,RoboDeck &robot);
  		int openSession(RoboDeck &robot);	
  		int closeSession(RoboDeck &robot);
  		std::string getRobotProtocolVersion(RoboDeck &robot);
  		int batteryLevel (RoboDeck &robot);
};
