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
 * \file animation.h
 *
 * A blackhole library class for creating animation frames
 */

#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include "spritesheet.h"
#include "imageBase.h"
#include <iostream>
#include <stdio.h>

namespace blackhole {
namespace graphics {

  /**
   *  \brief The class for looping through SpriteSheet frames
   *         built on ImageBase
   */
  class Animation : public ImageBase {
  private:
    SpriteSheet* images;
    int* frames;
    int num_frames;
    float speed;
    float time = 0;
  public:

    /**
     *  \brief Constructor of Animation.
     *
     *  \param images The pointer to the SpriteSheet used for frames
     *  \param frame The starting frame
     *  \param frames The order of frames for the animation eg. 0, 2, 1, 2
     *  \param num_frames The number of frames in the animation eg. 4
     *  \param speed The amount of time between frames
     */
    Animation(SpriteSheet* images, int frame, int* frames, int num_frames, float speed = 1);
    ~Animation();

    /**
     *  \brief Set the x position of the Animation SpriteSheet
     *
     *  \param x The x position you want the sprite to render on
     *
     *  \sa getX()
     *  \sa getY()
     *  \sa setY()
     */
    void setX(float x);

    /**
     *  \brief Set the y position of the Animation SpriteSheet
     *
     *  \param y the y position you want the sprite to render on
     *
     *  \sa getY()
     *  \sa getX()
     *  \sa setX()
     */
    void setY(float y);

    /**
     *  \brief Get the x position of the Animation SpriteSheet
     *
     *  \sa setX()
     *  \sa setY()
     *  \sa getY()
     */
    float getX();

    /**
     *  \brief Get the y position of the Animation SpriteSheet
     *
     *  \sa setY()
     *  \sa setX()
     *  \sa getX()
     */
    float getY();




    
    /**
     *  \brief Set the frame for the Animation to show
     *
     *  \param frame The frame you want the Animation to show
     *
     *  \sa getFrame()
     *  \sa resetAnimation()
     */
    void setFrame(int frame);

    /**
     *  \brief Get the frame the Animation is showing
     *
     *  \sa setFrame()
     *  \sa resetAnimation()
     */
    int getFrame();



    /**
     *  \brief set the frame back to 0
     *
     *  \sa setFrame()
     *  \sa getFrame()
     */
    void resetAnimation();


    /**
     *  \brief add the amount of time passed so that the Animation
     *         can update.
     *
     *  \param time The amount of time passed in the frame
     */
    void addTime(float time);



    /**
     *  \brief Get a pointer to the SpriteSheet
     *
     *  \return SpriteSheet* of Animation SpriteSheet
     */
    SpriteSheet* getSpriteSheet();

    /**
     *  \brief Get a pointer to the SpriteSheet texture
     *
     *  \return SDL_Texture* of the SpriteSheet for rendering
     */
    SDL_Texture* getTexture();


    
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
     *  \return SDL_Rect* srcRect of SpriteSheet
     */
    SDL_Rect* getSrcRect();
  
  };
}}
#endif
