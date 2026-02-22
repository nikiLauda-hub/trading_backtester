cmake_minimum_required(VERSION 3.20)
project(trading_backtester CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/pybind11)

pybind11_add_module(backtest_core core/main.cpp)

target_include_directories(backtest_core PRIVATE core)


# Автоматическое копирование собранного модуля в папку scripts
add_custom_command(TARGET backtest_core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:backtest_core>
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts/
)