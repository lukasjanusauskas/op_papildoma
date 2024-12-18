#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "functions.h"

int main() {
  // auto word_counts = get_word_count("data/wiki-test.txt");

  // for(const auto &[key, value]: word_counts) {
  //   std::cout << key << " " << value << "\n";
  // }

  auto cross_ref =  get_cross_ref("data/wiki-test.txt");

  for(auto it = cross_ref.begin(); it != cross_ref.end(); it++) {
    std::cout << it->first << " " << it->second << std::endl;
  }

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

std::multimap<std::string, int> get_cross_ref(std::string file_path){
  std::multimap<std::string, int> output_map;

  std::ifstream fd(file_path);

  std::string line, tmp_string;
  int counter = 1;

  while(!fd.eof()){
    std::stringstream stream;
    std::map<std::string, int> tmp_map;

    std::cout << counter << "\n\n";
    std::getline(fd, line);

    stream << line;

    while (stream >> tmp_string) {
      
      for(size_t i = 0; i<tmp_string.length(); ++i)
        if(ispunct(tmp_string[i]))
          tmp_string.erase(i--, 1);

      auto search = tmp_map.find(tmp_string);
      if(search == tmp_map.end()) {
        tmp_map.emplace(tmp_string, 0);
        auto new_pair = std::make_pair(tmp_string, counter);
        output_map.insert(new_pair);
      }

    }

    counter++;
  }

  fd.close();
  return output_map;
}