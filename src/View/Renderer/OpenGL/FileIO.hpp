//
// Created by charl on 10/03/2021.
//

#ifndef ICT397_GAME_ENGINE_FILEIO_HPP
#define ICT397_GAME_ENGINE_FILEIO_HPP
#include <iostream>
/**
 * Loads a texture from a file and returns its data
 * @param string - filename
 * @param int& - width
 * @param int& - height
 * @param int& - nrComponents
 * @param int& - reqComponents
 * @return unsigned char*
 */
unsigned char* TextureFromFile(const std::string& filename, int &width,int &height, int &nrComponents,int reqComponents);
/**
 * @brief Deletes the loaded texture data
 * @param unsigned char* - data
 */
void FreeTextureData(unsigned char* data);

#endif // ICT397_GAME_ENGINE_FILEIO_HPP
