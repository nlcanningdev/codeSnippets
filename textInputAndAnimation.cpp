/*sources:
https://www.freepascal-meets-sdl.net/sdl-2-0-scancode-lookup-table/
https://github.com/golightlydev/codeSnippets/blob/master/unicodeAndSDL_ttf.cpp
https://wiki.libsdl.org/Tutorials-TextInput
https://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php
https://wiki.libsdl.org/SDL_TextInputEvent
https://wiki.libsdl.org/SDL_ttf/TTF_RenderUNICODE_Blended_Wrapped  for when dealing with windows-specific stuff I think
https://wiki.libsdl.org/SDL_ttf/TTF_RenderUTF8_Blended_Wrapped for everything else
*/


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <iostream>
#include "dependencies/core/SDL2/include/SDL.h"
#include "dependencies/core/SDL2/include/SDL_main.h"
#include "dependencies/core/SDL2_image/include/SDL_image.h"

int test = SDL_SCANCODE_SLEEP;

struct Character {
    
};

struct Button {
    int buttonState; //0 = up, 1 = down
};

struct Input_scancode {
    Button button[283];
    
    Input_scancode() {
        for (size_t a = 0; a < 283; ++a) {
            this->button[a].buttonState = 0;
        }
    }
};

int main(int argc, char** argv)
{
    Input_scancode input;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    SDL_Window* window = SDL_CreateWindow("quickTest", 30, 30, 900, 900, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    IMG_Init(IMG_INIT_PNG);
    SDL_Event event;
    SDL_Surface* surface = IMG_Load("character.png");
    SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect characterAttributes_src = { 0, 0, 55, 81 };
    SDL_FRect characterAttributes_dest = { 0.0f, 0.0f, 55.0f, 81.0f };
    surface = IMG_Load("textAreaBackground.png");
    SDL_Texture* textAreaBackgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect textAreaBackgroundAttributes_src = { 0, 0, 600, 700 };
    SDL_FRect textAreaBackgroundAttributes_dest = { 150.0f, 100.0f, 600.0f, 700.0f };
    surface = IMG_Load("textAreaBorder.png");
    SDL_Texture* textAreaBorderTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect textAreaBorderAttributes_src = { 0, 0, 539, 68 };
    SDL_FRect textAreaBorderAttributes_dest = { 180.0f, 253.0f, 539.0f, 68.0f };
    surface = IMG_Load("textArea.png");
    SDL_Texture* textAreaTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect textAreaAttributes_src = { 0, 0, 522, 50 };
    SDL_FRect textAreaAttributes_dest = { 188.0f, 261.0f, 522.0f, 50.0f };
    surface = IMG_Load("inputCursor.png");
    SDL_Texture* inputCursorTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect inputCursorAttributes_src = { 0, 0, 1, 45 };
    SDL_FRect inputCursorAttributes_dest = { 190.0f, 263.0f, 1.0f, 45.0f };
    surface = IMG_Load("button.png");
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect buttonAttributes_src = { 0, 0, 128, 27 };
    SDL_FRect buttonOKAttributes_dest = { 589.0f, 220.0f, 128.0f, 27.0f };
    SDL_FRect buttonCancelAttributes_dest = { 449.0f, 220.0f, 128.0f, 27.0f };
    //add more stuff here of course



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


        SDL_RenderCopyF(renderer, characterTexture, &characterAttributes_src, &characterAttributes_dest);
        SDL_RenderCopyF(renderer, textAreaBackgroundTexture, &textAreaBackgroundAttributes_src, &textAreaBackgroundAttributes_dest);
        SDL_RenderCopyF(renderer, textAreaBorderTexture, &textAreaBorderAttributes_src, &textAreaBorderAttributes_dest);
        SDL_RenderCopyF(renderer, textAreaTexture, &textAreaAttributes_src, &textAreaAttributes_dest);
        SDL_RenderCopyF(renderer, inputCursorTexture, &inputCursorAttributes_src, &inputCursorAttributes_dest);
        SDL_RenderCopyF(renderer, buttonTexture, &buttonAttributes_src, &buttonOKAttributes_dest);
        SDL_RenderCopyF(renderer, buttonTexture, &buttonAttributes_src, &buttonCancelAttributes_dest);



        SDL_RenderPresent(renderer);
    }



    SDL_DestroyTexture(characterTexture);
    SDL_DestroyTexture(textAreaBackgroundTexture);
    SDL_DestroyTexture(textAreaBorderTexture);
    SDL_DestroyTexture(textAreaTexture);
    SDL_DestroyTexture(inputCursorTexture);



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
