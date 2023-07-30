# AGL - Another Graphics Library - alpha
AGL is a C++ graphics library that helps make displaying graphics easy and simple, it uses X11 for the window management and OpenGL for drawing graphics onto the screen. It's syntax takes heavy inspiration from SFML so it is object-oriented.

## Why
This reason for making this is that I wanted a graphics library that had 3D support but I didnt want to use something like GLFW as it is very bare bones in that you need to manually make the OpenGL calls to do anything, so I decided to make a library that lets you code in a syntax similar to SFML but also let you create both 2D and 3D environemts.

## Dependencies
- Xorg (only on linux)
- GLFW (only on windows)
- OpenGL
- GLEW
- SOIL
- FreeType2

## Note
I recommend not using AGL as I am planning to rewrite this library, most likely when this happens it will be under a new repository that I will link to on this readme when it is made.

## License
The AGL source code is distributed under the MIT License.

## TODO
- Add comments to code
- Tutorials on website
- Create a few basic examples
	- Orbit sim (interactive with text)
	- Orbit sim but in 3D
	- simple minecraft clone
- switch to Vulkan?
