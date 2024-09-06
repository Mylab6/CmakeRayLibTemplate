# CMake RayLib Template 

Zlib licnesed starter for raylib projects 
A very basic template for getting ray lib web builds working with CMake
## Supports Web Builds!

This took me the better part of a day to figure out. 
The long story short -> on Ubuntu run build_project.sh
This will create a nice zip file in your build folder that's ready for deployment to itch or another host. 

Alternatively you can use the included Github action to build and deploy to itch. 
Create a environment, call it web. Set your itch api key as a secret called BUTLER, and set ITCH_USERNAME/ITCH_PROJECT_NAME as a secredt called ITCH_URL.


#Building locally. 
I'm not really going to cover much here, but this works. 

cmake -S . -B build
cmake --build build

## Included libs. 
This comes with Raylib, RayGui and Physac. 
Eventually I'll include a small game with this repo.

## CTemplate Branch 

I decided to switch to CPP for my future projects, but the CTemplate branch is avaible if you'd like to try that!

### I AM NOT A C EXPERT.
If something wasn't done the right way, feel free to fork or make a PR. 
This project was born out of my inability to find a an easy way to get started with Raylib. It **should** be easy to get these things working. Web builds awesome!

Uses Kenny Assets:
License: (Creative Commons Zero, CC0)

