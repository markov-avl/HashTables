# Предметная область
Имеется холодильник, в котором хранятся продукты. Продукты имеют следующие данные:
1. Название продукта;
2. Дата покупки;
3. Срок годности;
4. Штрих код.

# Цель
Создать класс **холодильник** со следующей структурой:
1. Поля:
   - размер таблицы;
   - количество заполненных ячеек таблицы;
   - таблица.
2. Конструктор;
3. Деструктор;
4. Хеш-функция №1 (ключ) - *хеширует запись по первичному ключу* -> **индекс**;
5. Хеш-функция №2 (индекс) - *устраняет коллизии* -> **индекс**;
6. Add (запись продукта) - *добавляет запись* -> **целое число**;
7. Remove (запись продукта) - *удаляет запись* -> **целое число**;
8. Find (запись продукта) - *находит ячейку с данной записью* -> **целое число**;
9. Print (перегрузка потока вывода <<) -> **поток вывода**;

# Вариант задания
1. ***Статическая*** хеш-таблица;
2. ***Квадратичный поиск*** как метод устранения коллизий;
3. Ячейки могут иметь состояние "***свободно***" или "***занято***";
4. Хеширование производится по ***названию продукта*** и ***дате покупки***.

# Структура отчета
1. Описание алгоритма;
2. Спецификации;
3. Тесты.