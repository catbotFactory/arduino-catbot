# Arduino catbot

this will be the initial sketch loaded to the catbot when shipped with a joystick

## Upload

use avrdude of arduino IDE to upload catbot.ino to the board

## Monitor

ensure that ```serialOut``` is set to true, and upload the sketch to the board, it will open a serial communication (9600 bps) and sent joy X,Y and state changes for button and laser

## TODO

- make a .h for batch upload
- make a version stand alone + controll over serial
