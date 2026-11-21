cmake_minimum_required(VERSION 3.20)
project(TP_POO CXX)

# O enunciado exige C++17 ou superior (por causa do "inline static" do Settings.h).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Os ficheiros de dados (mapas, ficheiros de teste do executa) vao para a pasta do executavel,
# para que "carrega mapa1.txt" e "executa teste1.txt" funcionem a partir dela.
file(GLOB TXT_FILES "${CMAKE_SOURCE_DIR}/dados/*.txt")
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

# Cada classe nova (.h e .cpp) entra nesta lista, na pasta do seu tema.
add_executable(TP_POO
        main.cpp
        Settings.h

        interface/Ecra.h
        interface/Ecra.cpp
        interface/Vista.h
        interface/Vista.cpp
        interface/Simulador.h
        interface/Simulador.cpp

        comandos/Comando.h
        comandos/Comando.cpp
        comandos/ComandoFabrica.h
        comandos/ComandoFabrica.cpp
        comandos/ComandoCarrega.h
        comandos/ComandoCarrega.cpp
        comandos/ComandoAvanca.h
        comandos/ComandoAvanca.cpp
        comandos/ComandoCompra.h
        comandos/ComandoCompra.cpp
        comandos/ComandoVende.h
        comandos/ComandoVende.cpp
        comandos/ComandoRoda.h
        comandos/ComandoRoda.cpp
        comandos/ComandoMelhora.h
        comandos/ComandoMelhora.cpp
        comandos/ComandoContrata.h
        comandos/ComandoContrata.cpp
        comandos/ComandoAtribui.h
        comandos/ComandoAtribui.cpp
        comandos/ComandoDespede.h
        comandos/ComandoDespede.cpp
        comandos/ComandoEstado.h
        comandos/ComandoEstado.cpp
        comandos/ComandoLposicao.h
        comandos/ComandoLposicao.cpp
        comandos/ComandoGrava.h
        comandos/ComandoGrava.cpp
        comandos/ComandoRecupera.h
        comandos/ComandoRecupera.cpp
        comandos/ComandoExecuta.h
        comandos/ComandoExecuta.cpp
        comandos/ComandoAjuda.h
        comandos/ComandoAjuda.cpp
        comandos/ComandoFim.h
        comandos/ComandoFim.cpp

        fabrica/Fabrica.h
        fabrica/Fabrica.cpp
        fabrica/Terreno.h
        fabrica/Terreno.cpp
        fabrica/Solo.h
        fabrica/Solo.cpp
        fabrica/Cratera.h
        fabrica/Cratera.cpp
        fabrica/Deposito.h
        fabrica/Deposito.cpp
        fabrica/Posicao.h
        fabrica/Posicao.cpp
        fabrica/Aleatorio.h
        fabrica/Aleatorio.cpp
        fabrica/Engenheiro.h
        fabrica/Engenheiro.cpp

        maquinas/Direcao.h
        maquinas/Maquina.h
        maquinas/Maquina.cpp
        maquinas/Perfuradora.h
        maquinas/Perfuradora.cpp
        maquinas/Transportador.h
        maquinas/Transportador.cpp
        maquinas/Refinaria.h
        maquinas/Refinaria.cpp
        maquinas/Oficina.h
        maquinas/Oficina.cpp
        maquinas/Silo.h
        maquinas/Silo.cpp
        maquinas/Lancador.h
        maquinas/Lancador.cpp

        itens/Item.h
        itens/Item.cpp
        itens/MateriaPrima.h
        itens/MateriaPrima.cpp
        itens/ProdutosRefinados.h
        itens/ProdutosRefinados.cpp
        itens/MinerioFerro.h
        itens/MinerioFerro.cpp
        itens/SilicioBruto.h
        itens/SilicioBruto.cpp
        itens/Gelo.h
        itens/Gelo.cpp
        itens/PlacaFerro.h
        itens/PlacaFerro.cpp
        itens/SilicioPuro.h
        itens/SilicioPuro.cpp
        itens/Agua.h
        itens/Agua.cpp
        itens/KitHabitat.h
        itens/KitHabitat.cpp
)

# Assim o #include "Item.h" continua a funcionar em qualquer ficheiro, seja qual for a pasta.
target_include_directories(TP_POO PRIVATE
        ${CMAKE_SOURCE_DIR}/interface
        ${CMAKE_SOURCE_DIR}/comandos
        ${CMAKE_SOURCE_DIR}/fabrica
        ${CMAKE_SOURCE_DIR}/maquinas
        ${CMAKE_SOURCE_DIR}/itens
        ${CMAKE_SOURCE_DIR}    # Settings.h; fica por ultimo para as pastas terem prioridade
)
