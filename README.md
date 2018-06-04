06/04/2018:
Micro$oft has acquired github, you can find updates from this software at: https://coto88.bitbucket.io/
Have a good day.

This is the Toolchain Generic DS netplay example project:

Compile Toolchain: To compile this project you will need to follow the steps at https://github.com/cotodevel/ToolchainGenericDS: Then simply extract the project somewhere.

Compile this project: Open msys, through msys commands head to the directory your extracted this project. Then write: make clean make

After compiling, run the example in NDS.

Project Specific description: 

Press A to disable DSWNIFI 
press B to change to DSWNIFI UDP NIFI mode (setup: https://github.com/cotodevel/ToolchainGenericDS/tree/master/misc/tcp)
press X to change to DSWNIFI localhost mode.

Then you must run this homebrew in BOTH DS, press L to send a frame to the other DS. 
The receiver DS will have a frame sent from the Sender (Sender DS Clock Time).

Coto