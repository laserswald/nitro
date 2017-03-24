# Nitro
_faster than you would think_

## Introduction
Nitro is an attempt at making a plugin-based minimal window manager. Some of the reasons for this include:
* It's never been done as far as I know
* All the cool kids are doing it
* Issues with dealing with backflip
Mostly, this WM solidifies some of the ideas I have been having with regards to [Backflip](http://github.com/laserswald/backflip). 

## Interesting ideas

- **Multiple window selection**:
  This, I think, is the main innovation of Nitro. The concept involves being able to select several windows and perform an operation on all of them at once.
  Operations on windows like CWM style grouping and workspaces boil down into a program selecting the windows (all the ones on a monitor, perhaps?)
  and then performing an operation on all of them. I've experimented with this with Backflip a bit, and the idea can be very powerful.

- **Pseudo-windows**: 
  Another interesting concept is the idea of a rectangle on the screen that can be used to specify where windows should go. Imagine drawing a window in Plan 9's Rio, but better. One use case is drawing a rectangle on the screen and making it the "master" part, a la Xmonad. The possibilities are endless. 
  
- **FIFO based IPC**  
- **Compiled plugins**
