/*
 * ParseXML.hpp
 *
 *  Created on: 29/02/2016
 *      Author: claus
 */

#ifndef PARSEXML_HPP_
#define PARSEXML_HPP_

#include "Common.hpp"

namespace gnome {

class ParseXML {
private:
    // Place locations onto vector.
    std::unordered_map<std::string, Location> _locations;

    // Stop at end of xml-string.
    bool continue_parsing = true;

    const std::string dquote = "\"";

    // Declare strings and size on strings when searching for id.
    const std::string search_version = "<measurementSiteRecord version=\"";
    const std::string search_id = "id=\"";
    const size_t search_version_size = search_version.size();
    const size_t search_id_size = search_id.size();
    size_t start_pos_version {0};
    size_t end_pos_version {0};
    size_t start_pos_id {0};
    size_t end_pos_id {0};
    std::string id {};

    // Declare string and size on strings when searching for description.
    const std::string search_description_start = "<measurementSiteName><values><value lang=\"nob\">";
    const std::string search_desciption_end = "</value></values></measurementSiteName>";
    const size_t search_description_start_size = search_description_start.size();
    size_t start_pos_description {0};
    size_t end_pos_desctiption {0};
    std::string description {};

    // Declare string and size on strings when searching for latitude and longitude.
    const std::string search_latitude_start = "<latitude>";
    const std::string search_latitude_end = "</latitude>";
    const size_t search_latitude_start_size = search_latitude_start.size();
    size_t start_pos_latitude {0};
    size_t end_pos_latitude {0};
    std::string latitude {""};

    const std::string search_longitude_start = "<longitude>";
    const std::string search_longitude_end = "</longitude>";
    const size_t search_longitude_start_size = search_longitude_start.size();
    size_t start_pos_longitude {0};
    size_t end_pos_longitude {0};
    std::string longitude {""};

public:
    ParseXML(const std::string&);
    virtual ~ParseXML();
    std::unordered_map<std::string, Location> locations();
};

} /* namespace gnome */

#endif /* PARSEXML_HPP_ */
