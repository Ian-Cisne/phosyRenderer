#ifndef LOGGER_H_
#define LOGGER_H_


#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>
#include <ctime>

namespace rasterizer
{
    enum LogLevel{
        kInfo,
        kSuccess,
        kDebug,
        kWarning,
        kError,
        kMiscellaneuos,
        LogLevelQuantities
    };

    class Logger {
    private:
        Logger( std::ostream & stream):  stream_{stream}{
        }

        ~Logger(){
            stream_ << "\033[0m\n";
        }

    public:
        static Logger& getLogger(std::ostream & stream) {
            static Logger logger(stream);
            return logger;
        }
        
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        template <typename T>
        Logger & operator<<(T const &value);
    private:
        std::ostream &stream_;
        LogLevel loglevel_;
    };
    
    template <typename T>
    Logger & Logger::operator<<(T const &value)
    {
        stream_ << value;
        return *this;
    }


    template <>
    Logger & Logger::operator<<(LogLevel const &level)
    {
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
} // namespace rasterizer

#endif