/*

			Copyright (C) 2017  Coto
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
USA

*/

#include "socket.h"
#include "in.h"
#include <netdb.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "main.h"
#include "InterruptsARMCores_h.h"
#include "specific_shared.h"
#include "ff.h"
#include "memoryHandleTGDS.h"
#include "reent.h"
#include "sys/types.h"
#include "dsregs.h"
#include "dsregs_asm.h"
#include "typedefsTGDS.h"
#include "consoleTGDS.h"
#include "utilsTGDS.h"

#include "devoptab_devices.h"
#include "fsfatlayerTGDS.h"
#include "usrsettingsTGDS.h"

#include "videoTGDS.h"
#include "keypadTGDS.h"
#include "guiTGDS.h"
#include "dmaTGDS.h"

#include "dswnifi_lib.h"

int main(int _argc, sint8 **_argv) {
	
	IRQInit();
	
	bool project_specific_console = false;	//set default console or custom console: default console
	GUI_init(project_specific_console);
	GUI_clear();
	
	sint32 fwlanguage = (sint32)getLanguage();
	
	int ret=FS_init();
	if (ret == 0)
	{
		printf("FS Init ok.");
	}
	else if(ret == -1)
	{
		printf("FS Init error.");
	}
	
	//switch_dswnifi_mode(dswifi_idlemode); is required at program start to properly init dswnifi library
	switch_dswnifi_mode(dswifi_idlemode);		//single player / IDLE
	
	printf("TGDS Multiplayer Example. Need 2 DS");
	printf("Press A: IDLE");
	printf("Press B: UDPNIFI");
	printf("Press X: LOCALNIFI");
	printf("Press L to send frame to external connected DS");
	
	while (1)
	{
		if ((keysPressed() & KEY_A)){
			switch_dswnifi_mode(dswifi_idlemode);		//IDLE: (single player)
			printf("Mode:idle");
		}
		if ((keysPressed() & KEY_B)){
			switch_dswnifi_mode(dswifi_udpnifimode);	//UDP NIFI: Check readme
			printf("Mode:udpnifi");
		}
		if ((keysPressed() & KEY_X)){
			switch_dswnifi_mode(dswifi_localnifimode);	//LOCAL NIFI:
			printf("Mode:localnifi");
		}
		
		if ((keysPressed() & KEY_L)){
			volatile char somebuf[frameDSsize];	//use frameDSsize as the sender buffer size, any other size won't be sent.
			//Sender DS Time
			sprintf((char*)somebuf,"DSTime:%d:%d:%d",getTime()->tm_hour,getTime()->tm_min,getTime()->tm_sec);
			FrameSenderUser = HandleSendUserspace((uint8*)somebuf,sizeof(somebuf));
		}
		IRQVBlankWait();
	}

	return 0;
}