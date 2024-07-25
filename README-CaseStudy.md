# **OMI \- 3D High Level Assignment**

# OMI

Omi is a company which provides a strong 3D marketing modeler application for its clients. They use a homemade 3D/C++ engine. You will be able to create a scene with a large variety of accessories, backgrounds and animation to enhance your products (perfume, makeup sport accessory,...). Once the composition of the scene has been done, the application sends it to a powerful cloud computer which will be able to perform a rendering to mimic a photorealistic marketing ad.

# My project

The goal of my project is to propose a fictional alternative to their application. The point of view of this study case is based on the fact that I need to realize this copy on my own and fast enough to be able to provide a beta version of my project to potential fictional clients. For this matter, I will use Unreal Engine for the rendering and the UI (**User Interface**), it is very powerful and well documented.  
Building my own Engine or forking an existing one would be too complicated to maintain by myself. I much prefer to leave this part to focus on the features of the project.

Using Unreal Engine, will also help me to hire in the future developers who are already familiar with it.

## 

## 3D Webview

For the webview part, I would use “Arcane Mirage” or any other concurrents (Arcware,  which provide an efficient way to stream on a webpage an Unreal project.  
[Play Unreal Engine 5 projects on a Web Browser\!](https://www.youtube.com/watch?v=eJTNvSiCZY0)  
[Deploy Unreal Engines Pixel Streaming at scale on AWS](https://aws.amazon.com/fr/blogs/gametech/deploy-unreal-engines-pixel-streaming-at-scale-on-aws/)

When the 3D scene is saved, it will store the data of the scene inside a JSON file which will be useful during the final processing to recreate the scene and animations defined by the client (main object, accessories, positions, rotation, animation, camera,...).

## Rendering

The Unreal engine is extremely powerful, especially with the new version (UE5). The sdk source code is public and modifiable so it could be optimized for the purpose of the 3D modeler. The usage of Unreal is free until you have reached a 1 million $ gross which gives you a lot of freedom at start and access to a top notch engine used in video games, architecture and movies.

## Backend processing

For the backend, I will use the power of AWS/Azure to dynamically allocate cloud machines which will make the 3D final rendering. When a rendering is asked, I will check first if I have a VM (**Virtual Machine**) already installed and ready to work. Otherwise, I will allocate a new one with a light OS installed to win time during the installation and optimize the number of data allowed by my cloud provider. 

The VM will get access from git my repository through terminal commands and launch a CMake script capable of installing dependencies (Visual Studio, Qt creator, Unreal Engine static libraries). When the VM is setup, it downloads the 3D scene script file of the user and it will manage the “build and deploy” steps 

* load the 3D scene script  
* place the camera  
* take a snapshot of the rendering  
* saving the picture on the client page of my website  
* send an email to the client that the rendering is done.

## Databases

For the databases, I would still use my AWS/Azure to store the databases for the website, the renderings and 3D objects imported. To be able to scale the amount of data to store or the number of VM that you need to make your service fluid is really convenient  and I would never be afraid of the saturation of my services. But it comes of course with an expensive price of using it.  
[Cloud Costs for Azure and AWS](https://www.vissensa.com/blog/data-egress-cloud-costs/\#:\~:text=Azure%20provide%20businesses%20with%20the,free%20per%20month%20per%20region.) 

## Final Rendering

Unreal provides a lot of technologies which can provide a high quality Render (Shaders, Nanite, PCG). By placing a camera in the scene and taking a snapshot after launching the simulation I would be able to get a high resolution rendering. It means to be able to control the engine through a script file capable of setting up the 3D scene and launching a rendering.

The rendering pipeline between the webviewer app and the cloud version should be considered differently.

The webviewer will use low quality 3D objects, a restricted number of shaders and need to optimize the interaction of the user when he wants to move the camera or an object with the highest frame rate possible. The usage of graphics effects will be a key to provide an appealing composition with the minimum impact on the interactions : LOD, texture atlas, tessellation, triangulation, deferred rendering…

The Cloud renderer, at the opposite, should use all the enhancing techniques possible : displacement mapping, normal map, subdivision, tessellation, ambient occlusion, Physically Based Rendering (PBR), anti aliasing, nanites (UE5 feature). The mastering of lights and the usage of high quality texture are the key for a photorealistic rendering.

## Add assets

For the 3D scanning object, the easiest way would be to ask the client to scan it with his phone with a 3D app (Kiri Engine, Polycam, Reality Scan) and store it on my website. I will hire an external 3D modeler on Fiverr to rework the 3D model to be able to have a clean version of the 3D object. Blender has a feature called Instance Meshes capable of cleaning fast any aberration that the mobile scanner could have done during the process. It does not seem that an IA machine learning is existing nowadays which could automate this task.

[CLEANING UP A 3D SCAN: WILL IT REPLACE MODELING?](https://3d-ace.com/blog/cleaning-up-a-3d-scan/)  
[Easily Clean Your 3D Scans (blender)](https://www.youtube.com/watch?v=dKo0rWXVAlc)

The artist would have special access to the website to get a list of 3D scans that need to be cleaned. By selecting a new scan, he will access a page where to download the object and where he can upload the clean version. 

If the quality of the scan is poor, the artist could ask the client to remake the scan. It will send an email of warning to the client and a link to a tutorial which explains the best practice to efficiently scan an object and which apps/3D object extensions are recommended.

Once the artist has uploaded the new version of the object, he would submit his work and the client would receive an email to invite him to check the result online. The client could vote for the quality of the cleaning, it will not have an impact on the fees paid to the artist for his work but will decrease his trust factor for a future collaboration. If the client is satisfied with the cleaning, we will be able to delete the 3D scan version of the object and store the cleaned object.

## My tribute

Working with several companies with different sizes gave me a large variety of skills that could help me to be a perfect man in the middle for all the teams working on this project : programmers, artists and clients. I have the conscientious to work efficiently with programmers and provide strong code. My creativity and my previous job at pastagames gave me a good background to understand the vision of the artist and the needs of clients.

Communication between teams is always tricky. We are using different vocabularies to talk about the same things. I believe it is necessary to have weekly meetings with every team to be able to exchange the progress of everyone in order to avoid the loss of important information. You need to be able to view through the perception of other workers to produce something that matters and is useful. In the development team, using “pull request” and asking the approval of your work by one of your pairs can avoid bugs, doublon functions/classes that already exist somewhere.

## Disadvantages

The main disadvantage of this project is the over usage of dependencies : 

+ Rendering : Unreal Engine  
+ Web app : Arcane Mirage  
+ Cloud/Database : AWS/Azure

It liberates the project from a lot of inconveniences, brings flexibility (upscale database, avoids building a full 3D engine,...)  and provides a lot of features ready for use.   
But it will also chain the projects to its dependencies. If a bug affects one of them, it will have a bad impact on the project and I will be forced to wait for a fast correction from the team in charge (the recent shutdown of all the windows computers due to a bug in the antivirus Crowdstrike is a good example).   
Another issue related to use dependencies is also to be forced to adapt our features to the tools they provide. If a desired feature is designed outside the box, we will collide with the capacities that the services provide.

# Extension of the project

To have only one camera in the scene which is used to compose and render is an issue for both sides. It helps the simplification needed at the beginning of the app but now that you have more experienced users. I believe you should be able to separate it into multiple possibilities.  
Another aspect that could be frustrating in OMI at the moment, will be the absence of a tree where you can find all the objects of the scene. It could be tricky to modify an object half hidden in the back of the scene (Translation/Rotation/Scale) .

In  terms of VR, I think OMI will be a perfect match with this technology to emerge the user and virtualise even more the photo shooting experience. Unreal will again be a great asset for it.

For the AR technology, the possibility to place the props and the product inside the environment of the user and render it with an accurate precision could significantly improve the experience by using a natural background instead of using a 2D texture applied on the background.

