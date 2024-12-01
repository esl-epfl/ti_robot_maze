---------------------------------------------
Setting up work environment (as in module 1)
---------------------------------------------
 - Install CCS (http://www.ti.com/tool/ccstudio)
 - On Windows, Launchpad drivers are installed when USB is plugged in
 - Import "inc" and "LineFollowRobot" (CCS imports them as separate projects, check that the #include paths are correct)
 - Templates for all labs available at http://www.ti.com/lit/zip/SLAC768

---------------------
Programming the robot
---------------------
 - For some reason, copying the relevant .c files in "inc" into the project directory may be necessary
 - N.B. The completed files in "inc" are sometimes sketchy, e.g. the motors are very jerky at low speed and don't go backwards
 - LaunchPad is flashed by building and running the code as Debug
 - For easier debugging, the LaunchPad can run the code while plugged in and without batteries (press Resume after flashing), including printf over USB to the CCS console
