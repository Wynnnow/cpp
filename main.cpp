#include <iostream>
#include "Logger.h"

int main() {
    Logger::getInstance().initialize("./", spdlog::level::trace, "log.txt", 7);

    Logger::getInstance().destroy();
    return 0;
}
