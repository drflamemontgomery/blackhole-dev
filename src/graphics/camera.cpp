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
 * \file camera.cpp
 *
 * A blackhole library class for viewing images
 */

#include "graphics/camera.h"

namespace blackhole::graphics {

  extern bool compare_position(const ImageHolder& first, const ImageHolder& second);
  
  Camera::Camera(SDL_Renderer* renderer, int w, int h, float x, float y) {
    this->renderer = renderer;
    this->texture = SDL_CreateTexture(renderer,
				      SDL_PIXELFORMAT_RGBX8888,
				      SDL_TEXTUREACCESS_TARGET,
				      w,
				      h);
    this->x = x;
    this->y = y;

    destRect = {(int)x, (int)y, w, h};
    viewport = {0, 0, w, h};
  }

  Camera::~Camera() {
    SDL_DestroyTexture(texture);
  }

  void Camera::setX(float x) {
    this->x = x;
  }

  void Camera::setY(float y) {
    this->y = y;
  }

  void Camera::addImage(ImageBase* image) {
    ImageHolder imageHolder = {
      image
    };
    renderQueue.push_back(imageHolder);
    renderQueue.sort(compare_position);
  }

  void Camera::removeImage(ImageBase* image) {
    renderQueue.remove_if([image](const ImageHolder& value) {return value.image == image;});
  }


  
  SDL_Rect* Camera::getViewport() {
    return &viewport;
  }
  
  SDL_Texture* Camera::getTexture() {
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderClear(renderer);

    for(auto image = renderQueue.begin(); image != renderQueue.end(); ++image) {
      SDL_RenderCopyEx(renderer, image->image->getTexture(), image->image->getSrcRect(),image->image->getDestRect(), 0, NULL, image->image->getRendererFlip());
    }
    
    
    SDL_SetRenderTarget(renderer, NULL);
    return texture;
  }

  SDL_Texture* Camera::getCamTexture() {
    return texture;
  }

  void Camera::addTime(float time) {
    for(auto image = renderQueue.begin(); image != renderQueue.end(); ++image) {
      image->image->addTime(time);
    }
  }
}
