//
// Created by Andrew Graser on 7/25/2024.
//

#include "Core/Log.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace GLE {
    std::shared_ptr<spdlog::logger> Log::mCoreLogger = nullptr;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        mCoreLogger = spdlog::stdout_color_mt("GLE");
        mCoreLogger->set_level(spdlog::level::trace);
    }
}
