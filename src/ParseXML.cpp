/*
 * ParseXML.cpp
 *
 *  Created on: 29/02/2016
 *      Author: claus
 */

#include "ParseXML.hpp"

namespace gnome {

ParseXML::ParseXML(const std::string& s) {
    while (continue_parsing) {
        // Search for id in measurementSiteRecord. Start searching at position end_pos_longitude.
        start_pos_version = s.find(search_version, end_pos_longitude);
        end_pos_version = s.find(dquote, (start_pos_version + search_version_size));
        start_pos_id = s.find(search_id, (start_pos_version + search_version_size));
        end_pos_id = s.find(dquote, (start_pos_id + search_id_size));

        // If id is found.
        if (start_pos_version != -1 && end_pos_version != -1 && start_pos_id != -1 && end_pos_id != -1) {
            auto start = start_pos_id + search_id_size;
            auto end = end_pos_id - start;
            id = s.substr(start, end);

            // Search for location name.
            start_pos_description = s.find(search_description_start, end_pos_version);
            end_pos_desctiption = s.find(search_desciption_end, (start_pos_description + search_description_start_size));
            if (start_pos_description != -1 && end_pos_desctiption != -1) {
                auto start = start_pos_description + search_description_start_size;
                auto end = end_pos_desctiption - start;
                description = s.substr(start, end);
            } else {
                description = "Void";
            }

            // Search for latitude.
            start_pos_latitude = s.find(search_latitude_start, end_pos_desctiption);
            end_pos_latitude = s.find(search_latitude_end, (start_pos_description + search_latitude_start_size));
            if (start_pos_latitude != -1 && end_pos_latitude != -1) {
                auto start = start_pos_latitude + search_latitude_start_size;
                auto end = end_pos_latitude - start;
                latitude = s.substr(start, end);
            } else {
                latitude = "0.0";
            }

            // Search for longitude.
            start_pos_longitude = s.find(search_longitude_start, end_pos_latitude);
            end_pos_longitude = s.find(search_longitude_end, (start_pos_longitude + search_longitude_start_size));
            if (start_pos_longitude != -1 && end_pos_longitude != -1) {
                auto start = start_pos_longitude + search_longitude_start_size;
                auto end = end_pos_longitude - start;
                longitude = s.substr(start, end);
            } else {
                longitude = "0.0";
            }
            boost::algorithm::replace_all(description, "&#230;", "æ");
            boost::algorithm::replace_all(description, "&#248;", "ø");
            boost::algorithm::replace_all(description, "&#229;", "å");
            boost::algorithm::replace_all(description, "&#198;", "Æ");
            boost::algorithm::replace_all(description, "&#216;", "Ø");
            boost::algorithm::replace_all(description, "&#197;", "Å");
            Location loc {id, description, latitude, longitude};
            _locations.emplace(id, loc);
        } else {
            // No more id's, terminate while-loop.
            continue_parsing = false;
        }
    }
}

ParseXML::~ParseXML() {
}

std::unordered_map<std::string, Location> ParseXML::locations() {
    return _locations;
}

} /* namespace gnome */
