set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(miniz_wasm main.cpp)
target_compile_options(miniz_wasm PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(miniz_wasm PRIVATE miniz)
target_link_options(miniz_wasm PRIVATE
    --no-entry
    --bind
    -sALLOW_MEMORY_GROWTH=1
    -sDISABLE_EXCEPTION_CATCHING=1
    -sMODULARIZE)
