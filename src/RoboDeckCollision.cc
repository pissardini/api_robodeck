/*
 Copyright (c) 2014 R.Pissardini <rodrigo AT pissardini DOT com> 

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
#include <string>
#include <iostream>
#include <cstdio>

#include "RoboDeck.hh"
#include "RoboDeckCollision.hh"
#include "RoboDeckMoving.hh"


using namespace std;

int RoboDeckCollision::collisionDetection(RoboDeck &robot){

	unsigned char buf[256];
	int size;

	buf[0] = 0x03;
	buf[1] = 0x0B;

	if (!robot.send(buf,2)) cout <<"Could not send collisionDetection command "<< endl;

	if ((size = robot.receive(buf))<0){
		cerr <<"Error: getting collisionDetection command."<< endl;
	}

	ushort data= buf[2];
	return int (data); //return [0] false or [1] true
}
