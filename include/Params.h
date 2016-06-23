#ifndef PARAMS_H
#define PARAMS_H

#include <sstream>
#include <string>
#include <boost/date_time.hpp>
#include <boost/algorithm/string/join.hpp>
#include <vector>
#include <map>

/** \brief Параметры, которые определяют показ рекламы */
class Params
{
public:
    std::string cookie_id_;
    std::string post_;
    std::string get_;
    unsigned long long key_long_;
    boost::posix_time::ptime time_;
    std::string guid_;
    std::string request_;
    std::string rand_;

    Params();
    Params &parse();

    /** Установка параметров, которые определяют показ рекламы */
    Params &cookie_id(const std::string &cookie_id);
    Params &get(const std::string &get);
    Params &post(const std::string &post);
    Params &guid(const std::string &guid);
    Params &request(const std::string &request);
    Params &rand(const std::string &rand);
    
    /** Получение параметров, которые определяют показ рекламы */
    std::string getCookieId() const;
    std::string getUserKey() const;
    unsigned long long getUserKeyLong() const;
    boost::posix_time::ptime getTime() const;

};

#endif // PARAMS_H
