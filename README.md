# SATisfability Problem
9th semestr, MIPT base chair generalize programming course

## Task 1, 3-SAT in partially compile time

In Russian:

* Вход: CNF известная на этапе компиляции:
  ```python
  (v1 or v2 or not v3) and (v2 or v3 or not v1)
  ```
  Может содержать от 2 до 10000 переменных `v1, v2, .... v10000`
Закодирована триплетами конъюнктов `(1, 2, -3), (2, 3, -1)`. Отрицание кодирует переменную с отрицанием.
Может содержать до 100000 триплетов.
По сути речь о массиве фиксированной длины из структур или кортежей по три целых числа.

* Выход: любой набор значений переменных при котором она true или ошибка если такого набора нет. 

Задача NP-сложная. Формула известна во время компиляции.
Необходимо получить чисто runtime решение, получить чисто compile-time решение и сделать гибридное решение когда какие-то структуры данных вы строите во время компиляции и этим ускоряете исполнение.

Критерий сдачи: продемонстрировать что гибридное решение лучше чем оба чистых решения.

## Task 1, Results

In Russian:

* Получен график зависимости времени исполнения/компиляции программы от размеров поданной CNF.

![img](https://github.com/uslsteen/sat_solver/blob/main/pics/perfomance_stats.png)
* Отметим, что при числе триплетов CNF $N> 70$ compile time реализация перестала собираться
* Runtime и hybrid реализация собирались исполнялись за время, меньшеe 1 ms, при $N \leq 70$
* Несмотря на cравнительно небольшой выбор набор тестов, видно, что hybrid реализация при $N > 70$ заметно быстрее runtime реализации.

## Build

- [Modules CMake tutorial without CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API variable](https://www.kitware.com/import-cmake-the-experiment-is-over/)

* Configure CMake from the root of the sources tree:
```bash
mkdir build/

CXX=<path/to/clang++-17> CC=<path/to/clang-17> <path/to/cmake-3.28> -B build/ \
                                               -GNinja \
                                               -DCMAKE_MAKE_PROGRAM=<path/to/ninja>\
                                               -S . \
                                               -DCMAKE_BUILD_TYPE=Release \
                                               -DBUILD_TESTS=ON
```

* Run build:

```bash
cd build/
<path/to/cmake-3.28> --build build/ --config Release -j ${JOBS}
```

Additionally suggest set varialbe ```CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS```

## Tests

- Run Unit Tests

```bash
ctest -C ${BUILD_TYPE} -VV -j ${JOBS} -L unit
```
