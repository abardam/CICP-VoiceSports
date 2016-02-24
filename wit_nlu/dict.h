#pragma once


#ifndef DICT_H
#define DICT_H
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>


class dict {
private:
	std::map<std::string, std::string> ja2en;
	
public:
	dict();
	std::string getEn(std::string ja);
	std::vector<std::string> getVec(std::string text);

};

#endif /* !DICT_H */