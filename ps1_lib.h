#ifndef PS1_LIB_H
#define PS1_LIB_H

#include <string>
#include <string_view>
#include <vector>

std::string GetPs1(std::string_view pwd, std::string_view home,
                   std::string_view prefix, std::string_view suffix,
                   int max_length,
                   const std::vector<std::string>& truncated_paths);

#endif