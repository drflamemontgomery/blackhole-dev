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
 * \file image.h
 *
 * A blackhole library class for simple images
 */

#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include "imageBase.h"

namespace blackhole {
namespace graphics {

  /**
   *  \brief class for simple Image rendering using
   *         built on ImageBase
   */
  class Image : public ImageBase {
  private:
    float x;
    float y;
  public:

    /**
     *  \brief Constructor of Image
     *
     *  \param file The location of image file
     *  \param renderer The renderer of the Window
     *  \param x The x position of the Image
     *  \param y the y position of the Image
     */
    Image(const char* file, SDL_Renderer* renderer, float x = 0, float y = 0);
    ~Image();

    /**
     *  \brief Set the x position of the Image
     *
     *  \param x The x position you want the sprite to render on
     *
     *  \sa getX()
     *  \sa getY()
     *  \sa setY()
     */
    void setX(float x);

    /**
     *  \brief Set the y position of the Image
     *
     *  \param y the y position you want the sprite to render on
     *
     *  \sa getY()
     *  \sa getX()
     *  \sa setX()
     */
    void setY(float y);

    /**
     *  \brief Get the x position of the Image
     *
     *  \sa setX()
     *  \sa setY()
     *  \sa getY()
     */
    float getX();

    /**
     *  \brief Get the y position of the Image
     *
     *  \sa setY()
     *  \sa setX()
     *  \sa getX()
     */
    float getY();


    /**
     *  \brief Get a pointer to the destination rect used for positioning
     *         with the renderer
     *
     *  \return SDL_Rect* destRect of Image
     */
    SDL_Rect* getDestRect();
  };
}}

#endif
