cmake_minimum_required(VERSION 3.20)
project(TP_POO CXX)

# O enunciado exige C++17 ou superior (por causa do "inline static" do Settings.h).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# O programa tem de compilar sem qualquer warning: ligamos os avisos todos
# para os ver durante o desenvolvimento, e nao so na entrega.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (MSVC)
    add_compile_options(/W4)
endif ()

# Cada classe nova (.h e .cpp) entra nesta lista.
# O "New > C++ Class" do CLion acrescenta-a sozinho.
add_executable(TP_POO
        main.cpp
        Settings.h
)
