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
 * \file imageBase.h
 *
 * A blackhole library abstract class for all image based classes
 */

#pragma once
#ifndef IMAGE_BASE_H
#define IMAGE_BASE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


namespace blackhole {
namespace graphics {

  /**
   *  \brief The abstract class for all rendered images
   */
  
  class ImageBase {
  protected:
    SDL_RendererFlip rendererFlip = SDL_FLIP_NONE;

    int layer = 0;
  
    SDL_Rect destRect;
    SDL_Texture* texture;
    void init(const char* file, SDL_Renderer* renderer);
  public:

    /**
     *  \brief Overridable function for getting x position
     *
     *  return float of x position
     *
     *  \sa getY()
     */
    virtual float getX();

    /**
     *  \brief Overridable function for getting y position
     *
     *  return float of y position
     *
     *  \sa getX()
     */
    virtual float getY();


    /**
     *  \brief Overridable function for updating ImageBase time
     *
     *  \param time The amount of time passed in the frame
     */
    virtual void addTime(float time);



    /**
     *  \brief Overridable function for flipping ImageBase across the x plane
     *
     *  \param flipped Set ImageBase is flipped x
     *
     *  \sa setFlipY()
     *  \sa isFlippedY()
     *  \sa isFlippedX()
     */
    virtual void setFlipX(bool flipped);

    /**
     *  \brief Overridable function for flipping ImageBase across the y plane
     *
     *  \param flipped Set ImageBase is flipped y
     *
     *  \sa setFlipX()
     *  \sa isFlippedX()
     *  \sa isFlippedY()
     */
    virtual void setFlipY(bool flipped);

    /**
     *  \brief Overridable function for checking if ImageBase is 
     *         flipped across the x plane
     *
     *  \return true or false depending on if it is flipped
     *
     *  \sa isFlippedY()
     *  \sa setFlipX()
     *  \sa setFlipY()
     */
    virtual bool isFlippedX();

    /**
     *  \brief Overridable function for checking if ImageBase is 
     *         flipped across the y plane
     *
     *  \return true or false depending on if it is flipped
     *
     *  \sa isFlippedX()
     *  \sa setFlipX()
     *  \sa setFlipY()
     */
    virtual bool isFlippedY();
    

    /**
     *  \brief Overridable function for setting ImageBase texture
     *         generally used in the Camera class
     *
     *  \param tex Pointer to the texture that should replace the old texture
     *
     *  \sa getTexture()
     */
    virtual void setTexture(SDL_Texture* tex);

    /**
     *  \brief Overridable function for getting a pointer to the ImageBase
     *         texture. Used for rendering
     *
     *  \return SDL_Texture* of the ImageBase texture
     *
     *  \sa setTexture()
     */
    virtual SDL_Texture* getTexture();

    /**
     *  \brief Overridable function for getting the rendererflip for the
     *         ImageBase. Used for rendering
     *
     *  \return SDL_RendererFlip containing the texture flip data
     */
    virtual SDL_RendererFlip getRendererFlip();


    /**
     *  \brief Get a pointer to the destination rect used for positioning
     *         with the renderer
     *
     *  \return SDL_Rect* destRect of SpriteSheet
     *
     *  \sa getSrcRect()
     */
    virtual SDL_Rect* getDestRect();

    /**
     *  \brief Get a pointer to the source rect used for positioning
     *         with the renderer
     *
     *  \return NULL for rendering entire ImageBase
     *
     *  \sa getDestRect()
     */
    virtual SDL_Rect* getSrcRect();


    /**
     *  \brief Set the layer to be rendered on. 0 - low layer. 100 - high layer
     *
     *  \param layer Layer position to render on
     *
     *  \sa getLayer()
     */
    virtual void setLayer(int layer);

    /**
     *  \brief Get the layer ImageBase is on
     *
     *  \return int of layer eg. 0 or 100
     *
     *  \sa setLayer()
     */
    virtual int getLayer();
  };
}}

#endif
