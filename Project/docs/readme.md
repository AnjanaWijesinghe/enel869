# Ball height controller
The system works with a STM32F103ZG.
The system is implemented to control the height of a ball inside a tube that has a fan attached to the top and a servo motor attached a valve at the bottom with and IR sensor placed at the bottom of the tube.
The system uses PID to control the height of the ball.


## Directory structure
```bash
root/ : Contains all the files of the project.
|- Analysis/ : Contains the anaysis that was conducted, including the scripts that were used for it and the results and the data that was collected to conduct the analysis.
|- Code/ : Contains all the code required to run the ball height controller.
|- | - main.c : main file
|- | - main.h : main file header
|- | - cli/ : Serial communication controller
|- | - drivers/ : clock and gpio drivers
|- | - ir/ : IR sensor contoller
|- | - led/ : LED implemented to debug
|- | - pid/ : PID controller
|- | - servo/ : servo motor controller
|- | - timer/ : timer driver
|- | - utils/ : utility functions
|- DebugConfig/ 
|- docs/ : documents regarding the project including reports and proposals and code documentation
|- | - html/ : code documentation using doxygen
|- | - images/ : images from the report
|- | - videos/ : sample video of the PID controller running and holding the level of the ball
|- | - Notes.docx : Logs taken during the project
|- | - Project plan.docx : Project plan submitted initially
|- | - Project plan.pdf : Project plan submitted initially
|- | - readme.md : that's me!
|- | - Report.docx : final report
|- | - Report.pdf : final report
|- | - Test plan.pdf : test plan created initially
|- Listings/ 
|- Objects/
|- RTE/
|- EventsRecorderStub.scvd
|- project.uvguis.anjan
|- project.uvoptx
|- project.uvprojx
```