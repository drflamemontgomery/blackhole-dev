/*
  MIT License

  Copyright (c) 2021 Ashton Warner

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/**
 * \file tilemap.cpp
 *
 * A blackhole library class for turning tilemaps into images
 */

#include "graphics/tilemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


namespace blackhole::graphics {
  
  Tilemap::Tilemap(const char* file, SDL_Renderer* renderer) {
    map = new Tmx::Map();
    map->ParseFile(file);
    
    tileLayers = (Image**)malloc(map->GetNumTileLayers()*sizeof(Image*));
    SpriteSheet** tilesets;
    tilesets = (SpriteSheet**)malloc(map->GetNumTilesets()*sizeof(SpriteSheet*));

    for(int i = 0; i < map->GetNumTilesets(); i++) {
      const Tmx::Image* tilesetImage = map->GetTileset(i)->GetImage();
      std::string tilesetFilepath = map->GetFilepath() + tilesetImage->GetSource();
      tilesets[i] = new SpriteSheet(tilesetFilepath.c_str(),
				    renderer, 0, 0,
				    map->GetTileset(i)->GetColumns(),
				    ceil(map->GetTileset(i)->GetTileCount()/
					 map->GetTileset(i)->GetColumns())
				    );
    }


    
    for(int i = 0; i < map->GetNumTileLayers(); i++) {

      const Tmx::TileLayer* layer = map->GetTileLayer(i);
      SDL_Texture* texture = SDL_CreateTexture(renderer,
					       SDL_PIXELFORMAT_RGBA8888,
					       SDL_TEXTUREACCESS_TARGET,
					       map->GetWidth()*
					       map->GetTileWidth(),
					       map->GetHeight()*
					       map->GetTileHeight());
      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
      tileLayers[i] = new Image("/home/looking/c_testing/asdf.png", renderer, layer->GetX(), layer->GetY());
      

      SDL_Rect destrect = { 0, 0 , 0, 0 };

      SDL_SetRenderTarget(renderer, texture);
      
      for(int x = 0; x < layer->GetWidth(); x++) {
	for(int y = 0; y < layer->GetHeight(); y++) {
	  int tileset_id = layer->GetTileTilesetIndex(x, y);
	  if(tileset_id < 0) {
	    continue;
	  }
	  
	  tilesets[tileset_id]->setFrame(layer->GetTileId(x, y));
	  destrect = {
	    x*map->GetTileset(tileset_id)->GetTileWidth(),
	    y*map->GetTileset(tileset_id)->GetTileHeight(),
	    map->GetTileset(tileset_id)->GetTileWidth(),
	    map->GetTileset(tileset_id)->GetTileHeight()
	  };
	  SDL_RenderCopy(renderer, tilesets[tileset_id]->getTexture(),
			 tilesets[tileset_id]->getSrcRect(), &destrect);
	}
      }
      SDL_SetRenderTarget(renderer, NULL);
      printf("src_rect: %d\n", tileLayers[i]->getSrcRect() == NULL);
      
      tileLayers[i]->setTexture(texture);
      
    }
    

    free(tilesets);
    tilesets = 0;
  }

  Tilemap::~Tilemap() {
    free(tileLayers);
    tileLayers = 0;
  };

  
  Tmx::Map* Tilemap::getMap() {
    return map;
  }
  
  Image* Tilemap::getTileLayerImage(int layer) {
    return tileLayers[layer];
  }

  const Tmx::TileLayer* Tilemap::getTileLayer(int layer) {
    return map->GetTileLayer(layer);
  }
  
  const Tmx::ObjectGroup* Tilemap::getObjectGroup(int layer) {
    return map->GetObjectGroup(layer);
  }
}
