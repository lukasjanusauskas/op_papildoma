#include <iostream>
#include <regex>

#include <map>
#include <set>

#include <fstream>
#include <sstream>

#include "functions.h"

int main() {
  // auto word_counts = get_word_count("data/wiki-test.txt");

  // for(const auto &[key, value]: word_counts) {
  //   std::cout << key << " " << value << "\n";
  // }

  // auto cross_ref =  get_cross_ref("data/wiki-test.txt");

  // for(auto it = cross_ref.begin(); it != cross_ref.end(); it++) {
  //   std::cout << it->first << " " << it->second << std::endl;
  // }

  // auto set_urls = get_url_adresses("data/url-test.txt");
  // for(auto s: set_urls)
  //   std::cout << s << std::endl;

  output_word_cross_ref("data/wiki-test.txt", "output/cross-ref.txt");

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

  // Istrinti narius, pasikartojancius viena karta
  for (auto &[key, value]: output_map)
    if(value <= 1) 
      output_map.erase(key);

  return output_map;
}

std::multimap<std::string, int> get_cross_ref(std::string file_path){
  std::multimap<std::string, int> output_map;
  std::map<std::string, bool> repeats;

  std::ifstream fd(file_path);

  std::string line, tmp_string;
  int counter = 1;

  while(!fd.eof()){
    std::stringstream stream;
    std::map<std::string, int> tmp_map;

    std::getline(fd, line);

    stream << line;

    while (stream >> tmp_string) {
      
      for(size_t i = 0; i<tmp_string.length(); ++i)
        if(ispunct(tmp_string[i]))
          tmp_string.erase(i--, 1);

      // Jei skaicius: neiskaiciuojam
      if(!isalpha(tmp_string[0])) continue;

      auto search = tmp_map.find(tmp_string);
      if(search == tmp_map.end()) {
        tmp_map.emplace(tmp_string, 0);

        auto new_pair = std::make_pair(tmp_string, counter);
        output_map.insert(new_pair);
      } 

      auto rep_search = repeats.find(tmp_string);

      if(rep_search != repeats.end()) {
        repeats[tmp_string] = true;
      } else {
        repeats.emplace(tmp_string, false);
      }
    }

    counter++;
  }

  for(auto it = output_map.begin(); it != output_map.end(); it++) {
    auto search_in_repeat = repeats.find(it->first);

    if(search_in_repeat->second) continue;
    else output_map.erase(search_in_repeat->first);
  }

  fd.close();
  return output_map;
}

std::set<std::string> get_url_adresses(std::string file_path) {
  std::set<std::string> set_urls;
  std::ifstream fd(file_path);
  std::string tmp_string;
  const std::regex pattern("(https?://)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]+\\.[a-zA-Z0-9()]{1,}");

  while(!fd.eof()) {
    fd >> tmp_string;

    if(std::regex_match(tmp_string, pattern)) 
      set_urls.insert(tmp_string);
  }

  fd.close();
  return set_urls;
}

void output_word_counts(std::string file_path, std::string output_path){
  auto word_counts = get_word_count(file_path);

  std::ofstream fr(output_path);
  for(auto &[key, value]: word_counts)
    fr << key << ": " << value << std::endl;

  fr.close();
}

void output_word_cross_ref(std::string file_path, std::string output_path){
  auto cross_ref = get_cross_ref(file_path);

  std::ofstream fr(output_path);
  std::string last = "";

  for(auto it = cross_ref.begin(); it != cross_ref.end(); it++) {
    if(it->first.compare(last) == 0) {
      fr << "\t" << it->second;
    }

    else {
      fr << "\n" << it->first << " " << it->second;
      last = it->first;
    }
  }

  fr.close();
}

void output_url_addresses(std::string file_path, std::string output_path){
  auto set_urls = get_url_adresses(file_path);

  std::ofstream fr(output_path);
  for(auto s: set_urls)
    fr << s << std::endl;

  fr.close();
}