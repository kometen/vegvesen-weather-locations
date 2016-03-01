//============================================================================
// Name        : vegvesen-weather-locations.cpp
// Author      : Claus Guttesen
// Version     :
// Copyright   : Just let me know.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "ParseXML.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <username> <password>" << endl;
        return EXIT_FAILURE;
    }

    const string url = "https://www.vegvesen.no/ws/no/vegvesen/veg/trafikkpublikasjon/vaer/1/GetMeasurementWeatherSiteTable/";

    std::string username = argv[1];
    std::string password = argv[2];
    std::string credentials = username + ":" + password;

    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    request.setOpt(new curlpp::options::Url(url));
    request.setOpt(new curlpp::options::UserPwd(credentials));

    ostringstream out;
    out << request;

    gnome::ParseXML parse{out.str()};

    auto l = parse.locations();
    for (auto& i : l) {
        cout << i.first << ", " << i.second.description << endl;
    }
    cout << "locations: " << l.size() << endl;

	return 0;
}
