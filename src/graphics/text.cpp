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
 * \file text.cpp
 *
 * A blackhole library class for displaying text
 */

#include "graphics/text.h"

namespace blackhole::graphics {
  Text::Text(const char* file, const char* text, SDL_Renderer* renderer, int size, SDL_Color color, float x, float y) {
    TTF_Font* font = TTF_OpenFont(file, size);

    if(font == NULL) {
      fprintf(stderr, "Failed to open font %s\n", file);
      return;
    }
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    SDL_QueryTexture(this->texture, NULL, NULL, &destRect.w, &destRect.h);

    this->x = x;
    this->y = y;
  }

  Text::~Text() {
    SDL_DestroyTexture(texture);
  }

  void Text::setX(float x) {
    this->x = x;
  }

  void Text::setY(float y) {
    this->y = y;
  }
  
  float Text::getX() {
    return x;
  }

  float Text::getY() {
    return y;
  }


  SDL_Rect* Text::getDestRect() {
    destRect.x = round(x);
    destRect.y = round(y);
    return &destRect;
  }
}
