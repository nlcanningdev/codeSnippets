/*sources:
https://www.freepascal-meets-sdl.net/sdl-2-0-scancode-lookup-table/
https://github.com/golightlydev/codeSnippets/blob/master/unicodeAndSDL_ttf.cpp
https://wiki.libsdl.org/Tutorials-TextInput
https://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php
https://wiki.libsdl.org/SDL_TextInputEvent
*/


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <iostream>
#include "dependencies/core/SDL2/include/SDL.h"
#include "dependencies/core/SDL2/include/SDL_main.h"
#include "dependencies/core/SDL2_image/include/SDL_image.h"

int test = SDL_SCANCODE_SLEEP;

struct Button {
    int buttonState; //0 = up, 1 = down
};

struct Input_scancode {
    Button button[282];
    //145 = Home, 166 = numpad7, 146 = pgup, 168 = numpad9, 148 = end, 160 = numpad1, 149 = pgdn, 162 = numpad3, 144 = ins, 169 = numpad0
    
    Input_scancode() {
        for (size_t a = 0; a < 282; ++a) {
            this->button[a].buttonState = 0;
        }
    }
};

int main(int argc, char** argv)
{
    Input_scancode input;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    SDL_Window* window = SDL_CreateWindow("quickTest", 20, 20, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    IMG_Init(IMG_INIT_PNG);
    SDL_Event event;
    SDL_Surface* surface = IMG_Load("special_keydown.png");
    SDL_Texture* textureSpecialKeyDown = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("regular_keydown.png");
    SDL_Texture* textureRegularKeyDown = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    //in real code these will both be FRect or whatever it's called, for smooth movement
    SDL_Rect textureSpecialKeyDownAttributes_src = { 0, 0, 303, 285 }; //the x, y, width and height used to clip the desired subtexture from the texture (in this case, the entire texture)
    SDL_Rect textureRegularKeyDownAttributes_src = { 0, 0, 303, 285 };
    SDL_Rect textureSpecialKeyDownAttributes_dest = { 10, 100, 303, 285 }; //the x, y, width and height used to position the clipped texture in the window
    SDL_Rect textureRegularKeyDownAttributes_dest = { 400,100, 303, 285 };
    bool gameRunning = true;
    bool textInputEnabled = false;
    while (gameRunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            if (textInputEnabled) {

            }
            else {
                if (event.type == SDL_KEYDOWN)
                       input.button[event.key.keysym.scancode].buttonState = 1;
                else if (event.type == SDL_KEYUP) //in the real code, if the state is 1 it would be changed to both
                       input.button[event.key.keysym.scancode].buttonState = 0;
            }
        }
        SDL_RenderClear(renderer);
        if (input.button[89].buttonState == 1) //kp_1
            SDL_RenderCopy(renderer, textureSpecialKeyDown, &textureSpecialKeyDownAttributes_src, &textureSpecialKeyDownAttributes_dest);
        if (input.button[56].buttonState == 1) //slash
            SDL_RenderCopy(renderer, textureRegularKeyDown, &textureRegularKeyDownAttributes_src, &textureRegularKeyDownAttributes_dest);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(textureSpecialKeyDown);
    SDL_DestroyTexture(textureRegularKeyDown);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
