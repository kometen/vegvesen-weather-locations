/*
 * Common.hpp
 *
 *  Created on: 29/02/2016
 *      Author: claus
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/algorithm/string/replace.hpp>

struct Location {
    std::string id;
    std::string description;
    std::string latitude;
    std::string longitude;

    Location(std::string a, std::string b, std::string c, std::string d)
    : id{a}, description{b}, latitude{c}, longitude{d} {}
};


#endif /* COMMON_HPP_ */
