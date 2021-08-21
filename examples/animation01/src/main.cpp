#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of Animation01
 *
 *         size:   width = 600px
 *                height = 600px
 *
 *
 *  renderFrame:   width = 600px
 *                height = 600px
 */
graphics::Window window(600, 600, "Animation01", {0, 0, 600, 600});

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

int frame_order[5] = {0, 1, 2, 3, 4};

/*
 *  Create Animation
 *
 *  SpriteSheet:  spritesheet
 *
 *  starting_frame:     0
 *  frames:             frame_order
 *  num_frames:         5
 * 
 *  seconds per frame:  0.2
 */
graphics::Animation animation(&spritesheet, 0, frame_order, 5, 0.2f);


int main(void) {

  // Add animation to render frame
  window.addImage(&animation);

  // Add camera to renderer
  window.addCamera(&cam1);

  // Start main loop running function game_main()
  // 60 frames per second
  window.setMainFunction(game_main);
  window.startMainLoop(60);
  while(!window.isClosed());
  
  return 0;
}

void game_main(void) {
  if(window.keyDown(SDL_SCANCODE_RIGHT)) {
    animation.setX(animation.getX() + 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_LEFT)) {
    animation.setX(animation.getX() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_UP)) {
    animation.setY(animation.getY() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_DOWN)) {
    animation.setY(animation.getY() + 128*window.getDeltaTime());
  }
}
