# cub3d
The goal of this 42 school's project is to make a dynamic first-person view similar to that of the Wolfenstein 3D game by implementing raycasting.
The MinilibX graphics library is used for rendering.

<img width="664" img align="center" alt="Screenshot of the game" src="https://user-images.githubusercontent.com/92207326/198876988-c08c13db-a2ba-4086-aef6-a40166bf660d.png">

## How to run it
To compile the project :
```
make
```
Then to run the program :
```
./cub3D [path_to_map]
```
ex :
```
./cub3D maps/map1.cub
```
## How to play
Use the W,A,S,D to move and Left/Right arrows to rotate the camera to the left/right.
Esc key to exit.

## Features
* Wall collision
* Textures paths modifiable directly in map files.
* Floor/Ceiling colors modifiable in map files.
* Map structure modifiable in map files.
* Pressing multiple keys at the same time is handled.

## Credits
* [Lode's Computer Graphics Tutorial on Raycasting](https://lodev.org/cgtutor/raycasting.html)
* Wolfenstein 3D textures from ID Software
* [MinilibX](https://github.com/42Paris/minilibx-linux)
