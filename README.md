API Robodeck
============

API Robodeck is a Application Programming Interface developed in C/C++  as  interface for robotic platform Robodeck (http://www.xbot.com.br/).

The origin of code were the libraries developed by Mauro E.S. Muñoz. Afterwards, the first proposal of API was presented in the research of Guilherme Orlandini "Development of Applications Based in Techniques of Computer Vision for Autonomous Mobile Robot" (2012).

This API is a complete and updated version based on the Muñoz and Orlandini code, developed by R.S.Pissardini (2012-2014) in this research "Veículos autônomos de transporte terrestre: proposta de arquitetura de tomada de decisão para navegação autônoma". This version still require minor modifications (such Makefile files), but is fully functional for use.

How to Use
==========

The API Robodeck was created in C/C++ and contains all the code and libraries associated for operation. To use:

* Download the API.
* Create your application in directory /test. Add #include "../src/robodeck_api.h"  or the C++ libraries.
* Call the functions as a convenience.
* Configure the .ini file in /conf according to your convenience.
* Compile your code. The most trivial way is:

g++ yourapp ../src/*.hh ../src/*.cc ../3rd/iniparser/*.h ../3rd/iniparser/*.c   -w -o app

For execute, use ./app

For example:

g++ example.c ../src/*.hh ../src/*.cc ../3rd/iniparser/*.h ../3rd/iniparser/*.c   -w -o example

./example

Integrating with the robotic platform
=====================================

* Turn on the robotic platform.
* Connect with wi-fi network of  robotic platform using the password provided by the manufacturer.
* Initialize your application.