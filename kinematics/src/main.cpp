#include "./include/main.hpp"
#include <math.h>
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

int main (int argc, char* argv[])
{
    // ----- Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL could not initialize\n");
        return 1;
    }

    // ----- Create window
    SDL_Window* window = SDL_CreateWindow("Kinematics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error creating window.\n");
        return 2;
    }

    // ----- SDL OpenGL settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // ----- SDL OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // ----- SDL v-sync
    SDL_GL_SetSwapInterval(1);

    // ----- GLEW
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    double angle = 0;
    Arm arm1(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 100, 0);
    Arm arm2(arm1.GetEndX(), arm1.GetEndY(), 100, 1.3);
    Arm arm3(arm2.GetEndX(), arm2.GetEndY(), 120, 1.3);
    arm2.parent = &arm1;
    arm3.parent = &arm2;

    uint8_t armColor[4] = {26, 150, 255, 255};
    // ----- Game loop
    bool quit = false;
    while (quit == false)
    {
        SDL_Event windowEvent;
        while (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }

        /*
            do drawing here
        */
        arm1.Render(renderer, armColor);
        arm2.Render(renderer, armColor);
        arm3.Render(renderer, armColor);
        arm1.angle = sin(angle)*1.2;
        arm2.angle = cos(angle * 0.9) * 0.92;
        arm3.angle = sin(angle * 1.1) * 1.34;
        arm2.x = arm1.GetEndX();
        arm2.y = arm1.GetEndY();
        arm3.x = arm2.GetEndX();
        arm3.y = arm2.GetEndY();
        angle += 0.0005;
        SDL_GL_SwapWindow(window);
    }

    // ----- Clean up
    SDL_GL_DeleteContext(glContext);

    return 0;
}