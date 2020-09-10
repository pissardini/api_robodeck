/*
 * Author: Mauro Enrique de Souza Muñoz (mesmunoz AT gmail DOT com)
 * Original Work: Projeto do software do RoboDeck 0.2, 2009.
 * Date: 06/07/2009 (dd/mm/yyyy)
 *
 * Updates: 
 *	- Author: R. Pissardini <rodrigo AT pissardini DOT com >
 *	- Date: 07/03/2013
 *		- Insert <string.h> for memcpy
 *		- Insert <unistd.h> for ::read, ::close, etc.
		- Cleaning the code.
 */

#include "RoboDeck.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

#define HEADER_SIZE 10

/****************************** Robot Deck *******************************/

/*** constructor ***/

RoboDeck::RoboDeck(){
  _packId     = 0x00;
  _controller = 0;
  _robot      = 0;
  _session    = 0;
  _socket = -1;
}

/*** destructor ***/

RoboDeck::~RoboDeck() { closeConnection();}

/*** open Connection ***/
bool RoboDeck::openConnection(string host,string portStr){
  if (isConnected()) return false;

  ushort port;
  istringstream iss( portStr );
  iss >> port;

  struct hostent *haddr = gethostbyname(host.c_str());
  if (!haddr||!haddr->h_addr[0]){
    cerr << "E_UNKNOWN_HOST" << endl;
    return false;}

  int sock;
  if ((sock = socket(PF_INET, SOCK_STREAM,0))<0){
    cerr << "E_CREATE" << endl;
    return false;}

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = *((uint32_t *) haddr->h_addr);
  addr.sin_port = htons( port );
  struct sockaddr *paddr = (struct sockaddr *)&addr;

  if (::connect( sock, paddr, sizeof(addr))){
    cerr << "E_CONNECT" << endl;
    return false;}

  cout <<"Connected with host "<< host <<" at port "<< port <<endl;
  _socket = sock;
  return true;
}


/*** close Connection ***/
bool RoboDeck::closeConnection(){
  if (!isConnected()) return true;
  ::close(_socket );
  _socket = -1;
  return true;
}

/*** send ***/
bool RoboDeck::send(uchar *data,int size){
  if (!isConnected()||size > 255) return false;

  // Allocates message buffer.
  int    msgSize = HEADER_SIZE + size;
  uchar *msgData = new uchar[msgSize];

  if (! ++_packId ) _packId = 0x01;

  // Fills message header.
  uchar *buf = msgData;
  *buf++ = _packId;
  *buf++ = 0x00;                // Package reference.
  *buf++ = (_controller >> 8);  // Controller ID.
  *buf++ = 0xff & _controller;
  *buf++ = (_robot >> 8);       // Robot ID.
  *buf++ = 0xff & _robot;
  *buf++ = (_session >> 8);     // Session ID.
  *buf++ = 0xff & _session;
  *buf++ = 0x01;                // Command kind (action).
  *buf++ = (uchar)size;         // Command data size.

  // Copy command data to message buffer.
  memcpy( buf, data, size); //destination, source, num - RODRIGO POLI 

  // Write message buffer to connection socket.
  int sent = ::write( _socket, msgData, msgSize );

  delete(msgData);
  return (sent == msgSize);
}

/*** receive ***/
int RoboDeck::receive(uchar *data){
  // Receive header data.
  uchar header[HEADER_SIZE];
  if (::read( _socket, header, HEADER_SIZE) != HEADER_SIZE) return -1;

  // Command's length.
  uchar size = header[9];

  // Read message command.
  if (::read( _socket, data,size)!= size) size = -1;

  return size;
}
