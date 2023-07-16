cmake_minimum_required(VERSION 3.25)

project(miniz_wasm)
enable_language(C)

# Save compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Third Party
add_subdirectory(third_party SYSTEM)

# miniz_wasm
add_executable(miniz_wasm main.c)
target_link_libraries(miniz_wasm PRIVATE miniz)
