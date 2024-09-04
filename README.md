# DDD

Учебный проект по освоению взаимодействия программного кода приложения с СУБД.

## Анализ:

статьи:
* https://habr.com/ru/articles/809831/ - плохая статья, про DDD.

* https://habr.com/ru/companies/otus/articles/713728/ -  про проетирование, про шаблоны (нормальная статья, не хватает UML диаграмм и примера кода на все рассматриваемые шаблоны).

* https://habr.com/ru/companies/otus/articles/715702/ - продолжение прошлой статьи выше в контексте БД.

Первые шаги - DDD,  паттерны UoF, Repository.


DDD (Domain Driven Design) - микросервисная архитектура на базе сущностей предметной области.


https://habr.com/ru/articles/344164/

https://habr.com/ru/articles/672328/

Луковичная архитектура в компоновке backend-приложения и куда в итоге класть маперы???

Bounded context ?
Event storming?

https://vaadin.com/blog/ddd-part-1-strategic-domain-driven-design.


### И так к проекту:

Проект будет состоять из 2 частей - сервер и клиент.

* Для тестирования сервера будем использовать GoogleTests
* Для тестирования СУБД попробую использовать SQLLite (если получится)

Чертовски интересно что такое событийная архитектура?

Боюсь что придётся достать книгу по многопоточности для реализации нормаьных контейнирова и ШИН.

- https://habr.com/ru/articles/324984/ -- работа с chrono, ссылка на библиотеку date
- https://habr.com/ru/articles/509220/ -- хеш-таблицы