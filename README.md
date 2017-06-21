# Nitro
An experimental X window manager designed to be entirely modular

## Introduction
Nitro is an attempt at making a plugin-based minimal window manager with some fresh ideas on how window managing should work. Some of the reasons for this include:
* Compiled plugins for a WM haven't been done as far as I know
* All the cool kids are making window managers these days
* Issues with dealing with my current setup (looking at you fuzzy focus in wmutils)
* A vehicle for my ideas about how we can improve the concepts behind window management

Mostly, this WM solidifies some of the ideas I have been having with regards to [Backflip](http://github.com/laserswald/backflip). 

## Interesting ideas

- **Multiple window selection**:
  This, I think, is the main innovation of Nitro. The concept involves being able to select several windows and perform an operation on all of them at once. Operations on windows like CWM style grouping and workspaces boil down into a program selecting the windows (all the ones on a monitor, perhaps?) and then performing an operation on all of them. I've experimented with this with Backflip a bit, and the idea can be very powerful.

- **Pseudo-windows**: 
  Another interesting concept is the idea of a rectangle on the screen that can be used to specify where windows should go. Imagine drawing a window in Plan 9's Rio, but better. One use case is drawing a rectangle on the screen and making it the "master" part, a la Xmonad. The possibilities are endless. 
  
- **FIFO based IPC**  
- **Compiled plugins**
