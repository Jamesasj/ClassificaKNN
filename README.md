# ClassificaKNN
Algoritmo de KNN implementado em C++ para realizar a classificação das íris das plantas

Implementado para a disciplina de Mineração de Dados

https://archive.ics.uci.edu/ml/datasets/iris

<h4> Como usar </h4>

Compile o arquivo main.cpp

```
g++ main.cpp -o main
```
Execute o programa usando os seguintes argumentos 

[0] -> número do K 

[1] -> base de dados que queira usar para classificar (training_data, testing_data) ou criar a sua para classificar.
Por padrão ele cria um arquivo result como a saída padrão para mostrar a classificação 


```
./main 7 training_data > result
```
<h5> Observação </h5>
O programa não está padronizando as entradas entre 0 e 1.
