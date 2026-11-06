# TP de POO 2026/27: a fábrica em Marte

Trabalho prático de Programação Orientada a Objetos (DEIS/ISEC), em par: Luís Vieira e Rafael Amado.

## Como abrir
Abrir esta pasta no CLion (File > Open). O projeto é CMake, em C++17, e compila com os avisos todos ligados
(`-Wall -Wextra -Wpedantic`): **o enunciado exige zero warnings**.

## Regras do enunciado que valem para o código todo
- O `Settings.h` é o dos docentes e **não se altera** na versão entregue: todos os valores vêm dali.
- Toda a apresentação da fábrica e do painel passa pela classe `Ecra` (buffer de no máximo 40x80, sem coleções).
- Os comandos são uma hierarquia polimórfica com a base `Comando` e o método `executa()`.
- O silo não usa nenhuma coleção da biblioteca standard.
- **Cada checkpoint leva só o que pede**: o que estiver feito a mais é penalizado.

## Entregas
| Entrega | Prazo | Zip |
|---|---|---|
| Checkpoint 1 | 08/11, 12:00 | `poo_2627_m1_nome1_numero1_nome2_numero2.zip` |
| Checkpoint 2 | 22/11, 12:00 | `poo_2627_m2_nome1_numero1_nome2_numero2.zip` |
| Final | 13/12, 12:00 | `poo_2627_final_nome1_numero1_nome2_numero2.zip` |

O zip leva o projeto CLion (sem executável nem `cmake-build-*`) e o relatório em PDF.

### Checkpoint 1
- [ ] Classe `Ecra`, completa
- [ ] Criação da fábrica (o que vai ser o `fabrica` e o `carrega`) e a sua apresentação pelo `Ecra`: molduras, régua,
      crateras, depósitos e o painel de estado (pode ser parcial)
- [ ] `lposicao` (só para o terreno) e `fim`
- [ ] Planeamento das classes, já organizadas em `.h` e `.cpp`
- [ ] Relatório simplificado: opções tomadas e classes planeadas (máximo 5 páginas, sem capa e índice)
