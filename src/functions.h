#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <map>
#include<set>
#include <string>
#include <vector>

std::map<std::string, int> get_word_count(std::string file_path);
void output_word_counts(std::string output_path);

std::multimap<std::string, int> get_cross_ref(std::string file_path);
void output_word_cross_ref(std::string output_path);

std::set<std::string> get_url_adresses(std::string file_path);
void output_url_addresses(std::string output_path);

#endif