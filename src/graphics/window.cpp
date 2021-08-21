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
 * \file window.cpp
 *
 * A blackhole library class for creating SDL windows
 */

#include "graphics/window.h"
#include <SDL2/SDL_ttf.h>

namespace blackhole::graphics {

  bool compare_position(const ImageHolder& first, const ImageHolder& second);
  bool cam_sort(const CameraHolder& first, const CameraHolder& second);
  void renderThreadLoop(Window* window);
  //void eventThreadLoop(Window* window);

  time_t getTime();
  
  Window::Window(int width, int height, const char* title, SDL_Rect renderFrame) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->bg_color = { 0xFF, 0xFF, 0xFF, 0xFF };
    this->renderFrame = renderFrame;
	
    init();
	
  }

  Window::Window(int width, int height, const char* title, SDL_Rect renderFrame, Color bg) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->bg_color = bg;
    this->renderFrame = renderFrame;
    
    init();
  }
  

  Window::~Window() {
    this->running = false;
    this->renderThread.join();
    //this->eventThread.join();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
  
  bool Window::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("Failed to Initialize SDL2\n");
      return false;
    }
	
    this->window = SDL_CreateWindow(this->title,
				    SDL_WINDOWPOS_CENTERED,
				    SDL_WINDOWPOS_CENTERED,
				    this->width,
				    this->height,
				    0);
	
    if(!this->window) {
      printf("Failed to Initialize Window\n");
      return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer) {
      printf("Failed to Initialize Renderer\n");
      return false;
    }
    
    preRenderer = SDL_CreateTexture(renderer,
				    SDL_PIXELFORMAT_RGBX8888,
				    SDL_TEXTUREACCESS_TARGET,
				    renderFrame.w,
				    renderFrame.h);

    TTF_Init();
    
    return true;

	
  }

  // Rendering Function
  
  void Window::Render() {
    time_t time;
    while(running) {
      time = getTime();
      SDL_SetRenderDrawColor(renderer,
			     bg_color.red,
			     bg_color.green,
			     bg_color.blue,
			     bg_color.alpha);
      SDL_RenderClear(renderer);
      SDL_SetRenderTarget(renderer, preRenderer);
      SDL_RenderClear(renderer);

      for(auto image = renderQueue.begin(); image != renderQueue.end(); ++image) {
	SDL_Rect destRect = *image->image->getDestRect();
	for(auto cam = cameraQueue.begin(); cam != cameraQueue.end(); ++cam) {
	  SDL_Rect viewport = *cam->cam->getViewport();
	  
	  if((viewport.x < destRect.x || viewport.w > destRect.x) &&
	     (viewport.y < destRect.y || viewport.h > destRect.y)) {
	    SDL_RenderCopyEx(renderer, image->image->getTexture(), image->image->getSrcRect(), &destRect, 0, NULL, image->image->getRendererFlip());
	    break;
	  }
	  else if((viewport.x < destRect.x + destRect.w  ||
	     viewport.w > destRect.x + destRect.w ) &&
	     (viewport.y < destRect.y + destRect.h  ||
	      viewport.h > destRect.y + destRect.h)) {
	    SDL_RenderCopyEx(renderer, image->image->getTexture(), image->image->getSrcRect(), &destRect, 0, NULL, image->image->getRendererFlip());
	    break;
	  }
	}
	image->image->addTime(frameTime);
      }

      for(auto cam = cameraQueue.begin(); cam  != cameraQueue.end(); ++cam) {

	SDL_Rect destRect = *cam->cam->getViewport();
	SDL_Rect camDestRect = *cam->cam->getDestRect();
	SDL_QueryTexture(preRenderer, NULL, NULL, &destRect.w, &destRect.h);
	
	SDL_SetRenderTarget(renderer, cam->cam->getCamTexture());
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, preRenderer, NULL, &destRect, 0, NULL, cam->cam->getRendererFlip());

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, cam->cam->getCamTexture(), cam->cam->getSrcRect(), &camDestRect);
      }
      
      SDL_RenderPresent(renderer);

      handleEvents(difftime(getTime(), time)/1000.0f);
      
      while(difftime(getTime(), time) < 1000.0/fps) {
	SDL_Delay(1);
      }
      frameTime = difftime(getTime(), time)/1000;
    }
  }

  void Window::addCamera(Camera* cam) {
    CameraHolder camHolder = {
      cam
    };
    cameraQueue.push_back(camHolder);
    cameraQueue.sort(cam_sort);
  }
  
  void Window::addImage(ImageBase* image) {
    ImageHolder imageHolder = {
      image
    };
    renderQueue.push_back(imageHolder);
    renderQueue.sort(compare_position);
  }

  void Window::removeImage(ImageBase* image) {
    renderQueue.remove_if([image](const ImageHolder& value) {return value.image == image;});
  }

  void Window::removeCamera(Camera* cam) {
    cameraQueue.remove_if([cam](const CameraHolder& value) {return value.cam == cam;});
  }

  void Window::setFps(int fps) {
    this->fps = fps;
  }

  float Window::getTimeSinceLastFrame() {
    return frameTime;
  }
  
  
  int Window::getWidth() {
    return width;
  }

  int Window::getHeight() {
    return height;
  }

  SDL_Window* Window::getWindow() {
    return this->window;
  }
  
  SDL_Renderer* Window::getRenderer() {
    return this->renderer;
  }

  
  void Window::setRenderFrame(int width, int height) {
    this->renderFrame.w = this->width > width ? this->width : width;
    this->renderFrame.h = this->height > height ? this->height : height;

    SDL_DestroyTexture(preRenderer);
    preRenderer = SDL_CreateTexture(renderer,
				    SDL_PIXELFORMAT_RGBX8888,
				    SDL_TEXTUREACCESS_TARGET,
				    renderFrame.w,
				    renderFrame.h); 
  }
  

  void Window::setScale(floatXY scale) {
    this->scale = scale;
    SDL_RenderSetScale(renderer, this->scale.x, this->scale.y);
  }

  floatXY Window::getScale() {;
    return scale;
  }

  void Window::startMainLoop(int fps) {
    this->fps = fps;
    this->running = true;
    this->renderThread = std::thread(renderThreadLoop, this);
    //this->eventThread = std::thread(eventThreadLoop, this);
    time_t timer;
    while(!isClosed()) {
      timer = getTime();
      if(_main != NULL) {
	this->_main();
      }
      this->deltaTime = difftime(getTime(), timer)/1000.0;
    }
  }

  void Window::setMainFunction(void (*_main)()) {
    this->_main = _main;
  }

  void Window::setEventHandler(void (*_eventMain)(SDL_Event* event, float deltaTime)) {
    this->_eventMain = _eventMain;
  }
  
  void Window::handleEvents(float deltaTime) {
    //while(running) {
      SDL_Event event;
      while(SDL_PollEvent(&event) && running) {
	if(_eventMain != NULL) {
	  _eventMain(&event, deltaTime);
	}
	switch(event.type) {
	case SDL_WINDOWEVENT:
		  
	  switch(event.window.event) {
	  case SDL_WINDOWEVENT_CLOSE:
	    closed = true;
	    return;
	  }
		  
	  break;
	}
      }
      //}
  }


  bool Window::isClosed() {
    return closed;
  }


  double Window::getDeltaTime() {
    return deltaTime;
  }
  
  bool Window::keyDown(SDL_Scancode scancode) {
    return keyboard_state[scancode];
  }
  
  bool compare_position(const ImageHolder& first, const ImageHolder& second) {
    return(first.image->getLayer() < second.image->getLayer());
  }

  bool cam_sort(const CameraHolder& first, const CameraHolder& second) {
    return(first.cam->getLayer() < second.cam->getLayer());
  }

  void renderThreadLoop(Window* window) {
    window->Render();
  }

  // void eventThreadLoop(Window* window) {
  //   window->handleEvents();
  // }


  time_t getTime() {
    struct timeval time{};
    gettimeofday(&time, nullptr);
    time_t timer = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return timer;
  }
  
}
