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
 * \file camera.h
 *
 * A blackhole library class for viewing images
 */

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "imageBase.h"
#include "imageHolder.h"
#include <iostream>
#include <list>

namespace blackhole {
namespace graphics {

  /**
   *  \brief The class for viewing classes built on ImageBase
   */
  class Camera : public ImageBase {
  private:
    float x;
    float y;
    SDL_Rect viewport;
    std::list<ImageHolder> renderQueue;

    SDL_Renderer* renderer;
  public:
    /**
     *  \brief The Constructor of Camera
     *
     *  \param renderer The renderer of the Window
     *  \param w The width of the Camera
     *  \param h The height of the Camera
     *  \param x The x position of the Camera
     *  \param y the y position of the Camera
     */
    Camera(SDL_Renderer* renderer, int w, int h, float x = 0, float y = 0);
    ~Camera();


    /**
     *  \brief adjusts time for the images when Camera is used as 
     *         an image collator
     *
     *  \param time The amount of time passed in the frame
     */
    void addTime(float time);
    
    /**
     *  \brief Set the x position of the Camera
     *
     *  \param x The x position you want the Camera to view
     *
     *  \sa setY()
     */
    void setX(float x);

    /**
     *  \brief Set the y position of the Camera
     *
     *  \param y The y position you want the Camera to view
     *
     *  \sa setX()
     */
    void setY(float y);


    /**
     *  \brief Add an ImageBase based class to the Camera for collating.
     *         Use for ImageBase only this Camera can see
     *
     *  \param image pointer to the ImageBase for rendering
     *
     *  \sa removeImage()
     */
    void addImage(ImageBase* image);

    /**
     *  \brief Remove an ImageBase based class from the camera
     *
     *  \param image pointer to the ImageBase you want to remove
     *
     *  \sa addImage()
     */
    void removeImage(ImageBase* image);



    /**
     *  \brief Get the size of the Camera viewport
     *
     *  \return SDL_Rect* containing the size of the viewport
     */
    SDL_Rect* getViewport();

    /**
     *  \brief Get the texture of the Camera for copying renderer
     *
     *  \return SDL_Texture* to be erased and copied over for the main renderer
     */
    SDL_Texture* getCamTexture();

    /**
     *  \brief Get the texture of the Camera with its images
     *
     *  \return SDL_Texture* to be copied to the main renderer
     */
    SDL_Texture* getTexture();
  };
}}

#endif
