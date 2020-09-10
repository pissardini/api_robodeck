/*
 * Author: Mauro Enrique de Souza Muñoz (mesmunoz AT gmail DOT com)
 * Date: 06/07/2009 (dd/mm/yyyy)
 * RoboDeck control interface library.
 * Updates: 
 *	- Author: R. Pissardini <rodrigo AT pissardini DOT com >
 *	- Date: 07/03/2013
 *		- Cleaning the code.
 */


#ifndef _RoboDeck_
#define _RoboDeck_

#include <string>

/****************************** Robot Deck *******************************/

class RoboDeck {
	public:
	  typedef unsigned char  uchar;
	  typedef unsigned short ushort;
	  RoboDeck();
	  ~RoboDeck();

	  void setController(ushort controllerId)  { _controller = controllerId; }
	  void setRobot     (ushort robotId)       { _robot = robotId; }
	  void setSession   (ushort sessionId)     { _session = sessionId; }

	  // States
	  bool isConnected() {return _socket >= 0;}

	  // Opens a tcp-ip connection.
	  // 'host' is the host name or the host IP address.
	  // 'port' is the port number, in decimal representation.
	  bool openConnection( std::string host, std::string port );

	  // Closes the current connection.
	  bool closeConnection();

	  // Send a message data using RoboDeck's protocol format.
	  // Note that 'size' must be < 256.
	  // Obs: creates RoboDeck's message header and sends it first.
	  bool send( uchar *data, int size );

	  // Fills 'data' with RoboDeck's incoming message command.
	  // Note that no header data is returned!
	  // Returns the message's command size or -1 in case of error.
	  // Note that 'data's buffer must be at least 255 bytes long.
	  int receive( uchar *respData );

  	private:

	  uchar  _packId;
	  ushort _controller;
	  ushort _robot;
	  ushort _session;

	  int _socket;  // Socket connection.
};

#endif
