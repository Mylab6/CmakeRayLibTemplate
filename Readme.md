#CMake RayLib Template 

Zlib licnesed starter for raylib projects 
A very basic template for getting ray lib projects working with CMake
## Supports Web Builds!

This took me the better part of a day to figure out. 
The long story short -> on Ubuntu run build_project.sh
This will create a nice zip file in your build folder that's ready for deployment to itch or another host

#Building locally. 
I'm not really going to cover much here, but this works. 

cmake -S . -B build
cmake --build build

## Included libs. 
This comes with Raylib, RayGui and Physac. 
Eventually I'll include a small game with this repo.

### I AM NOT A C EXPERT.
If something wasn't done the right way, feel free to fork or make a PR. 
This project was born out of my inability to find a an easy way to get started with Raylib. It **should** be easy to get these things working. Web builds awesome!

