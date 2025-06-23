#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

void write_to_file(const std::string& filename, const std::vector<std::string>& content);
void write_to_file(const std::string& filename, const std::string& content);

#endif // UTILS_H 