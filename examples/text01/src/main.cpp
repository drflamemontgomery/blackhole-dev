#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of Text01
 *
 *         size:   width = 600px
 *                height = 600px
 *
 *
 *  renderFrame:   width = 600px
 *                height = 600px
 */
graphics::Window window(600, 600, "Text01", {0, 0, 600, 600});

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
 *  Create Text
 *
 *  filepath:  text01/assets/yoster.ttf 
 *
 *      text:  Hello World
 *     color:  0, 0, 0    Black
 *       pos:  x = 10
 *             y = 10
 *
 */
graphics::Text text((getLocalDir() + "/../assets/yoster.ttf").c_str(),
		    "Hello World",
		    window.getRenderer(),
		    20,
		    {0, 0, 0},
		    10, 10);

int main(void) {

  // Add text to render frame
  window.addImage(&text);

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
}
