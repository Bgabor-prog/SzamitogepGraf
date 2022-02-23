#include <SDL.h>
#include <stdbool.h>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>

const int width = 800;
const int height = 600;

struct Circle{
    int x;
    int y;
    int radius;
};

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color);
int setMaxCircleCount();
int setRandomRgb(int lower, int upper);

int main(int argc, char ** argv)
{
    int mouseX;
    int mouseY;
    int lower = 0;
    int upper = 255;
    int MAX_CIRCLE_COUNT;
    Circle circle;
    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    std::vector<Circle> circles;

    MAX_CIRCLE_COUNT = setMaxCircleCount();
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("KorRajzolas", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    SDL_Event event;

    int exit = 0;
    bool HaveCircle = true;
    bool drawing = false;
    bool quit = false;
    while(!quit){
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch(event.type){
        case SDL_QUIT:
            quit = true;
            break;

        }

        SDL_SetRenderDrawColor(renderer,110,110,110,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button && HaveCircle){
            case SDL_BUTTON_LEFT:
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                drawing = true;
                color.r = setRandomRgb(lower,upper);
                color.g = setRandomRgb(lower,upper);
                color.b = setRandomRgb(lower,upper);
            break;
            }
        break;

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button && HaveCircle){
            case SDL_BUTTON_LEFT:
                drawing = false;
                exit++;
            }
        }

        switch(event.type){

        case SDL_MOUSEMOTION:
            {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            printf("Mouse loc:%d,%d\n",mouseX,mouseY);
            }
        break;

        case SDL_MOUSEBUTTONDOWN:
        switch(event.button.button){
            case SDL_BUTTON_RIGHT:
                if(mouseX < circle.x){
                    printf("Left move!\n");
                   circle.x--;

                }else if(mouseX > circle.x){
                   circle.x++;
                }
                if(mouseY > circle.y){
                    circle.y++;

                }else if(mouseY < circle.y){
                    circle.y--;

                }
            }

        }

        if(exit == MAX_CIRCLE_COUNT){
            HaveCircle = false;
        }

        circles.push_back({circle.x,circle.y,circle.radius});
        for(auto & circle : circles){
            SDL_RenderDrawCircle(renderer,circle.x,circle.y,30,color);
            SDL_RenderFillCircle(renderer,circle.x,circle.y,30,color);
        }

        if(drawing){
            SDL_RenderDrawCircle(renderer,circle.x,circle.y,30,color);
            SDL_RenderFillCircle(renderer,circle.x,circle.y,30,color);
            printf("Circle pos:%d,%d\n",circle.x,circle.y);
        }

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

return 0;
}

int setRandomRgb(int lower, int upper){
   return lower + rand() / (RAND_MAX / (upper - lower + 1) + 1);
}



int setMaxCircleCount(){
    int maxNum;
    printf("Adja meg a kirajzolni kivant korok szamat!\n--->");
    scanf("%d",&maxNum);

return maxNum;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color){

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color){

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

