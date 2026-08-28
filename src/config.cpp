#include "config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<std::string> split(std::string str, std::string delimiter) {
  std::vector<std::string> lineSplit;

  size_t pos = 0;

  std::string token;

  while (pos = str.find(delimiter) != std::string::npos) {
    token = str.substr(0, pos);
    lineSplit.push_back(token);
    str.erase(0, pos + delimiter.size());
  }

  lineSplit.push_back(str);

  return lineSplit;
}