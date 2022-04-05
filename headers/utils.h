#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <map>

#ifndef ISO8583PARSER_UTILS_H
#define ISO8583PARSER_UTILS_H

//convertion from hex to binary
std::string Hex2Binary(std::string hex_val);
size_t String2Numbers(std::string t);

/*std::vector<std::map<std::string, std::string>>*/ void dataElementEntry(short dataElmIndex, std::vector<std::map<std::string, std::string>> _elm, std::string isoMessage);


#endif //ISO8583PARSER_UTILS_H
