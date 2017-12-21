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
	
	printf("TGDS Multiplayer Example. Need 2 DS");
	printf("Recompile Example if you want to ");
	printf("alternate between multiplayer modes");
	
	printf("Press L to send frame to connected DS");
	
	//single player:
	//switch_dswnifi_mode(dswifi_idlemode);
	//udp nifi:
	//switch_dswnifi_mode(dswifi_udpnifimode);	//UDP NIFI: Check readme
	//local nifi: 
	switch_dswnifi_mode(dswifi_localnifimode);	//LOCAL NIFI:
	
	//read IP if udpnifi mode
	if((getMULTIMode() == dswifi_udpnifimode)&&(dswifiSrv.dswifi_setup == true)){
		printf("connected: IP: %s",(char*)print_ip((uint32)Wifi_GetIP()));
	}
	
	while (1)
	{
		//Press L to send a frame to the other DS
		if ((keysPressed() & KEY_L)){
			volatile char somebuf[frameDSsize];	//use frameDSsize as the buffer size, anything above that size won't be sent.
			//Send This DS Time
			sprintf((char*)somebuf,"DSTime:%d:%d:%d",getTime()->tm_hour,getTime()->tm_min,getTime()->tm_sec);
			FrameSenderUser = HandleSendUserspace((uint8*)somebuf,sizeof(somebuf));
		}
		
		if ((keysPressed() & KEY_A)){
			clrscr();
		}
		
		if ((keysPressed() & KEY_B)){
			printf("test!:%d",rand());
		}
		
		IRQVBlankWait();
	}

	return 0;
}