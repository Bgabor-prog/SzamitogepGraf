#include "program.h"
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include "scene.h"

GLfloat ambient_light[] = { 0.5f, 0.5f, 0.5f, 0.0f };
GLfloat diffuse_light[] = { 0.5f, 0.5f, 0.0, 0.0f };
GLfloat specular_light[] = { 0.5f, 0.5f, 0.5f, 0.2f };
GLfloat position[] = { 0.0f, 0.0f, 3.0f, 1.0f };

void init_Program(Program* Program, int width, int height)
{
    int error_code;
    int inited_loaders;

    Program->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    Program->window = SDL_CreateWindow("beadando",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height,SDL_WINDOW_OPENGL);
    if (Program->window == NULL) {
        printf("Unable to create the Programlication window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    Program->gl_context = SDL_GL_CreateContext(Program->window);
    if (Program->gl_context == NULL) {
        printf("Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    CreateCamera(&(Program->camera));
    CreateScene(&(Program->scene));

    Program->is_running = true;
}


void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glPopMatrix();
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-.08, .08,-.06, .06,.1, 10);
}

void HandlingProgramEvents(Program* Program)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                Program->is_running = false;
                break;
            case SDL_SCANCODE_W:
                SetCameraSpeed(&(Program->camera), 2);
                break;
            case SDL_SCANCODE_S:
                SetCameraSpeed(&(Program->camera), -2);
                break;
            case SDL_SCANCODE_A:
                SetCameraSideSpeed(&(Program->camera), 1.5);
                break;
            case SDL_SCANCODE_D:
                SetCameraSideSpeed(&(Program->camera), -1.5);
                break;
            case SDL_SCANCODE_SPACE:
                SetCameraLiftSpeed(&(Program->camera), 2);
                break;
            case SDL_SCANCODE_E:
                SetCameraLiftSpeed(&(Program->camera), -2);
                break;
            case SDL_SCANCODE_KP_PLUS:
                ambient_light[0] = ambient_light[1] = ambient_light[2] += 0.1;
                printf("+ lenyomva");
                break;
            case SDL_SCANCODE_KP_MINUS:
                ambient_light[0] = ambient_light[1] = ambient_light[2] -= 0.01;
                printf("- lenyomva");
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                SetCameraSpeed(&(Program->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                SetCameraSideSpeed(&(Program->camera), 0);
                break;
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_E:
                SetCameraLiftSpeed(&(Program->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                RotateCamera(&(Program->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            Program->is_running = false;
            break;
        default:
            break;
        }
    }
}


void UpdateProgram(Program* Program)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - Program->uptime;
    Program->uptime = current_time;

    UpdateCamera(&(Program->camera), elapsed_time);
    UpdateScene(&(Program->scene));
}

void RenderProgram(Program* Program)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    SetView(&(Program->camera));
    RenderScene(&(Program->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(Program->window);
}

void ExitFromProgram(Program* Program)
{
    if (Program->gl_context != NULL) {
        SDL_GL_DeleteContext(Program->gl_context);
    }

    if (Program->window != NULL) {
        SDL_DestroyWindow(Program->window);
    }

    SDL_Quit();
}
