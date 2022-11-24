#pragma once

#include <cstdarg>
#include <cstdio>

#define LOGGER_MAX_BUFFER_SIZE 1024

namespace Cosmos
{
    class Logger
    {
    public:

        typedef enum Severity
        {
            TRACE = 0,
            INFO,
            WARN,
            ERROR,
            ASSERT
        } Severity;

    public:

        // prints to standart console output
        static void Print(Severity severity, const char* file, unsigned int line, const char* message, ...)
        {
            printf("[%s]", SeverityToConstChar(severity));

            if (severity >= Severity::WARN) printf("[Line %d:File %s]", line, file);

            char buffer[LOGGER_MAX_BUFFER_SIZE];
            va_list args;
            va_start(args, message);
            vsnprintf(buffer, LOGGER_MAX_BUFFER_SIZE, message, args);
            va_end(args);

            printf(" %s\n", buffer);
        }

        // returns the severity as a const char*
        static const char* SeverityToConstChar(Severity severity)
        {
            switch (severity)
            {
                case Severity::TRACE: return "Trace";
                case Severity::INFO: return "Info";
                case Severity::WARN: return "Warn";
                case Severity::ERROR: return "Error";
                case Severity::ASSERT: return "Assert";
            }
            return "Unknown";
        }
    };
}

#define COSMOS_WARN(...)    Cosmos::Logger::Print(Cosmos::Logger::Severity::WARN, __FILE__, __LINE__, __VA_ARGS__);
#define COSMOS_ERROR(...)    Cosmos::Logger::Print(Cosmos::Logger::Severity::ERROR, __FILE__, __LINE__, __VA_ARGS__);
#define COSMOS_ASSERT(x, ...)    { if(!(x)) { Cosmos::Logger::Print(Cosmos::Logger::Severity::ASSERT, __FILE__, __LINE__, __VA_ARGS__); abort();}}

#if defined(ENGINE_DEBUG) || defined(SANDBOX_DEBUG)
    #define COSMOS_TRACE(...)	Cosmos::Logger::Print(Cosmos::Logger::Severity::TRACE, __FILE__, __LINE__, __VA_ARGS__);
    #define COSMOS_INFO(...)	Cosmos::Logger::Print(Cosmos::Logger::Severity::INFO, __FILE__, __LINE__, __VA_ARGS__);
#else
    #define COSMOS_TRACE
    #define COSMOS_INFO
#endif