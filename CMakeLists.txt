cmake_minimum_required(VERSION 3.10)
project(miner_weeper)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Добавить исполняемый файл
add_executable(miner_weeper 
    "miner-weeper/main.cpp"
    "miner-weeper/MinerWeeper.cpp"
    "miner-weeper/MinerWeeper.hpp"
)

# Связать с SFML
target_link_libraries(miner_weeper 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio
)

# Копировать ресурсы после сборки
file(COPY 
    "${CMAKE_SOURCE_DIR}/miner-weeper/images"
    DESTINATION ${CMAKE_BINARY_DIR}
)
