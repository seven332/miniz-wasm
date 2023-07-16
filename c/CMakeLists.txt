cmake_minimum_required(VERSION 3.25)

project(miniz_wasm)
enable_language(C CXX)

# Save compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(third_party SYSTEM)
add_subdirectory(src)
