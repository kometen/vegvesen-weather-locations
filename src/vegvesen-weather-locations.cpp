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

#include <pqxx/pqxx>

#include "ParseXML.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <username> <password>" << endl;
        return EXIT_FAILURE;
    }

    try {
        try {
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

            pqxx::connection C("dbname=weather user=claus hostaddr=127.0.0.1 port=5432");
            if (!C.is_open()) {
                cerr << "Unable to connect to database " << C.dbname() << endl;
                return EXIT_FAILURE;
            }

            std::string query = "select * from locations";
            pqxx::nontransaction N(C);
            pqxx::result R(N.exec(query));

            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
//                cout << c[1].as<int>() << ", " << c[2].as<string>() << endl;
                l.erase(to_string(c[1].as<int>()));
            }
            C.disconnect();

            pqxx::connection D("dbname=weather user=claus hostaddr=127.0.0.1 port=5432");
            if (!D.is_open()) {
                cerr << "Unable to connect to database " << D.dbname() << endl;
                return EXIT_FAILURE;
            }

            pqxx::work W(D);
            for (auto& i : l) {
                query = "insert into locations (site_id, measurementsitename, coordinate) values (";
                query += i.second.site_id + ",'" + i.second.description + "',point(" + i.second.longitude + "," + i.second.latitude + "))";
                W.exec(query);
            }
            W.commit();
//            cout << "locations: " << l.size() << endl;

            C.disconnect();
            return EXIT_SUCCESS;

        } catch (const exception& e) {
            cerr << e.what() << endl;
            return EXIT_FAILURE;
        }
    } catch (curlpp::LogicError& e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    } catch (curlpp::RuntimeError& e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
