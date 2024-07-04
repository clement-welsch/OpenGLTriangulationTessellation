# OMI
OMI Technical test

## C++ Programming Assignment

### Goal

---

In this assignment we want to see your ability to write clean, maintainable, and efficient C++ to solve the sort of problem that is common in computer graphics. You can make this as simple or complex as you like and you are free to write the algorithm from scratch or use third party libraries. Do what you think best demonstrates your skills and explain your choice.

### Assignment

---

The points.json files below each contain an array of 2D points that form the outline of a polygon. You need to write a program that loads these points, displays what you loaded, calculates triangulation/tessellation, and displays the result.

You can display the results as images or create a UI whatever suits you. If you would like to make it interactive or more fancy feel free to do so.

The red lines show the input data and pale triangles with green outlines are what we would like you to calculate.

### What we are looking for

---

- We are looking for clean, maintainable, and efficient C++ code.
- Be creative and impress us.
- Provide clear and detailed build instructions as we will build and run your code.

First thing first, I start this project by creating a private github project to track my code and use pull requests to make evolve my code step by step.
After that, I use "The cherno OpenGL Tutorials" to setup my visual studio project because I beleive he is really reliable.
To load JSON files, I decided to use an homemade reader because the construction of json files provided are really simple.
Otherwise, I would have used rapidjson that I was using at my previous job or jsoncpp.

- Write your own algorithm or use third party libraries. Explain your choice.
- Explain the algorithm that you used.
- Describe pros and cons of your solution.


## 3D High Level Assignment ##

### Goal ###

---

In this assignment we are aiming to understand how you would design a product similar to what we currently have at Omi and how you would plan to improve it in the future. 

### The Assignment ###

---

As you have seen in the first part of the recruitment process Omi provides a service that allows our customers to have a digital twin of their products that can be used to generate a range of advertising media.

We would like you to explain what architecture you would use to build a product similar to this, how you would extend and improve the product in the future, and how you would work with other members of the team to integrate your work.

### What we are looking for ###

---

This is an open ended assignment so feel free to be creative. Here are a few of the things that we will be looking for:

- An overview of how you would structure the product. Talk about all the major components including UI, 3D webview, backend processing, databases, and how artists would add assets.
- How would you achieve the real time 3D rendering?
- How would you achieve high quality final renders?
- How would you extend the product in the future? I’m thinking Metaverse, VR, AR, and interacting with other platforms as well as new features that the customer would use.
- Talk about the assets what type of data would we need to store and how would it be managed.
- How would artists use the system to upload assets and what validation would need performing?
- What is the difference between real time assets and those used for high quality renders?
- What sort of things could you do to improve the efficiency of other members of the team? Especially in relation to product/3D model on-boarding.

### What we are not looking for ###

---

We don’t really expect any code but you are free to add it if you wish.

### src ###
####OpenGL Project Setup####
https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=1

####Delaunay####
https://github.com/jbegaint/delaunay-cpp

####Tesselation####
https://www.youtube.com/watch?v=21gfE-zUym8
https://www.youtube.com/watch?v=OqRMNrvu6TE
https://learnopengl.com/Guest-Articles/2021/Tessellation/Tessellation
