DROP TABLE OrderLines;
DROP TABLE Batches;

PRAGMA foreign_keys = ON; -- Включение поддержки проверки целостности по внешнему ключу

CREATE TABLE Batches (
    GUID VCHAR PRIMARY KEY, -- GUID заказа
    Sku VCHAR NOT NULL, -- Единица складского учета
    AvailableQuantity INTEGER NOT NULL CHECK(AvailableQuantity >= 0), -- Доступное кол-во товара в заказе
    AllocateQuantity INTEGER NOT NULL CHECK(AllocateQuantity >= 0), -- Занятое кол-во товара в заказе
    DeliveryDate DATE -- Дата доставки
);

CREATE TABLE OrderLines (
    OrderID VCHAR PRIMARY KEY, -- ID заказа (по книге vchar, так то можно сделать integer)
    Sku VCHAR NOT NULL, -- Единица складского учета (дублирование, плохо кончено, однако так удобне конвертировать строки в объекты)
    Quantity INTEGER NOT NULL CHECK(Quantity > 0), -- Кол-во заказа в этой позиции
    ParrentGUID VCHAR  NOT NULL, -- Родительский заказ (размещение)
    FOREIGN KEY (ParrentGUID)  REFERENCES Batches (GUID) -- ограничение по внешнему ключу
    ON DELETE CASCADE -- Что делать при обновлении записи в Batches
    ON UPDATE CASCADE -- Что делать при удалении записи в Batches
);