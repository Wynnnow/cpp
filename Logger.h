//
// Created by Vixtel on 2024/1/2.
//

#ifndef CPP_LOGGER_H
#define CPP_LOGGER_H
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/async.h"
#include <memory>
#include <iostream>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

    void initialize(const std::string& logDir, spdlog::level::level_enum logLevel, const std::string& logFileName, int maxAgeDays) {
        spdlog::init_thread_pool(8192, 1);
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(logDir + "/" + logFileName, maxAgeDays, 0);
        std::vector<spdlog::sink_ptr> sinks {stdout_sink, file_sink};
        auto logger = std::make_shared<spdlog::async_logger>("multi_sink", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
        spdlog::set_level(logLevel);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v");
    }

    void destroy() {
        spdlog::drop_all();
    }

    template <typename... Args>
    void log(spdlog::level::level_enum lvl, const char* file, int line, const char* format, const Args&... args) {
        spdlog::log(lvl, "[{}:{}] {}", file, line, fmt::format(format, args...));
    }

private:
    Logger() {}
};

#define LOG_TRACE(...) Logger::getInstance().log(spdlog::level::trace, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::getInstance().log(spdlog::level::debug, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) Logger::getInstance().log(spdlog::level::info, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) Logger::getInstance().log(spdlog::level::warn, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().log(spdlog::level::err, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::getInstance().log(spdlog::level::critical, __FILE__, __LINE__, __VA_ARGS__)

#endif //CPP_LOGGER_H
