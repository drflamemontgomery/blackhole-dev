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
 * \file spritesheet.h
 *
 * A blackhole library class for using spritesheet images
 */

#pragma once
#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "imageBase.h"

namespace blackhole {
namespace graphics {

  /**
   *  \brief A class for turning an image into frames built on ImageBase
   */
  class SpriteSheet : public ImageBase {
  private:
    float x;
    float y;

    int rows;
    int cols;
    int row_size;
    int col_size;

    int frames;
    int frame;
  
    SDL_Rect srcRect;
  
  public:
    /**
     *  \brief Constructor of the SpriteSheet
     *
     *  \param file The location of image file
     *  \param renderer The renderer of the Window
     *  \param x The x position of the Image
     *  \param y the y position of the Image
     *  \param cols The amount of columns in the SpriteSheet image
     *  \param rows The amount of rows in the SpriteSheet image
     */
    SpriteSheet(const char* file, SDL_Renderer* renderer, float x = 0, float y = 0, int cols = 1, int rows = 1);
    ~SpriteSheet();

    /**
     *  \brief Set the frame that the SpriteSheet is showing
     *
     *  \param frame The frame to show
     *
     *  \sa getFrame()
     */
    void setFrame(int frame);

    /**
     *  \brief Get the frame that the SpriteSheet is showing
     *
     *  \return number of frame shown eg. 0
     *
     *  \sa setFrame()
     */
    int getFrame();



    /**
     *  \brief Set the x position of the SpriteSheet
     *
     *  \param x The x position you want the sprite to render on
     *
     *  \sa getX()
     *  \sa getY()
     *  \sa setY()
     */
    void setX(float x);

    /**
     *  \brief Set the y position of the SpriteSheet
     *
     *  \param y The y position you want the sprite to render on
     *
     *  \sa getY()
     *  \sa getX()
     *  \sa setX()
     */
    void setY(float y);

    /**
     *  \brief Get the x position of the SpriteSheet
     *
     *  \sa setX()
     *  \sa setY()
     *  \sa getY()
     */
    float getX();

    /**
     *  \brief Get the y position of the SpriteSheet
     *
     *  \sa setY()
     *  \sa setY()
     *  \sa getX()
     */
    float getY();


    /**
     *  \brief Get a pointer to the destination rect used for positioning
     *         with the renderer
     *
     *  \return SDL_Rect* destRect of SpriteSheet
     */
    SDL_Rect* getDestRect();

    /**
     *  \brief Get a pointer to the source rect used for getting the frame
     *         of the SpriteSheet
     *
     *  \return SDL_Rect* frame rect of SpriteSheet
     */
    SDL_Rect* getSrcRect();
  };  
}}

#endif
