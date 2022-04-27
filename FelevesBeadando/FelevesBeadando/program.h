#ifndef PROGRAM_H
#define PROGRAM_H

#include "camera.h"
#include "scene.h"
#include <SDL2\SDL.h>
#include <stdbool.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct Program
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
} Program;


void init_Program(Program* Program, int width, int height);

void init_opengl();

void reshape(GLsizei width, GLsizei height);

void HandlingProgramEvents(Program* Program);

void UpdateProgram(Program* Program);

void PressedUpdate(Program* Program);

void RenderProgram(Program* Program);

void ExitFromProgram(Program* Program);

void render_helppanel(GLuint texture);

void show_panel(bool* helppanel_show);

#endif // PROGRAM_H
