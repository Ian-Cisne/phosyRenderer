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
        static Logger& getLogger(std::ostream & stream=std::cerr) {
            static Logger logger(stream);
            return logger;
        }
        
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        template <typename T>
        inline Logger & operator<<(T const &value) {
            stream_ << value;
            return *this;
        }
    private:
        std::ostream &stream_;
        LogLevel loglevel_;
    };
    

} // namespace rasterizer

#endif