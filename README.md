# IC3
Information and Coding project 3

## Comandos de Compilação e Resultados

### FCM/modelEntropy:
#### Comandos de compilação:
> g++ modelEntropy.cpp -o modelEntropy

>./modelEntropy PT.utf8

Estes comandos são para calcular um modelo a partir de um ficheiro de texto (neste caso PT.utf8 que representa a lingua portuguesa)

### FCM/TESTEFCM:
#### Comandos de compilação:
> g++ testefcm.cpp -o testefcm


> ./testefcm ModelPT.txt TextoSimplesTeste.txt

Se já tivermos um modelo criado (por ex. ModelPT.txt), usámos este comando de compilação 
(opção y) para calcular a entropia do modelo e calcular distância e entropia estimada 
em relação ao segundo argumento (ficheiro de texto) 

> ./testefcm PT.utf8 TextoSimplesTeste.txt

Este comando é para criar um modelo de uma determinado linguagem/texto (opção n) e
calcular entropia do modelo e distância e entropia estimada em relação a um certo texto
(por exemplo o da Carochinha, TextoSimplesTeste.txt passado como segundo argumento)

### LANG:
#### Comandos de compilação:
> g++ lang.cpp -o lang

### FINDLANG:
#### Comandos de compilação:
> g++ findlang.cpp -o findlang
> 
> ./findlang BOSN.utf8 ENG.utf8 ESP.utf8 FI.utf8 GER.utf8 IT.utf8 LT.utf8 PT.utf8 RU.utf8 SWE.utf8 TURK.utf8 TextoSimplesTeste.txt 
