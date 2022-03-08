1. Добавим в algorithm.c реализацию функции max. Тогда произойдёт конфликт multiple definition

2. Добавим строчку `c = min(a, a)` внутрь `doComputation`. Поскольку функции `min` не существует, получим undefined reference