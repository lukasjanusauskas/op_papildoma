#include <iostream>
#include <map>
#include <fstream>
#include "functions.h"

int main() {
  auto word_counts =  get_word_count("data/wiki-test.txt");

  for(const auto &[key, value]: word_counts) 
    if(value > 1)
    std::cout << key << ": " << value << std::endl;

  return 0;
}

std::map<std::string, int> get_word_count(std::string file_path) {
  std::map<std::string, int> output_map;

  std::ifstream fd(file_path);

  std::string tmp_string;
  while(!fd.eof()) {
    fd >> tmp_string;
    
    for(size_t i = 0; i<tmp_string.length(); ++i)
      if(ispunct(tmp_string[i]))
      tmp_string.erase(i--, 1);
      
    auto search = output_map.find(tmp_string);

    if(search != output_map.end()) {
      int new_count = search->second + 1;
      output_map[tmp_string] = new_count;
    } else {
      output_map.emplace(tmp_string, 1);
    }
  }

  fd.close();
  return output_map;
}