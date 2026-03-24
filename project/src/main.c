#include "../includes/db.h"

int main(void) {
    sqlite3 *db;
    
    if (sqlite3_open("green.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Не удалось открыть БД: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    Create_Tables(db);

    printf("\nДобавление цветка\n");
    Insert_Flower(db, "Орхидея", "Тропическая", 500.0);
    printf("Содержимое таблицы flowers:\n");
    sqlite3_exec(db, "SELECT * FROM flowers;", callback, 0, 0);

    printf("\nТекущие отчеты\n");
    Reports_Select(db);

    printf("\nПоиск по дате\n");
    Search_By_Date(db, "2026-03-24");

    printf("\nОформление заказа\n");
    Add_Order_Calc(db, "2026-03-24", "2026-03-25", 1, 1, 1);
    printf("Содержимое таблицы orders:\n");
    sqlite3_exec(db, "SELECT * FROM orders;", callback, 0, 0);

    printf("\nЗащита цены (Обновление)\n");
    Safe_Price_Update(db, 1, 550.0);
    printf("Таблица flowers после обновления цены:\n");
    sqlite3_exec(db, "SELECT * FROM flowers WHERE flower_id = 1;", callback, 0, 0);

    printf("\nУдаление заказа\n");
    Delete_Order_By_Id(db, 1);
    printf("Таблица orders после удаления ID 1:\n");
    sqlite3_exec(db, "SELECT * FROM orders;", callback, 0, 0);

    sqlite3_close(db);
    
    return 0;
}