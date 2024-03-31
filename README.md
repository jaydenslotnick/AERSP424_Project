# NFL Mock Draft Simulation Code README

This README file provides instructions on how to compile and run the NFL Mock Draft Simulation Code.

## Cloning the Repository

Follow these steps to clone the repository from GitHub into a local directory of your choice:

1. Copy and paste this link into your browser: [https://github.com/jaydenslotnick/AERSP424_Project](https://github.com/jaydenslotnick/AERSP424_Project).
2. Click the "Code" dropdown in the upper right side of the webpage and copy the HTTPS clone URL.
   - If you encounter issues with step 2, use this link instead: [https://github.com/jaydenslotnick/AERSP424_Project.git](https://github.com/jaydenslotnick/AERSP424_Project.git).
3. Navigate to the desired file directory on your local machine to clone the repository.
4. Right-click and choose the option "Open Git Bash here." Note: If Git Bash is not installed on your device, install it before proceeding.
5. Type `git clone` followed by the clone link obtained in step 2. Example: `git clone https://github.com/jaydenslotnick/AERSP424_Project.git`.
6. Close Git Bash.

## Building the Solution Code with CMAKE

Follow these steps to use CMAKE to build the solution code:

1. Open the folder named "AERSP424_Project" that was created during the cloning process.
2. Create a new folder called "build" within the "AERSP424_Project" folder.
3. Navigate inside the "build" folder that you just created.
4. Right-click and choose the option "Open Git Bash here."
5. Type `cmake ..` and press Enter. Note: If CMAKE is not installed on your device, install it before proceeding with this step.
6. Navigate back to the "AERSP424_Project" folder.
7. Copy and paste the following CSV files into the "build" folder: `Half_PPR_TopPlayers.csv`, `NFL_TopPlayers.csv`, `PPR_TopPlayers.csv`.
8. Open the `Fantasy_Football_Mock_Draft_Simulator.sln` file located inside the "build" folder.
9. Right-click on "main" and select "Set as Startup Project."
10. Click on "Build," then select "Build Solution."
11. Click the green run arrow.

Your code should now be compiled and ready to run!
