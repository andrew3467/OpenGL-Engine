//
// Created by Andrew Graser on 7/25/2024.
//

#ifndef OPENGL_ENGINE_LOG_H
#define OPENGL_ENGINE_LOG_H

#include "glepch.h"

#include "spdlog/logger.h"

namespace GLE {
    class Log {
    public:
        static void Init();


        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return mCoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> mCoreLogger;
    };

}


#define GLE_TRACE(...)    ::GLE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GLE_INFO(...)     ::GLE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GLE_WARN(...)     ::GLE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GLE_ERROR(...)    ::GLE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GLE_FATAL(...)    ::GLE::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define GLE_ASSERT(x, ...)    {if(!(x)) {GLE_ERROR("Assertion failed: {0}", __VA_ARGS__); }}

#endif //OPENGL_ENGINE_LOG_H
