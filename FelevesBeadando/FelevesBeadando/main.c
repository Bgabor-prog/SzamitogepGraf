#include "program.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    Program Program;

    init_Program(&Program, 1280, 800);
    while (Program.is_running) {
        HandlingProgramEvents(&Program);
        UpdateProgram(&Program);
        RenderProgram(&Program);
    }
    ExitFromProgram(&Program);

    return 0;
}
