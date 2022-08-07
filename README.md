# AGL - Another Graphics Library
AGL is a C++ graphics library that helps make displaying graphics easy and simple, it uses X11 for the window management and OpenGL for drawing graphics onto the screen. It's syntax takes heavy inspiration from SFML so it is object-oriented.

## Why
This reason for making this is for 2 reasons
1. I wanted a graphics library like SFML that has 3D support (not done yet)
2. I wanted to challenge myself and do something new

## Dependencies
- Xorg
- OpenGL
- GLEW

## Learn
If you want to learn how to use AGL then go to [github website] for documentation and for tutorials on how to use AGL

## License
The AGL source code is distributed under the MIT License, this means that the AGL code is free to be used in any way.

## TODO
- All OpenGL primatives
	- GL_POINTS
	- GL_LINE_STRIP
	- GL_LINE_LOOP
	- GL_LINES
	- GL_LINE_STRIP_ADJACENCY
	- GL_LINES_ADJACENCY
	- GL_TRIANGLE_STRIP
	- GL_TRIANGLE_FAN
	- GL_TRIANGLES
	- GL_TRIANGLE_STRIP_ADJACENCY
	- GL_TRIANGLES_ADJACENCY
	- GL_PATCHES
- Keyboard and mouse support
- Shaders
- Color
- Textures
- Text
- Create a few basic examples
	- Orbit sim (interactive with text)
	- 2d shapes (triangle, rectangle, circle)
	- Texture demo
	- Shader demo
- Caching shape verticies instead of calculating it every frame
	- Might increase fps (dont need to recalculate them every frame)
	- Could be pointless (extra logic may cause a lower fps)
- Tutorials on website
- 3D support
- 3D examples
	- Orbit sim but in 3D
	- 3D shapes
