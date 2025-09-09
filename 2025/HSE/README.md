# Семинар 1
## Задача 0
Вычислить префикс функцию строки "abacaba", вспомнить алгоритм Кнута-Морриса-Пратта

<details>
<summary>Решение</summary>
Префис функция: 0 0 1 0 1 2 3

Пусть хотим найти все вхождения $p$ в $t$, тогда:
* склеим $p#t$, # - символ которого нет в $p$ и $t$.
* вычислим $\phi(p#t)
* Ищем позиции, где $\phi_i = |p|$
* Время работы алгоритма $\mathcal{O}(|p|+|t|)$
* В варианте, когда просто склеиваем строки потребление памяти также $\mathcal{O}(|p|+|t|)$.
</details>

## Задача 1
Реализовать алгоритм Кнута-Морриса-Пратта, какие тесты вы бы написали?

<details>
<summary>Решение</summary>
    
```
#include <iostream>
#include <vector>
#include <cassert>

std::vector<size_t> CalculatePreffixFunction(const std::string& text) {
    size_t n = text.length(); 
    std::vector<size_t> preffix_function(n, 0); 

    size_t len = 0;
    size_t i = 1;

    while (i < n) {
        if (text[i] == text[len]) {
            len++;
            preffix_function[i] = len;
            i++;
        } else if (len != 0) {
            len = preffix_function[len - 1];
        } else {
            preffix_function[i] = 0;
            i++;
        }
    }

    return preffix_function;
}

std::vector<size_t> FindAllOccurences(const std::string& pattern, const std::string& text) {
    std::string combined = pattern + "#" + text;
    std::vector<size_t> pi = CalculatePreffixFunction(combined);
    std::vector<size_t> result;
    
    size_t m = pattern.size();
    for (size_t i = m + 1; i < combined.size(); ++i) {
        if (pi[i] == m) {
            result.push_back(i - 2 * m);
        }
    }
    return result;
}

int main()
{
    { 
        std::vector<size_t> expected = {0, 0, 1, 0, 1, 2, 3};
        assert(CalculatePreffixFunction("abacaba") == expected);
    }

    {
        std::vector<size_t> expected = {};
        assert(CalculatePreffixFunction("") == expected);
    }

    {
        std::vector<size_t> expected = {0,1,2,3,4};
        assert(CalculatePreffixFunction("aaaaa") == expected);
    }
    return 0;
}
```
</details>

## Задача 2
Можно ли в КМП алгоритме обойтись $\mathcal{O}(|p|) памяти?

<details>
<summary>Решение</summary>
Да, можно, значение префикс функции в алгоритме КМП никогда не превышает $|p|$ в силу наличия символа #.
</details>

## Задача 3
Визуализировать КМП в виде автомата для паттерна abacaba(граф со стрелочками) и при помощи автомата найти все вхождения паттерна в текст abadcabacabacaba.

<details>
<summary>Решение</summary>
Начальный переход:
$$
\delta(0, a) = 
\begin{cases}
0, a \neq b_1\\
1, a = b_1
\end{cases}
$$
Далее:
$$
\delta(j, a) = 
\begin{cases}
\delta(\pi(j), a), a \neq b_{j + 1}\\
j + 1, a = b_{j + 1}
\end{cases}
$$
Вершина $m$ -- терминальная.
Полученный автомат будет принимать все строки вида $*w$, что нам и нужно для поиска вхождений.

Также заметим, что каждый раз мы идем в максимальный <<суффикс текущего состояния>>, который можно прочесть в автомате.


**Для любознательных, формально что такое ДКА:**
Детерминированный конечный автомат $\mathcal{A}=(\Sigma, Q, q_0, \delta, F)$, где:
* $\Sigma$ - алфавит, конечное множество
* $Q$ - конечное множество состояний
* $q_0$ - начальное состояние
* $\delta: Q \times \Sigma \to Q$ - функция переходов (пример: $q \in Q, a \in \Sigma $ -- следующее состояние $\delta(q, a)$)
* $F \subseteq Q$ - множество принимаемых значений.

Для всякой входной строки $w = a_1, \ldots, a_l$, где $l \geq 0$ и $a_1,\ldots,al \in \Sigma$, вычисление -- по- следовательность состояний $p_0, p_1, \ldots, p_l$, где $p_0 = q_0$, и всякое следующее состояние $p_i$, где $i \in \{1, \ldots , l\}$, однозначно определено как $p_i = \delta(p_{i−1}, a_i)$.
    
Строка принимается, если последнее состояние принадлежит множеству F, иначе отвергается.
</details>

## Задача 4

