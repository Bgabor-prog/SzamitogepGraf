#include <SDL.h>
#include <stdbool.h>
#include <sstream>
#include <vector>

const int width = 800;
const int height = 600;


struct Color{
    int r = 0;
    int g = 0;
    int b = 0;
};

struct Color set_RGB();
int maxRECTANGLECount();

int main(int argc, char ** argv)
{

    SDL_Rect rect;
    rect.w = 100;
    rect.h = 60;

    int MAX_RECTANGLE_COUNT = 0;
    std::vector<SDL_Rect> Rects;

    struct Color rgb;
    rgb = set_RGB();

    MAX_RECTANGLE_COUNT = maxRECTANGLECount();

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("HelloWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_Event event;
    int exit = 0;
    bool drawing = false;
    bool quit = false;
    bool HaveLine = true;


    while (!quit) {
        SDL_Delay(10);
        SDL_PollEvent(&event);

            switch (event.type){
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEMOTION:
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                SDL_Log("Mouse cursor is at %d, %d", mouseX, mouseY);
            break;
            }
            SDL_SetRenderDrawColor(renderer,30,30,30,SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);


            switch (event.type){

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button && HaveLine){
                        case SDL_BUTTON_LEFT:
                            rect.x = event.motion.x;
                            rect.y = event.motion.y;
                            drawing = true;

                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button){
                        case SDL_BUTTON_LEFT:
                            drawing = false;
                            Rects.push_back({rect.x,rect.y,rect.w,rect.h});
                            exit++;
                        break;
                    }
                    break;
        }

        if(exit == MAX_RECTANGLE_COUNT){
            HaveLine = false;
        }

        SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE);
            for (auto & rect: Rects){

                SDL_RenderFillRect(renderer,&rect);
            }



        SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE);
        if (drawing){
            SDL_RenderFillRect(renderer, &rect);
        }
            SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

int maxRECTANGLECount(){
    int maxNum;
    printf("Adja meg mennyi teglalapot rajzoljom ki!(egesz szam)\n-->");
    scanf("%d",&maxNum);
return maxNum;
}

struct Color set_RGB(){

   struct Color rgb;
   int ok;
   char c;
   do{
    ok = 1;
    printf("Adja meg a piros szint(0-255 kozott)!\n--->");
    if(scanf("%d",&rgb.r) != 1 || rgb.r < 0 || rgb.r > 255){
        ok = 0;
        printf("Hibas ertek!\n");

        while((c=getchar()) != '\n');
    }


   }while(!ok);

   do{
    ok = 1;
    printf("Adja meg a zold szint(0-255 kozott)!\n--->");
    if(scanf("%d",&rgb.g) != 1 || rgb.g < 0 || rgb.g > 255){
        ok = 0;
        printf("Hibas ertek!\n");

        while((c=getchar()) != '\n');
    }


   }while(!ok);

   do{
    ok = 1;
    printf("Adja meg a kek szint(0-255 kozott)!\n--->");
    if(scanf("%d",&rgb.b) != 1 || rgb.b < 0 || rgb.b > 255){
        ok = 0;
        printf("Hibas ertek!\n");

        while((c=getchar()) != '\n');
    }


   }while(!ok);

   return rgb;
}
