# Triangulation and Tessellation


## Goal

---
The goal of the project is to ally triangulation and tessellation on various shapes of polygons.

## How to use it
---
The project is available on my personal github account : https://github.com/clement-welsch
Visual Studio 2022 has been used for this project with some dependencies :
+ OpenGL
+ GLEW
+ GLFW
+ GLM
+ mapbox/earcut : https://github.com/mapbox/earcut.hpp
The headers and libraries have been linked dynamicly so it should not need any extra work from yourselves to use them in the project.

To open the project, click on 'OMITessellation/OMITessellation.sln'
If you are using an other version of VS or c++ compiler, you might need to 'Retarget Projects'.
+ Open the project on Visual Studio
+ Right-click on OMITessellation inside the 'Solution Explorer dongle' and select 'Retarget Projects'

Press 'F7' to check if the project compiles correctly.
Press 'F5' to launch the execution of the project.
Once the project is launched, a console will open with the possibility to choose on shape to test :
1- Square shape
2- Inifinite shape
3- C letter shape
4- Chaos shape
5- Quit the program

## Folder architecture
OMITessellation contains the 'C++ Programming Assignment'
OMITessellation\api contains the dependencies.
OMITessellation\include & OMITessellation\src contain the source code of the project.
OMITessellation\res contains the JSON files and the shader files.

## Project architecture

### OpenGL
The architecture of the OpenGL project has been done following the structure of project proposed by an gaming programmer influencer : The Cherno - OpenGL series. (1)
I built the classes needed to setup the 3D API, linked the dependencies, load the json file, parse and compile the shader.
Applicaton is the main file of the project, it will launch the console, ask the loading of the shape and proceed the rendering loop for drawing and the Tessellation of the polygon.

The class Shape manages the loading of the polygon chosen and apply the ear clipping triangulation to get the indexes array.
All the setup of the shaders involed are proccess by the class Shader :  parse, compile, link to the shader progam and released.
In the rendering loop inside the Application, we call Renderer.Draw(...) which will manage the drawing of the polygon and the tesselation result.

### Triangulation
At the beginning of the project, I chose to use the Delaunay algorithm to perform the triangulation of the shape.
But an issue accured quite fast due to the concave shape of the polygons. (2) & (3)
I have tried to implement a concave hull overlayer to the algorithm to fix the issue but it did not work properly on 50% of the shapes. (4)

After few research, I found out another algorithm which is less popular and less documented : Ear-Clipping.
I found few articles and projects which have implemented it. (5)
I decided to use the work of 'mapbox/earcut' who did a great job nonetheless, I had to adapt it to my needs. (6)

### Tessellation
Due to the algorithm of triangulation that has been chosen to define the indexes array. 
The tessellation performed at this stage will be on 3 vertices patches.
The vertex shader is really simple, it multiply the matrix MVP (Model View Projection) to the vertex coordinates.

### src ###
#### OpenGL Project Setup ####
+ (1) https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=1

#### Delaunay ####
+ (2) https://mapbox.github.io/delaunator/
+ (3) https://github.com/delfrrr/delaunator-cpp
+ (4) https://github.com/senhorsolar/concavehull

#### TriangulationByEarClipping ####
+ (5) https://www.geometrictools.com/Documentation/TriangulationByEarClipping.pdf
+ (6) https://github.com/mapbox/earcut.hpp

####Tesselation####
+ https://www.youtube.com/watch?v=21gfE-zUym8
+ https://www.youtube.com/watch?v=OqRMNrvu6TE
+ https://learnopengl.com/Guest-Articles/2021/Tessellation/Tessellation
+ https://github.com/sp4cerat/OpenGL-Tessellation-Shader-Tutorial-C-/tree/master

+ https://gamedev.stackexchange.com/questions/153391/opengl-tessellation-shader-not-working
