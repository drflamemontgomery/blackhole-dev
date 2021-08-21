#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of Animation02
 *
 *         size:   width = 600px
 *                height = 600px
 *
 *
 *  renderFrame:   width = 600px
 *                height = 600px
 */
graphics::Window window(600, 600, "Animation02", {0, 0, 600, 600});

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
graphics::Animation animation01(&spritesheet, 0, frame_order, 5, 0.2f);

int frame_order2[5] = {4, 3, 2, 1, 0};

/*
 *  Create Animation
 *
 *  SpriteSheet:  spritesheet
 *
 *  starting_frame:     0
 *  frames:             frame_order2
 *  num_frames:         5
 * 
 *  seconds per frame:  0.2
 */
graphics::Animation animation02(&spritesheet, 0, frame_order2, 5, 0.2f);

graphics::animation_holder anim_array[2] = {
  {"animation01", animation01},
  {"animation02", animation02}
};


/*
 *  Create Animation Controller
 *
 *  animations:  anim_array
 *   array_len:  2
 */
graphics::AnimatorController anim_controller(anim_array, 2);

int main(void) {

  // Add animation to render frame
  window.addImage(&anim_controller);

  // Add camera to renderer
  window.addCamera(&cam1);

  // Start main loop running function game_main()
  // 60 frames per second
  window.setMainFunction(game_main);
  window.startMainLoop(60);
  while(!window.isClosed());
  
  return 0;
}

bool one_pressed  = false;
bool two_pressed = false;

void game_main(void) {
  if(window.keyDown(SDL_SCANCODE_RIGHT)) {
    anim_controller.setX(anim_controller.getX() + 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_LEFT)) {
    anim_controller.setX(anim_controller.getX() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_UP)) {
    anim_controller.setY(anim_controller.getY() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_DOWN)) {
    anim_controller.setY(anim_controller.getY() + 128*window.getDeltaTime());
  }




  if(window.keyDown(SDL_SCANCODE_1) && !one_pressed) {
    anim_controller.setAnimation("animation01");
    one_pressed = true;
  }
  else if(!window.keyDown(SDL_SCANCODE_1) && one_pressed) {
    one_pressed = false;
  }

  if(window.keyDown(SDL_SCANCODE_2) && !two_pressed) {
    anim_controller.setAnimation("animation02");
    two_pressed = true;
  }
  else if(!window.keyDown(SDL_SCANCODE_2) && two_pressed) {
    two_pressed = false;
  }
}
