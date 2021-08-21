#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of SpriteSheet01
 *
 *         size:   width = 600px
 *                height = 600px
 *
 *
 *  renderFrame:   width = 600px
 *                height = 600px
 */
graphics::Window window(600, 600, "SpriteSheet01", {0, 0, 600, 600});

/*
 *  Create Camera
 *
 *  size:   width = 600px
 *         height = 600px
 *
 *   pos:  x = 0
 *         y = 0
 */
graphics::Camera cam1(window.getRenderer(), 600, 600, 0, 0);

/*
 *  Create SpriteSheet
 *
 *  filepath:  spritesheet01/assets/spritesheet01.png 
 *
 *       pos:  x = 292    Center
 *             y = 292    Center
 *
 *   columns:  5
 *      rows:  1
 *
 */
graphics::SpriteSheet spritesheet((getLocalDir() +
				   "/../assets/spritesheet01.png").c_str(),
				  window.getRenderer(), 292, 292, 5, 1);

int main(void) {

  // Add spritesheet to render frame
  window.addImage(&spritesheet);

  // Add camera to renderer
  window.addCamera(&cam1);

  // Start main loop running function game_main()
  // 60 frames per second
  window.setMainFunction(game_main);
  window.startMainLoop(60);
  while(!window.isClosed());
  
  return 0;
}

bool plus_pressed  = false;
bool minus_pressed = false;

void game_main(void) {
  if(window.keyDown(SDL_SCANCODE_RIGHT)) {
    spritesheet.setX(spritesheet.getX() + 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_LEFT)) {
    spritesheet.setX(spritesheet.getX() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_UP)) {
    spritesheet.setY(spritesheet.getY() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_DOWN)) {
    spritesheet.setY(spritesheet.getY() + 128*window.getDeltaTime());
  }




  
  if(window.keyDown(SDL_SCANCODE_EQUALS) && !plus_pressed) {
    spritesheet.setFrame(spritesheet.getFrame() + 1);
    plus_pressed = true;
  }
  else if(!window.keyDown(SDL_SCANCODE_EQUALS) && plus_pressed) {
    plus_pressed = false;
  }

  if(window.keyDown(SDL_SCANCODE_MINUS) && !minus_pressed) {
    spritesheet.setFrame(spritesheet.getFrame() - 1);
    minus_pressed = true;
  }
  else if(!window.keyDown(SDL_SCANCODE_MINUS) && minus_pressed) {
    minus_pressed = false;
  }
}
