#include <iostream>

/*
get the number of times 10% of the x resolution at developer resolution can be tiled on the x axis
at developer resolution
then get the number of times 10% of the x resolution at developer resolution can be tiled on the y axis at
developer resolution

then, divide the current x resolution by the number of tiles at developer resolution on the x axis
divide the current y resolution by the number of tiles at developer resolution on the y axis
get the closest int values for both

ie. 1920 / 10 = 192
tileNumX = 100 / 10 (equal to 10, obviously)
1080 / 192 = 5.625
1600 / 10 = 160
900 / 5.625 = 160


this should keep the program looking reasonably close to how it did at developer resolution

get resolution x from setting in ini file. on first time running program, use some method to get desktop display resolution

for things like ui, a different calculation is going to be needed
*/

int main() {
    double developerTileNumX = 10;
    double developerTileNumY = 5.625;
    int currentResolutionX = 1600;
    int currentResolutionY = 900;
    int resultX = (int)((double)currentResolutionX / developerTileNumX);
    int resultY = (int)((double)currentResolutionY / developerTileNumY);
    std::cout << "size of 1 metre tile on x axis in pixels: " << resultX << std::endl;
    std::cout << "size of 1 metre tile on y axis in pixels: " << resultY << std::endl;
    return 0;
}
