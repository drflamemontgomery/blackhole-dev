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
 * \file spritesheet.cpp
 *
 * A blackhole library class for using spritesheet images
 */

#include "graphics/spritesheet.h"

namespace blackhole::graphics {
  SpriteSheet::SpriteSheet(const char* file, SDL_Renderer* renderer,
						   float x,float y,
						   int cols, int rows
						   ) {
	init(file, renderer);
	this->x = x;
	this->y = y;
	
	this->rows = rows;
	this->cols = cols;

	SDL_QueryTexture(texture, NULL, NULL, &col_size, &row_size);
	
	this->row_size /= rows;
	this->col_size /= cols;

	this->frames = rows*cols;

	this->destRect.w = col_size;
	this->destRect.h = row_size;
	this->srcRect = {0, 0, col_size, row_size};
  }

  SpriteSheet::~SpriteSheet() {
  }

  void SpriteSheet::setFrame(int frame) {
    frame = frame % frames < 0 ? frame + frames : frame % frames;
    this->frame = frame;
    this->srcRect = {
      frame%cols*col_size,
      (int)frame/cols*row_size,
      col_size,
      row_size
    };
  }

  int SpriteSheet::getFrame() {
	return frame;
  }
  
  
  void SpriteSheet::setX(float x) {
	this->x = x;
  }

  void SpriteSheet::setY(float y) {
	this->y = y;
  }

  float SpriteSheet::getX() {
    return x;
  }

  float SpriteSheet::getY() {
    return y;
  }

  SDL_Rect* SpriteSheet::getDestRect() {
	destRect.x = (int)x+0.5;
	destRect.y = (int)y+0.5;
	return &destRect;
  }
  
  SDL_Rect* SpriteSheet::getSrcRect() {
	return &srcRect;
  }
}
