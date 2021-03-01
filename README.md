# Предметная область
Имеется холодильник, в котором хранятся продукты. Продукты имеют следующие данные:
1. Название продукта;
2. Дата покупки;
3. Срок годности;
4. Штрих код.

# Цель
Создать класс __холодильник__ со следующей структурой:
1. Конструктор;
2. Деструктор;
3. Хеш-функция №1 (код) -> address;
4. Хеш-функция №2 (адрес) -> address;
5. Add (record) -> int;
6. Delete (record) -> boolean/int (код выполнения функции);
7. Search (record) - поиск записи по ключу -> boolean/int (код выполнения функции);
8. Print (перегрузка потока вывода <<);
9. Поля:
    - размер таблицы;
    - количество заполненных ячеек таблицы;
    - таблица.

# Вариант задания:
1. __Статическая__ хеш-таблица;
2. __Квадратичный поиск__ как метод устранения коллизий;
3. Ячейки могут иметь состояние "__свободно__" или "__занято__";
4. __Название продукта__ -> __дата покупки__.

# Структура отчета:
1. Описание алгоритма;
2. Спецификации;
3. Тесты.