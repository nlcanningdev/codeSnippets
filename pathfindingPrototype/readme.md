Creates an sdl window that displays a world of the same size as the window (1600 * 960 pixels).

All textures used are 64 * 64 pixels: 
one background texture tiled across the entire world, 
a texture that represents an obstacle in the world, that is used 30 times in the world,
a texture used for the user controlled character
and a texture used for the computer controlled character.

To exit the program, use the window x button.

To move the user controlled character, use the wasd keys.

To request that the computer controlled character move to the spot currently occupied by the user, press x,
once the computer character has reached the last point requested.

there is no collision between the computer character and the user character, but the user can collide with obstacles
or the edge of the world, and the computer character will avoid them, finding the quickest path, while accounting for
obstacles.
