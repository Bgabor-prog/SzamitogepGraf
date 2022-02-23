#include <SDL.h>
#include <stdbool.h>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>

const int width = 800;
const int height = 600;
const int lower = 0;
const int upper = 255;

struct Circle{
    int x;
    int y;
    int radius = 30;
    int r,g,b;
};

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius,SDL_Color color);
int setMaxCircleCount();
int setRandomRgb(int lower, int upper);

int main(int argc, char ** argv)
{
    //variables
    int mouseX;
    int mouseY;
    int MAX_CIRCLE_COUNT;
    int lineX1,lineX2,lineY1,lineY2;

    Circle newCircle;
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

    int circleCount = 0;
    bool HaveCircle = true;
    bool drawNewCircle = false;
    bool quit = false;
    bool RightButtonDown = false;
    while(!quit){
        SDL_Delay(1000/60);
        SDL_PollEvent(&event);

        if(SDL_QUIT == event.type){
            quit = true;
        }

        SDL_SetRenderDrawColor(renderer,110,110,110,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        //Setting the circle x,y coord = with the mouse pos x,y and setting the rgb colors
        switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            if(SDL_BUTTON_LEFT == event.button.button && HaveCircle){
                newCircle.x = event.motion.x;
                newCircle.y = event.motion.y;
                drawNewCircle = true;
                newCircle.r = setRandomRgb(lower,upper);
                newCircle.g = setRandomRgb(lower,upper);
                newCircle.b = setRandomRgb(lower,upper);
            }
        break;

        //if drawing finished count the circle number then set the drawing false
        case SDL_MOUSEBUTTONUP:
            if(SDL_BUTTON_LEFT == event.button.button && HaveCircle){
                drawNewCircle = false;
                circleCount++;
                circles.push_back(newCircle);
            }
        }

        //checking the mouth x,y pos then move the circle x,y coord towards the mouse x,y pos
        switch(event.type){
        case SDL_MOUSEMOTION:
            {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            printf("Mouse:%d, %d\n",mouseX,mouseY);
            }
        break;

        case SDL_MOUSEBUTTONDOWN:
        switch(event.button.button){
            case SDL_BUTTON_RIGHT:
                for(auto & circle : circles){
                    if(mouseX < circle.x){
                        printf("Left move!\n");
                        circle.x-=10;
                    }else if(mouseX > circle.x){
                        printf("Right move!\n");
                        circle.x+=10;
                    }
                    if(mouseY > circle.y){
                        printf("Down move!\n");
                        circle.y+=10;

                    }else if(mouseY < circle.y){
                        printf("Top move!\n");
                        circle.y-=10;
                    }
                }
            }
        }

        if(circleCount == MAX_CIRCLE_COUNT){
            HaveCircle = false;
        }

        //redraw the circles
        for(auto & circle : circles){
            color.r = circle.r;
            color.g = circle.g;
            color.b = circle.b;
            SDL_RenderDrawCircle(renderer,circle.x,circle.y,30,color);
            SDL_RenderFillCircle(renderer,circle.x,circle.y,30,color);

            //Set X sign in to the circle if the mouse on top of the circle
            if(mouseY < circle.y+30 && mouseX < circle.x+30 && mouseX > circle.x-30 && mouseY > circle.y-30){
                lineX1 = circle.x-5;
                lineY1 = circle.y+5;
                lineX2 = circle.x+5;
                lineY2 = circle.y-5;
                SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, lineX1, lineY1, lineX2, lineY2);
                SDL_RenderDrawLine(renderer, lineX1, lineY2, lineX2, lineY1);
            }
        }

        //draw the circles
        if(drawNewCircle){
            color.r = newCircle.r;
            color.g = newCircle.g;
            color.b = newCircle.b;
            SDL_RenderDrawCircle(renderer,newCircle.x,newCircle.y,30,color);
            SDL_RenderFillCircle(renderer,newCircle.x,newCircle.y,30,color);
            printf("Circle pos:%d,%d\n",newCircle.x,newCircle.y);
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

