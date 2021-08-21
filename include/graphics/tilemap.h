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
 * \file tilemap.h
 *
 * A blackhole library class for turning tilemaps into images
 */

#pragma once

#ifndef TILEMAP_H
#define TILEMAP_H

#include <tmxparser/Tmx.h>
#include "image.h"
#include "spritesheet.h"

namespace blackhole {
namespace graphics {

  /**
   *  \brief A class for loading tmx files as images built on ImageBase
   */
  class Tilemap {
  private:
    Tmx::Map* map;
    Image** tileLayers;
  public:
    /**
     *  \brief Constructor of Tilemap
     *
     *  \param file The location of tmx file
     *  \param renderer The renderer of the Window
     */
    Tilemap(const char* file, SDL_Renderer* renderer);
    ~Tilemap();

    /**
     *  \brief Get the raw data of the tilemap
     *
     *  return Tmx::Map containing tilemap data
     */
    Tmx::Map* getMap();

    /**
     *  \brief Get the image made from the tilemap Tile layers
     *
     *  \param layer Tile layer to get
     *
     *  \return Image* of the Tile layer
     *
     *  \sa getTileLayer()
     *  \sa getObjectGroup()
     */
    Image* getTileLayerImage(int layer);

    /**
     *  \brief Get the raw data of the tilemap Tile layers
     *
     *  \param layer Tile layer to get
     *
     *  \return Tmx::TileLayer* of the Tile Layer raw data
     *
     *  \sa getTileLayerImage()
     *  \sa getObjectGroup()
     */
    const Tmx::TileLayer* getTileLayer(int layer);

    /**
     *  \brief Get the raw data of the tilemap Object Groups
     *
     *  \param layer Object Group to get
     *
     *  \return Tmx::ObjectGroup* of the Object Group raw data
     *
     *  \sa getTileLayerImage()
     *  \sa getTileLayer()
     */
    const Tmx::ObjectGroup* getObjectGroup(int layer);
  
  };
}}

#endif
