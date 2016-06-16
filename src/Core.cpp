#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <map>

#include <ctime>
#include <cstdlib>
#include <chrono>

#include "../config.h"

#include "Config.h"
#include "Core.h"
#include "DB.h"
#include "base64.h"
#include "json.h"

Core::Core()
{
    std::clog<<"["<<tid<<"]core start"<<std::endl;
}
//-------------------------------------------------------------------------------------------------------------------
Core::~Core()
{
}
//-------------------------------------------------------------------------------------------------------------------
std::string Core::Process(Params *prms)
{
    #ifdef DEBUG
        auto start = std::chrono::high_resolution_clock::now();
        printf("%s\n","/////////////////////////////////////////////////////////////////////////");
    #endif // DEBUG
    startCoreTime = boost::posix_time::microsec_clock::local_time();

    params = prms;

    endCoreTime = boost::posix_time::microsec_clock::local_time();
    #ifdef DEBUG
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        printf("Time %s taken: %lld \n", __func__,  microseconds);
        printf("%s\n","/////////////////////////////////////////////////////////////////////////");
    #endif // DEBUG
    retJson["status"] = "OK";
    return retJson.dump();
}
//-------------------------------------------------------------------------------------------------------------------
void Core::ProcessSaveResults()
{
    request_processed_++;
    mongo::DB db("log");
    boost::posix_time::ptime time_ = boost::posix_time::second_clock::local_time();
    boost::posix_time::ptime utime_ = boost::posix_time::second_clock::universal_time();
    std::tm pt_tm = boost::posix_time::to_tm(time_ + (time_ - utime_));
    std::time_t t = mktime(&pt_tm);
    mongo::Date_t dt(t * 1000LLU);
    

    #ifdef DEBUG
        printf("%s\n","Save /////////////////////////////////////////////////////////////////////////");
    #endif // DEBUG
    try
    {
        std::string guid = params->json_["guid"];
        std::string title = params->json_["title"];
        std::string domain = params->json_["domain"];
        std::string domain_guid = params->json_["domain_guid"];
        std::string user = params->json_["user"];
        std::string user_guid = params->json_["user_guid"];
        bool garanted = false;
        if (params->json_["request"] == "complite")
        {
            garanted = true;
        }
        mongo::BSONObj record_block = mongo::BSONObjBuilder().genOID().
                                    append("dt", dt).
                                    append("guid", guid).
                                    append("title", title).
                                    append("domain", domain).
                                    append("domain_guid", domain_guid).
                                    append("user", user).
                                    append("user_guid", user_guid).
                                    append("garanted", garanted).
                                    obj();
        db.insert(cfg->mongo_log_collection_block_, record_block, true);
    }
    catch (std::exception const &ex)
    {
        Log::err("insert into log db: %s\n %s\n", ex.what(), params->json_.dump().c_str());
    }
    
    #ifdef DEBUG
        printf("%s\n","/////////////////////////////////////////////////////////////////////////");
    #endif // DEBUG
}
