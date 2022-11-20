#openGL 

### Resume

Engine provided by Gaetz: [git repository here](https://github.com/Gaetz/opengl-training)

Created a little shader animation using his engine.

Animation preview:

![Image](https://github.com/Oreyato/opengl-training/blob/MarieTheory/cube.gif)

### Navigation 

- Scene
    - .h: [here](https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/src/game/Scene_030_Test.h "https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/src/game/Scene_030_Test.h")
    - .cpp: [here](https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/src/game/Scene_030_Test.cpp "https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/src/game/Scene_030_Test.cpp")
- Tesselation Control Shader: [here](https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.tesc "https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.tesc")
- Tesselation Evaluation Shader: [here](https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.tese "https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.tese")
- Geometry Shader: [here](https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.geom "https://github.com/Oreyato/opengl-training/blob/MarieTheory/AdvancedOpenGL/assets/shaders/030_test.geom")

### Install

1.  clone this repository: [https://github.com/Oreyato/opengl-training](https://github.com/Oreyato/opengl-training "https://github.com/Oreyato/opengl-training")
3.  install cmake: [https://cmake.org/download/](https://cmake.org/download/ "https://cmake.org/download/")

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029294574864187392/unknown.png?width=400&height=27)    
    
3. open the "SDL.zip" and copy the content inside

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029294941718970448/unknown.png?width=380&height=300)
    
4.  follow the path and paste it here:

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029295076083499088/unknown.png?width=400&height=137)
    
    *(in order to solve an issue with git, that don't allow to include executable ~or something like that)*
    
6.  Execute "Visual Studio Installer"
    
7.  Click on "Modifier" (modify) on the latest version you have

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029295559560941600/unknown.png?width=400&height=68)
    
8.  Install C++ for Desktop

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029295839773999104/unknown.png?width=400&height=223)
    
9.  You can now open the project in Visual Code

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029296097673367602/unknown.png?width=155&height=300)
    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029296160126533693/unknown.png?width=400&height=148)

10.  Change the debugger:

    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029296773518331944/unknown.png?width=400&height=46)

    Click right here
    
11.  Choose this one:
    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029296989449506876/unknown.png?width=400&height=123)
    
12.  Type CTRL + SHIFT + P and select CMake:Configure
    ![Image](https://media.discordapp.net/attachments/1029294340700373053/1029297249227907112/unknown.png?width=400&height=81)
    
13.   When the configuration finished, press F7 to compile (as you can see in the screenshot above)
    
14.  If you want to test if everything is working, press F5