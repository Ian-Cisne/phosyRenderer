
#include "logger.h"

namespace rasterizer {
    
    template <>
    Logger & Logger::operator<<<LogLevel>(LogLevel const &level) {
        static std::array<std::string, LogLevelQuantities> prefixes (
            {
                "\033[34;1m", //info
                "\033[32;1m", //success
                "\033[92;3m", //debug
                "\033[33;1m", //warninng
                "\033[31;1m", //error
                "\033[01;3m"  //miscellaneuos
            }
        );
        std::time_t t = std::time(0);   
        std::tm* now = std::localtime(&t);
        
        stream_ <<  prefixes[loglevel_] << "[" << std::put_time(std::localtime(&t), "%T") << "]: ";


        return *this;
    }

} //namespace rasterizer