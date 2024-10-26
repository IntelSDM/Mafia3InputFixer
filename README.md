# Mafia 3 Input Fixer

## The problem

In Mafia 3 the mouse position isn't locked by the game from some unknown event. 
This means that while aiming driving or during any event where you move your mouse you will end up with your cursor leaving your game's window; 
This causes you to click outside the window making the game minimise. <br>
It is an extremely annoying bug and a restart will fix it but it happens every hour or so for me which makes the game unplayable.

## The solution
You can download the [release](https://github.com/IntelSDM/Mafia3InputFixer/releases) or build it with visual studio C++.<br> <br>
What the program does is install a low level input hook through setwndowhookex. This allows us to dictate what all the other programs can reieve in terms of input messages.
<br>
Then in our input hook we simply check if the game is the active window, if it isn't we prevent any other window recieving input. Therefore your mouse can't run off to another window and cause you to minimise the game.
<br>
Uses about 0.05% CPU

## Instructions
1) Run the EXE
2) Enjoy playing. 
