#include <SDL2/SDL.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  const char *_WindowName = "First";
  int _WindowWidth = 800;
  int _WindowHeight = 600;

  SDL_Window *_window;
  SDL_Surface *_winSurface;
  SDL_Surface *_imageSurface;
  SDL_Renderer *_renderer;

  const char *image1 = "./pictures/sample1.bmp";
  const char *image2 = "./pictures/480-360-sample.bmp";

  bool _isRunning = true;

  bool init();
  bool loadBmp(const char *filepath);
  void kill();
  void mainLoop();
  void draw();
};
