# 3DGraphicsGame
 ###  Creating a game / game engine using OpenGL (3.3) and SDL 2  
### I'm creating this project to better learn Graphics Progamming (OpenGL) and also improve in Game Development.  
----------------------------------------------------------------
### This project is coded with C++, using SDL 2 for input, audio, game menu rendering, and window creation with OpenGL being used for the actual game graphics.
----------------------------------------------------------------
![Screenshot](/CPP_OpenGL_ScreenShot.png?raw=true "Screenshot")

# The Rough Idea

 ## SDL 2 will be used to render Game Menu's (options, launch, etc) (I've created the Menu Manager and launcher)
 ## SDL 2 will get input from user (I've created a keyboard manager to keep track of input)
  
 ## OpenGL will be used for Graphics.
    Currently have 3D capabalitiy. Camera view is controlled with WASD / arrow keys(forward,left,etc.) and Keypad for rotation. Space Bar and left Ctrl (Up and down)
    
 ## Terrain Generation
  ![terrain flat grid](/FlatGrid_OpenGL.png?raw=true "Flat Grid screenshot")
 ### Currently I use a grid to generate terrain. I can adjust the size of each grid tile and the number of tiles in each row / column. I then use an equation to change the height values, producing a different terrain. 
  ![terrain grid](/Wireframe_OPENGL_screenshot.png?raw=true "Grid screenshot")
  ### Currently, color of the terrain is modulated by the height.
   ![terrain grid](/OpenGL_Terrain_Smooth.png?raw=true "Grid screenshot")
    
## Gameplay
 ### I completed user-controlled camera movement around the scene. However, I still need to add an actual "game" element. I originally thought I'd make a racing game with randomly generated terrain. However, the physics involved with that are more than I wish to implement right now. I'm thinking I'll make this game an arcade space / airplane dogfight game. I think I could tweak my terrain generation code to form a sphere instead. Thus allowing me to make randomly generated "planets".
 
