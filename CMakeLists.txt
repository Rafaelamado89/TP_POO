cmake_minimum_required(VERSION 3.20)
project(TP_POO CXX)

# O enunciado exige C++17 ou superior (por causa do "inline static" do Settings.h).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB TXT_FILES "${CMAKE_SOURCE_DIR}/*.txt")
foreach(TXT_FILE ${TXT_FILES})
    get_filename_component(FILENAME ${TXT_FILE} NAME)
    configure_file(${TXT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME} COPYONLY)
endforeach()

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
        Ecra.h
        Ecra.cpp
        Terreno.h
        Terreno.cpp
        Solo.h
        Solo.cpp
        Cratera.h
        Cratera.cpp
        Deposito.h
        Deposito.cpp
        Fabrica.h
        Fabrica.cpp
        Aleatorio.h
        Aleatorio.cpp
        Posicao.h
        Posicao.cpp
        Vista.h
        Vista.cpp

        Item.h
        Item.cpp
        MateriaPrima.h
        MateriaPrima.cpp
        ProdutosRefinados.h
        ProdutosRefinados.cpp
        MinerioFerro.h
        MinerioFerro.cpp
        SilicioBruto.h
        SilicioBruto.cpp
        Gelo.h
        Gelo.cpp
        PlacaFerro.h
        PlacaFerro.cpp
        SilicioPuro.h
        SilicioPuro.cpp
        Agua.h
        Agua.cpp
        KitHabitat.h
        KitHabitat.cpp

        Direcao.h
        Maquina.h
        Maquina.cpp
        Perfuradora.h
        Perfuradora.cpp
        Transportador.h
        Transportador.cpp
        Refinaria.h
        Refinaria.cpp
        Oficina.h
        Oficina.cpp
        Silo.h
        Silo.cpp
        Lancador.h
        Lancador.cpp
        Engenheiro.h
        Engenheiro.cpp
        Comando.h
        Comando.cpp
)
