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

#include "RoboDeck.hh"
#include <string>

class RoboDeckLocal {
	public:
		double *readCompass (RoboDeck &robot);
		double *readAccelerometer (RoboDeck &robot);
		void readGPSInfo (RoboDeck &robot);
		int *readGPSValidate (RoboDeck &robot);
		int *readGPSSatellite (RoboDeck &robot);
		double *readGPSTime (RoboDeck &robot);
		double *readGPSDate (RoboDeck &robot);
		double *readGPSLatitude (RoboDeck &robot);
		double *readGPSLongitude (RoboDeck &robot); 
		double *readGPSAltitude (RoboDeck &robot);
		double *readGPSHead (RoboDeck &robot);
		double *readGPSGet (RoboDeck &robot);
};
