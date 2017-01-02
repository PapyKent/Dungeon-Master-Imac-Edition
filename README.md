# Dungeon-Master-Imac-Edition
Remake of Dungeon Master made during Imac2

to compile
"cmake CMakeLists.txt"
"make"

executable is in "bin/Debug" repertory

Use Z/Q/S/D or W/A/S/D to move.
A/E or Q/E to turn left or right.

SPACEBAR to hit ennemies or to open chest.


LINUX
in CMakeLists.txt change :
  set(LIB_LIST glimac -lmingw32 -lSDLmain -lSDL  -lfreeglut -lglew32s -lopengl32  )
into :
  set(LIB_LIST glimac -lSDL  -lglut -lGLEW -lGL  )
