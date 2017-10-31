This is the Toolchain Generic DS Multiplayer example project:

1)Setup:

a)For UDP NIFI see: https://github.com/cotodevel/ToolchainGenericDS/tree/master/misc/tcp

or

b)For LOCAL NIFI :
in arm9/main.cpp comment: single player and udp nifi
then uncomment localnifi, like this:

//single player:
//switch_dswnifi_mode(dswifi_idlemode);
//udp nifi: 
//switch_dswnifi_mode(dswifi_udpnifimode);	//UDP NIFI: Check readme
//local nifi: 
switch_dswnifi_mode(dswifi_localnifimode);	//LOCAL NIFI:


2)Compile:
To compile this project you will need to follow the steps at https://github.com/cotodevel/ToolchainGenericDS:

Then simply extract the project somewhere.

Compile with Make as usual.


Then you must run this in BOTH DS, press L to send a frame to the other DS. The receiver DS will have a frame sent from the Sender (Sender DS Clock Time).

Coto