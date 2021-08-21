#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of Image01
 *
 *         size:   width = 600px
 *                height = 600px
 *
 *
 *  renderFrame:   width = 600px
 *                height = 600px
 */
graphics::Window window(600, 600, "Image01", {0, 0, 600, 600});

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
 *  Create Image
 *
 *  filepath:  image01/assets/img01.png 
 *
 *       pos:  x = 284    Center
 *             y = 284    Center
 *
 */
graphics::Image image((getLocalDir() + "/../assets/img01.png").c_str(),
			    window.getRenderer(), 284, 284);

int main(void) {

  // Add image to render frame
  window.addImage(&image);

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
    image.setX(image.getX() + 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_LEFT)) {
    image.setX(image.getX() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_UP)) {
    image.setY(image.getY() - 128*window.getDeltaTime());
  }

  if(window.keyDown(SDL_SCANCODE_DOWN)) {
    image.setY(image.getY() + 128*window.getDeltaTime());
  }
}
