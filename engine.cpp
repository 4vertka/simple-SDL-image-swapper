#include "engine.hpp"
#include <SDL2/SDL_render.h>

// Constructor and Destructor
Game::Game()
    : _isRunning(true), _window(nullptr), _winSurface(nullptr),
      _imageSurface(nullptr) {}

Game::~Game() { kill(); }

void Game::draw() {
  if (!_winSurface || !_imageSurface)
    return;

  SDL_FillRect(_winSurface, NULL,
               SDL_MapRGB(_winSurface->format, 255, 90, 120));

  SDL_Rect dest;
  dest.x = 100;
  dest.y = 50;
  dest.w = 640;
  dest.h = 427;

  SDL_BlitSurface(_imageSurface, nullptr, _winSurface, &dest);
  SDL_UpdateWindowSurface(_window);
}

void Game::run() {
  if (!init())
    return;

  if (!loadBmp(image1)) {
    kill();
    return;
  }

  draw();
  mainLoop();
}

void Game::mainLoop() {
  SDL_Event event;
  while (_isRunning) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        _isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_DOWN) {
          if (loadBmp(image2)) {
            draw();
          }
        }
        if (event.key.keysym.sym == SDLK_UP) {
          if (loadBmp(image1)) {
            draw();
          }
        }
        break;
      }
    }
  }
}

bool Game::loadBmp(const char *filepath) {
  if (!filepath)
    return false;

  SDL_Surface *tmp1 = SDL_LoadBMP(filepath);
  if (!tmp1) {
    std::cout << "Error loading image: " << SDL_GetError() << std::endl;
    return false;
  }

  // Free existing surface if it exists
  if (_imageSurface) {
    SDL_FreeSurface(_imageSurface);
  }

  // Convert surface to match window surface format
  _imageSurface = SDL_ConvertSurface(tmp1, _winSurface->format, 0);

  // Always free the temporary surface
  SDL_FreeSurface(tmp1);

  if (!_imageSurface) {
    std::cout << "Error converting image: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing: " << SDL_GetError() << std::endl;
    return false;
  }

  _window = SDL_CreateWindow(_WindowName, 100, 100, _WindowWidth, _WindowHeight,
                             SDL_WINDOW_SHOWN);
  if (!_window) {
    std::cerr << "Failed to create a window: " << SDL_GetError() << std::endl;
    return false;
  }

  _winSurface = SDL_GetWindowSurface(_window);
  if (!_winSurface) {
    std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Game::kill() {
  if (_imageSurface) {
    SDL_FreeSurface(_imageSurface);
    _imageSurface = nullptr;
  }

  if (_window) {
    SDL_DestroyWindow(_window);
    _window = nullptr;
  }

  SDL_Quit();
}
