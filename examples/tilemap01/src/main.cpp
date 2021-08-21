#include <iostream>
#include <blackhole/graphics.h>
#include <blackhole/file.h>

using namespace blackhole;

void game_main(void);


/*
 *  Create Window with name of Tilemap01
 *
 *         size:   width = 512px
 *                height = 512px
 *
 *
 *  renderFrame:   width = 512px
 *                height = 512px
 */
graphics::Window window(512, 512, "Tilemap01", {0, 0, 512, 512});

/*
 *  Create Camera
 *
 *  size:   width = 512px
 *         height = 512px
 *
 *   pos:  x = 0
 *         y = 0
 */
graphics::Camera cam1(window.getRenderer(), 512, 512, 0, 0);

/*
 *  Create Tilemap
 *
 *  file: tilemap01/assets/tilemap.tmx
 */

graphics::Tilemap tilemap((getLocalDir() + "/../assets/tilemap.tmx").c_str(),
			  window.getRenderer());

int main(void) {

  // Add tilemap Tile Layer 0 to renderer
  window.addImage(tilemap.getTileLayerImage(0));
  // Add camera to renderer
  window.addCamera(&cam1);

  // Start main loop running function game_main()
  // 60 frames per second
  window.setMainFunction(game_main);
  window.startMainLoop(60);
  while(!window.isClosed());
  
  return 0;
}

void game_main() {
}
