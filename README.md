# ASA 24/25 - Projeto 1
**Filipe Oliveira**  
**Número de estudante**: ist1110633

## 📌 Descrição do Projeto   

Este projeto tem como objetivo **desenvolver um algoritmo eficiente** para determinar a **ordem correta da parentetização** de uma sequência de operações de forma a obter um resultado específico.  

---

## 🎯 Definição do Problema  

Dado um operador **⊕**, definido por uma **tabela NxN**, e uma sequência de inteiros, devemos determinar **se é possível posicionar os parêntesis** para obter um valor específico.  

### 📌 **Entrada**  
O programa recebe um ficheiro com:  
1. **Um número `n`** (tamanho do conjunto de inteiros) e **um número `m`** (tamanho da sequência de inteiros).  
2. **Uma tabela `n x n`**, onde o valor na linha `i`, coluna `j` representa o resultado da operação `i ⊕ j`.  
3. **Uma sequência de `m` inteiros** entre `1` e `n`, separados por espaços.  
4. **Um número inteiro**, representando o resultado esperado.  

### 📌 **Saída**  
- Se for possível **parentetizar** a sequência para obter o valor esperado, o programa imprime **`1`** seguido da **parentetização mais à esquerda**.  
- Se **não for possível**, imprime apenas **`0`**.

---

📄 **Nota:** Para mais exemplos e explicações detalhadas, consultar [enunciado-ASA2425P1.pdf](./enunciado-ASA2425P1.pdf)