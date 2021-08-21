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
 * \file text.h
 *
 * A blackhole library class for rendering text
 */

#pragma once
#ifndef TEXT_H
#define TEXT_H

#include "imageBase.h"
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

namespace blackhole {
namespace graphics {

  /**
   *  \brief class for Text rendering
   *         built on ImageBase
   */
  class Text : public ImageBase {
  private:
    float x;
    float y;
  public:

    /**
     *  \brief Constructor of Text
     *
     *  \param file The location of the file
     *  \param text The text to display
     *  \param renderer The renderer of the Window
     *  \param size The size of the Text
     *  \param color The color of the Text
     *  \param x The x position of the Image
     *  \param y the y position of the Image
     */
    Text(const char* file, const char* text, SDL_Renderer* renderer, int size, SDL_Color color, float x = 0, float y = 0);
    ~Text();

    /**
     *  \brief Set the x position of the Text
     *
     *  \param x The x position you want the sprite to render on
     *
     *  \sa getX()
     *  \sa getY()
     *  \sa setY()
     */
    void setX(float x);

    /**
     *  \brief Set the y position of the Text
     *
     *  \param y the y position you want the sprite to render on
     *
     *  \sa getY()
     *  \sa getX()
     *  \sa setX()
     */
    void setY(float y);

    /**
     *  \brief Get the x position of the Text
     *
     *  \sa setX()
     *  \sa setY()
     *  \sa getY()
     */
    float getX();

    /**
     *  \brief Get the y position of the Text
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
     *  \return SDL_Rect* destRect of Text
     */
    SDL_Rect* getDestRect();
  };
}}

#endif
