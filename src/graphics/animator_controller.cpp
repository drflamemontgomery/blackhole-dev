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
 * \file animator_controller.cpp
 *
 * A blackhole library class for controlling animation frames
 */

#include "graphics/animator_controller.h"

namespace blackhole::graphics {

  AnimatorController::AnimatorController(animation_holder* animations, long int array_length){
	this->array_length = array_length;
	this->animations = animations;
	this->currentAnimation = &animations[0].animation;
	this->currentAnimationName = animations[0].name;
	this->destRect.w = currentAnimation->getDestRect()->w;
	this->destRect.h = currentAnimation->getDestRect()->h;
  }

  AnimatorController::~AnimatorController() {
  }

  void AnimatorController::setAnimation(const char* animation) {
	if(animation == currentAnimationName) {
	  return;
	}
	for(int i = 0; i < array_length; i++) {
	  if(animations[i].name == animation) {
		currentAnimation = &animations[i].animation;
		currentAnimationName = animations[i].name;
		destRect.w = currentAnimation->getDestRect()->w;
		destRect.h = currentAnimation->getDestRect()->h;

		currentAnimation->resetAnimation();
	  }
	}
  }

  Animation* AnimatorController::getAnimation() {
	return currentAnimation;
  }

  const char* AnimatorController::getAnimationName() {
	return currentAnimationName;
  }

  void AnimatorController::setX(float x) {
    this->x = x;
  }

  void AnimatorController::setY(float y) {
	this->y = y;
  }

  float AnimatorController::getX() {
	return x;
  }

  float AnimatorController::getY() {
	return y;
  }

  void AnimatorController::addTime(float time) {
	currentAnimation->addTime(time);
  }

  SDL_Texture* AnimatorController::getTexture() {
	return currentAnimation->getTexture();
  }

  SDL_Rect* AnimatorController::getDestRect() {
	destRect.x = round(this->x);
	destRect.y = round(this->y);
	return &destRect;
  }

  SDL_Rect* AnimatorController::getSrcRect() {
	return currentAnimation->getSrcRect();
  }
  
}
