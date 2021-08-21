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
 * \file window.h
 *
 * A blackhole library class for creating SDL windows
 */

#pragma once
#ifndef WINDOW_H
#define WINDOW_H


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <stdio.h>
#include <sys/time.h>
#include <thread>
#include <ctime>
#include <memory>
#include "color.h"
#include "imageHolder.h"
#include "cameraHolder.h"

namespace blackhole {
namespace graphics {

  /**
   *  \brief A struct for 2d positions
   */
  struct floatXY {
    float x;  /**< x position */
    float y;  /**< y position */
  };


  /**
   *  \brief A class for handling rendering, events, and main functions
   */
  class Window {
  private:
    bool init();
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* preRenderer;

    SDL_Rect renderFrame;
  
    Color bg_color;
    int width;
    int height;
    const char* title;

    floatXY scale;
    int fps;

    float frameTime;
  
    std::list<CameraHolder> cameraQueue;
    std::list<ImageHolder> renderQueue;
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    double deltaTime = 0;
  
    std::thread renderThread;
    //std::thread eventThread;
    bool running = false;
    bool closed = false;
    void (*_main)();
    void (*_eventMain)(SDL_Event* event, float deltaTime);
  
  public:

    /**
     *  \brief Constructor of Window with standard color
     *
     *  \param width Width of the Window
     *  \param height Height of the Window
     *  \param title Name of the Window
     *  \param renderFrame Rectangle of Renderable positions
     */
    Window(int width, int height, const char* title, SDL_Rect renderFrame);

    /**
     *  \brief Constructor of Window with custom color
     *
     *  \param width Width of the Window
     *  \param height Height of the Window
     *  \param title Name of the Window
     *  \param renderFrame Rectangle of renderable positions
     *  \param bg Color of the Window background
     */
    Window(int width, int height, const char* title, SDL_Rect renderFrame, Color bg);
    ~Window();


    /**
     *  \brief Function for rendering all classes built on ImageBase
     */
    void Render();


    /**
     *  \brief Function for adding a Camera to watch
     *
     *  \param cam Pointer to the Camera to add
     *
     *  \sa removeCamera()
     */
    void addCamera(Camera* cam);

    /**
     *  \brief Function for removing a Camera
     *
     *  \param cam Pointer to the Camera to remove
     *
     *  \sa addCamera()
     */
    void removeCamera(Camera* cam);



    /**
     *  \brief Function for adding an ImageBase for rendering
     *
     *  \param image Pointer to the ImageBase to add
     *
     *  \sa removeImage()
     */
    void addImage(ImageBase* image);

    /**
     *  \brief Function for removing an ImageBase
     *
     *  \param image Pointer to the ImageBase to remove
     *
     *  \sa addImage()
     */
    void removeImage(ImageBase* image);



    /**
     *  \brief Get the width of the WIndow
     *
     *  return width of window eg. 600 px
     *
     *  \sa getHeight()
     */
    int getWidth();

    /**
     *  \brief Get the height of the WIndow
     *
     *  return height of window eg. 600 px
     *
     *  \sa getWidth()
     */
    int getHeight();



    /**
     *  \brief Get the SDL declaration of the window
     *
     *  \return pointer of SDL_Window
     */
    SDL_Window* getWindow();

    /**
     *  \brief Get the SDL declaration of the renderer
     *
     *  \return pointer of SDL_Renderer
     */
    SDL_Renderer* getRenderer();


    /**
     *  \brief Set the size of the viewport that can be rendered on
     *
     *  \param width Width of the viewport
     *  \param height Height of the viewport
     */
    void setRenderFrame(int width, int height);


    
    /**
     *  \brief Set the zoom scale of the window
     *
     *  \param scale {x, y} value of the scale
     *  \sa getScale()
     */
    void setScale(floatXY scale);

    /**
     *  \brief Get the zoom scale of the window
     *
     *  \return floatXY of the scale eg. {2, 2} `2x zoom`
     *
     *  \sa setScale()
     */
    floatXY getScale();


    /**
     *  \brief Start the window functions
     *
     *  \param fps Frames Per Second
     */
    void startMainLoop(int fps);

    /**
     *  \brief Set the main function
     *
     *  \param _main Main function declared by the user
     */
    void setMainFunction(void (*_main)());

    /**
     *  \brief Set the event handler
     *
     *  \param _eventMain Event handler function declared by the user
     */
    void setEventHandler(void (*_eventMain)(SDL_Event* event, float deltaTime));
    
    /**
     *  \brief Check if window is closed
     *
     *  \return true if closed. false if not closed
     */
    bool isClosed();



    /**
     *  \brief Get the time since the last frame
     *
     *  \return float of time eg. 0.0122f seconds
     */
    float getTimeSinceLastFrame();

    /**
     *  \brief Set fps for the renderer
     *
     *  \param fps Frames Per Second
     */
    void setFps(int fps);


    /**
     *  \brief Get the time since last main function call
     *
     *  \return double of delta time
     */
    double getDeltaTime();

    /**
     *  \brief Check if key X is pressed
     *
     *  \param scancode SDL_Scancode of the key
     *
     *  \return true if key is pressed
     */
    bool keyDown(SDL_Scancode scancode);



    /**
     *  \brief Handle SDL Events. Used in the event thread
     *
     *  \param deltaTime time passed in the frame
     */
    void handleEvents(float deltaTime);
  };
}}


#endif
