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
 * \file animation.cpp
 *
 * A blackhole library class for creating animation frames
 */

#include "graphics/animation.h"

namespace blackhole::graphics {

  Animation::Animation(SpriteSheet* images, int frame, int* frames, int num_frames, float speed)
  {
    this->images = images;
    images->setFrame(frame);
    this->frames = frames;
    this->num_frames = num_frames;
    printf("%d\n", num_frames);
    this->speed = speed;
  }

  Animation::~Animation() {

  }

  void Animation::setX(float x) {
    images->setX(x);
  }

  void Animation::setY(float y) {
    images->setY(y);
  }
  
  float Animation::getX() {
    return images->getX();
  }

  float Animation::getY() {
    return images->getY();
  }

  void  Animation::setFrame(int frame) {
    images->setFrame(frame);
  }

  int Animation::getFrame() {
    return images->getFrame();
  }

  void Animation::resetAnimation() {
    this->time = 0;
  }
  
  void Animation::addTime(float time) {
    this->time += time;
    images->setFrame(frames[(int)(this->time / speed) % num_frames]);
  }

  SpriteSheet* Animation::getSpriteSheet() {
    return images;
  }

  SDL_Texture* Animation::getTexture() {
    return images->getTexture();
  }
  
  SDL_Rect* Animation::getSrcRect() {
    return images->getSrcRect();
  }

  SDL_Rect* Animation::getDestRect() {
    return images->getDestRect();
  }

}
