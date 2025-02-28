### Lab 03

The objective of this lab was to implement the integer Taylor series implemetation with 4 terms and compare it with the built-in sine and cosine implementation. The accuracy and speed of the algorithms were observed.

## How to use
1. The setup requires a STM32f103rb.
2. The code should be flashed onto the board (ideally using STM32 CUBE).
3. Connect the device to a PC (or another device that can be used to read I2C).
4. Read serial line at baud 115200.
5. Connect pin D7 to ADALM2000 (or another device that can be used to read signals).
6. The serial line will prompt to enter "1" or "2" for either "sine" or "cosine" methods.
7. Follow the prompts provided which will calculate the values using the two different algorithms and output them one by one in pirad.
8. At the same time, observe the output through Scopy (if using ADALM2000) to observe the time taken for each.

## Under the hood
Pin D7 (PA8) is set as a GPIO output pin which is used to keep track of time taken to run.
USART1 is enabled and I2C is used to communicate via the serial port at 115200 baud rate.
The internal cluck was run at the default 72MHz.

The Taylor series implementations are in trig.c with the associated trig.h.
The main.c is the main file.

Once started, the software will prompt to select whether sine or cosine is to be run. When selected, it will then prompt to enter any key when ready to run the next step (and will do after every step). Each of the following pirads will be taken as input and the selected algorithm will be used to generate the output. 
1. 0
2. 0.3
3. 0.5
4. 0.8
5. 1
6. -0.3
7. -0.5
8. -0.8
9. -1

The Pin D7 will be set to high right before the calculation starts and then to low right after it ends.

## Issues and modifications
The Taylor series implemetation was implemented without any issues.
The in-built functions were used without any issues.
The output of the Taylor series implementation is directly output as a fraction in pirad.
The output of the in-built functions are converted to pirad and then output.

## Other
The documented information about the timings and accuracy is stored in Lab03.docx under the root directory.
