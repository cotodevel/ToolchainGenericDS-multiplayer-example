This is the Toolchain Generic GDB stub example project:

Compile Toolchain: To compile this project you will need to follow the steps at https://github.com/cotodevel/ToolchainGenericDS: Then simply extract the project somewhere.

Compile this project: Open msys, through msys commands head to the directory your extracted this project. Then write: make clean make

After compiling, run the example in NDS.

Project Specific description: 

A.  UDP NIFI see: https://github.com/cotodevel/ToolchainGenericDS/tree/master/misc/tcp

or

B.  LOCAL NIFI:
in arm9/main.cpp comment: single player and udp nifi
then uncomment localnifi, like this:

//switch_dswnifi_mode(dswifi_idlemode);		//single player:

//switch_dswnifi_mode(dswifi_udpnifimode);	//udp nifi: Check readme

switch_dswnifi_mode(dswifi_localnifimode);	//local nifi: 


Then you must run this in BOTH DS, press L to send a frame to the other DS. The receiver DS will have a frame sent from the Sender (Sender DS Clock Time).

Coto