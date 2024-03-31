# AERSP424_Project

This ReadMe file will outline the direction on how to compile and run the NFL Mock Draft Simulation Code.


This section will go over how to clone the repository from github into a local file directory of your choice
1. Copy and paste this link into the browser of your choice: https://github.com/jaydenslotnick/AERSP424_Project
2. Click the "Code" dropdown in the upper right side of te webpage, copy the HTTPS clone URL
3. If having trouble with step 2, use this link: https://github.com/jaydenslotnick/AERSP424_Project.git
4. Navigate to the file directory of your choice to clone the repository
5. Right click and choose the option "Open Git Bash here." Note: if Git Bash is not installed on your device, install it before completing this step. 
6. Type git clone followed by the clone link given in step 3. Example: "git clone https://github.com/jaydenslotnick/AERSP424_Project.git"
7. Close Git Bash

This section will go over using CMAKE to build the solution code
8. Open the folder created named "AERSP424_Project"
9. Create a new folder called "build" contained in the AERSP_424_Project folder
10. Navigate inside the build folder that you just created 
11. Right click and choose the option "Open Git Bash here"
12. Type "cmake .." Note: if CMAKE is not installed on your device, install it before completing this step. 
13. Navigate to the AERSP_424_Project folder
14. Copy and paste the following csv files into the build folder: Half_PPR_TopPlayers.csv, NFL_TopPlayers.csv, PPR_TopPlayers.csv
15. Open the Fantasy_Football_Mock_Draft_Simulator.sln file that is located inside the build folder
16. Right click on "main" and then click on "Set as Startup Project"
17. Click on Build, then Build Solution
18. Click the green run arrow

The code should now be compiled and ready to run!
