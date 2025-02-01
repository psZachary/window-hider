# Window Hider
Works by using CreateRemoteThread to remote load a DLL to set the HWND display affinity of each window spawned by the process. Note that this repository is simply a POC and can be edited to fit your project's needs.

### Why use DLL injection? 
To set the display affinity of a window using **SetWindowDisplayAffinity** our process must own the window we are targeting in simpler terms: the parent of the HWND must be the process also setting the display affinity of said window.  

### How to add to your project
This is a single header library and can be included from the [single header include file](https://github.com/psZachary/window-hider/blob/master/test-app/wh/wh.h).

### Important note
This file drops a DLL onto the filesystem which is [encoded into a byte array inside of the header file](https://github.com/psZachary/window-hider/blob/3a22e1c4cacb71e866d78779b81083a7a2f5eece/test-app/wh/wh.h#L6), I would recommend [building the DLL](https://github.com/psZachary/window-hider/tree/master/window-hider) and [converting to the byte array manually](https://notisrac.github.io/FileToCArray/) such that it is trustworthy and that it works on your system. 

### Usage
```c++
#include <wh.h>

int main() {
  // Hide the default notepad window
  wh::hide_window("Untitled - Notepad");
  return 0;
}
```
