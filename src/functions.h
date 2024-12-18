#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <map>
#include <string>
#include <vector>

std::map<std::string, int> get_word_count(std::string file_path);
void output_word_counts(std::string file_path);

std::multimap<std::string, int> get_cross_ref(std::string file_path);
void output_word_cross_ref(std::string file_path);

void output_url_addresses(std::string file_path);

#endif