#include <SDL.h>
#include <stdbool.h>
#include <sstream>
#include <list>

const int width = 800;
const int height = 600;

struct Line{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Color{
    int r = 0;
    int g = 0;
    int b = 0;
};

struct Color set_RGB();
int maxLineCount();

int main(int argc, char ** argv)
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int MAX_LINE_COUNT = 0;
    std::list<Line> lines;

    struct Color rgb;
    rgb = set_RGB();

    MAX_LINE_COUNT = maxLineCount();
    printf("%d",MAX_LINE_COUNT);

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
            SDL_SetRenderDrawColor(renderer,30,40,50,SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);


            switch (event.type){

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button && HaveLine){
                        case SDL_BUTTON_LEFT:
                            x1 = event.motion.x;
                            y1 = event.motion.y;
                            x2 = event.motion.x;
                            y2 = event.motion.y;
                            drawing = true;

                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button){
                        case SDL_BUTTON_LEFT:
                            drawing = false;

                            Line line = { x1, y1, x2, y2 };
                            lines.push_back(line);
                            exit++;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (drawing && HaveLine){
                        x2 = event.motion.x;
                        y2 = event.motion.y;
                    }
                break;

        }

        if(exit == MAX_LINE_COUNT){
            HaveLine = false;
        }

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);


            for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i){
                Line line = *i;
                SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
            }



        SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE);
        if (drawing){
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
            SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

int maxLineCount(){
    int maxNum;
    printf("Adja meg mennyi legyen a vonalak max szama!(egesz szam)\n-->");
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
