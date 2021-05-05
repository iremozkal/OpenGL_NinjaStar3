# OpenGL_NinjaStar3

OpenGL transformations and basic GUI with Visual C++.  

## Tasks

+ Proceeding from the first step of the [previous experiment](https://github.com/iremozkal/OpenGL_NinjaStar2), perform the following requirements:
  + Create a ninja star whose center of mass is located on the origin, initially.
    + Make the star continuously rotate in counter clockwise direction around the z-axis crossing across its center of mass.
      - Add an interface button to start and stop the rotation.
      - Add 2 other buttons to increase and decrease the speed of the rotation and show the current speed on the interface. 
        -  Allowed speed interval should be [-10, 10].
    + Make the star grow and shrink in size like a beating heart, continuously.  
      - Add a button to start and stop the animation.
      - The scaling of the animation should be between 0.5 at its smallest and 1.5 at its largest.
    + Make the star continuously rotate in clockwise direction around the global z-axis, as its center of mass follows a spiral path as shown below.
      - Add a button to start and stop the rotation.
      - Add 2 other buttons to increase and decrease the speed of the rotation and show the current speed on the interface.
        - Allowed speed interval should be [-10, 10].
    + During the animations;
      - The star must not touch the window edges.
      - The spiral motion must be periodic and clear to observe.
      - When restarting a stopped animation, it must resume from where it stopped, not from the beginning.

![ninja star drawing](https://github.com/iremozkal/OpenGL_NinjaStar3/blob/main/Images/img1.PNG?raw=true)

**NOTE**: Implement your homework using OpenGL 3.1 version or higher. All programming assignments must use the shader-based functionality of OpenGL: 1) no immediate mode 2) at least one vertex shader and one fragment shader. Therefore, you should not use any of the deprecated features of the API, e.g. glBegin, glEnd, glVertex3f, glTranslate etc.  


## Solution
+ For rotation, I have theta value and to send the theta information to the vertex shader, loaded uniform variables with ```glUniform1f(theta,Theta)``` then send it to the program.  
+ In vertex shader, for the rotation I calculated the new positions according to these two equations below with uniform theta value and create a matrix according to z axis.  In final the return value from the shader will be multiple of the position and rotation matrix.

  ![ninja star drawing](https://github.com/iremozkal/OpenGL_NinjaStar2/blob/main/Images/equation.PNG?raw=true)  

+ To change the speed of the rotation, Theta constantly increase/decrease with a speed value. For this part, there is counter clockwise rotation. So Theta is decreasing with the speed value. 

+ For grow and shrink animation, I used a scale value to send the theta information to the vertex shader. Then uniform variables are loaded with ```glUniform1f(scaleLoc,scale)``` then send it to the program. I decleare the key ```growShrink = -1``` initially to not use an animation at start. It changes in the program according to growing (1) and shrinking (2). On growing, scale value increases, on shrinking it decreases. And controls the max and min scaling.

+ To follow a spiral path, use an exponential function and translate the center of the shape. Or the center of mass will be translated after each rotation with a translation matrix. I wrote a translate matrix and rotation matrix for x,y,z axises. And took an orbit angle, add an extra matrix of that, similar to the one for z axis. All matrices’ve done with sin cos
equations according to their axis. At the end, multiple all of them in the order ```orbitmatrix * translate matrix * rotation matrices x,y,z * scale matrix * position```. Not worked! This part of the project is needed to be fixed.

+ And during the animation, because of the shape must not touch the windows edge, initially set the position on a smaller one in vertex shader.

+ GLUI used for the interface of this assignment. I created the interface window as a right subwindow of main window. 4 buttons are used: ```Start Rotation```, 
```Stop Rotation```, ```Start Grow/Shrink```, ```Stop Grow/Shrink```. And an input for ```Change the Speed```.  
```
   new GLUI_Separator(glui)         # line seperator 
   new GLUI_StaticText(glui,"...")  # have a better look on titles  
```

## Result
  ![ninja star drawing](https://github.com/iremozkal/OpenGL_NinjaStar3/blob/main/Images/img2.PNG?raw=true)