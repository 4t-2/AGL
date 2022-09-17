# AGL - Another Graphics Library - alpha
AGL is a C++ graphics library that helps make displaying graphics easy and simple, it uses X11 for the window management and OpenGL for drawing graphics onto the screen. It's syntax takes heavy inspiration from SFML so it is object-oriented.

## Why
This reason for making this is that I wanted a graphics library that had 3D support but I didnt want to use something like GLFW as it is very bare bones in that you need to manually make the OpenGL calls to do anything, so I decided to make a library that lets you code in a syntax similar to SFML but also let you make both 2D and 3D programs.

## Dependencies
- Xorg
- OpenGL
- GLEW
- GLM

## Learn
If you want to learn how to use AGL then go to [my site](https://synteng.github.io/) for documentation and tutorials on how to use AGL

## License
The AGL source code is distributed under the MIT License.

## TODO
- Transform vertices on GPU instead of CPU
- Create own matrix type (drop GLM dependency)
- Textures (as many filetypes as can be easily done)
- Text (.ttf)
- 3D support
- Add comments to code
- Tutorials on website
- Create a few basic examples
	- Orbit sim (interactive with text)
	- 2d shapes (triangle, rectangle, circle)
	- Texture demo
	- Shader demo
	- Orbit sim but in 3D
	- 3D shapes
	- simple minecraft clone
