## Задание 6.3

Доработать решение задачи 2.3 (калькулятор) так, чтобы
функции загружались из динамических библиотек. В одной библиотеке
находится одна функция. При запуске программы считывается каталог с
библиотеками и загружаются найденные функции.

---

### Сборка проекта:

- make all - все модули
- make libs - для сборки динамических библиотек

### Работа программы:
Библиотеки для всех функций подгружаются в main_menu(). Функции находятся в массиве указателей и вызываются при необходимости. В остальном, не отличается от 2.3

