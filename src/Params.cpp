#include <sstream>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>
#include <boost/date_time.hpp>
#include <string>
#include <map>

#include "Params.h"
#include "GeoIPTools.h"
#include "Log.h"


Params::Params()
{
    time_ = boost::posix_time::second_clock::local_time();
}

std::string time_t_to_string(time_t t)
{
    std::stringstream sstr;
    sstr << t;
    return sstr.str();
}


Params &Params::cookie_id(const std::string &cookie_id)
{
    if(cookie_id.empty())
    {
        cookie_id_ = time_t_to_string(time(NULL));
    }
    else
    {
        cookie_id_ = cookie_id;
        boost::u32regex replaceSymbol = boost::make_u32regex("[^0-9]");
        cookie_id_ = boost::u32regex_replace(cookie_id_ ,replaceSymbol,"");
    }
    boost::trim(cookie_id_);
    key_long_ = atol(cookie_id_.c_str());

    return *this;
}
Params &Params::get(const std::string &get)
{
    get_ = get;
    return *this;
}
Params &Params::post(const std::string &post)
{
    post_ = post;
    return *this;
}
std::string Params::getCookieId() const
{
    return cookie_id_;
}

std::string Params::getUserKey() const
{
    return cookie_id_;
}

unsigned long long Params::getUserKeyLong() const
{
    return key_long_;
}
boost::posix_time::ptime Params::getTime() const
{
    return time_;
}

Params &Params::guid(const std::string &guid)
{
    guid_ = guid;
    return *this;
}
Params &Params::title(const std::string &title)
{
    title_ = title;
    return *this;
}
Params &Params::domain(const std::string &domain)
{
    domain_ = domain;
    return *this;
}
Params &Params::domain_guid(const std::string &domain_guid)
{
    domain_guid_ = domain_guid;
    return *this;
}
Params &Params::user(const std::string &user)
{
    user_ = user;
    return *this;
}
Params &Params::user_guid(const std::string &user_guid)
{
    user_guid_ = user_guid;
    return *this;
}
Params &Params::request(const std::string &request)
{
    request_ = request;
    return *this;
}
Params &Params::rand(const std::string &rand)
{
    rand_ = rand;
    return *this;
}
