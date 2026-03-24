#include "../includes/db.h"

int main(void) {
    sqlite3 *db;
    
    
    if (sqlite3_open("green.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Не удалось открыть БД: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    Create_Tables(db);

    Insert_Flower(db, "Орхидея", "Тропическая", 500.0);

    Reports_Select(db);

    Search_By_Date(db, "2026-03-24");

    
    Add_Order_Calc(db, "2026-03-24", "2026-03-25", 1, 1, 1);


    printf("\nЗащита цены: \n");
    Safe_Price_Update(db, 1, 160.0);

    Delete_Order_By_Id(db, 1);


    sqlite3_close(db);
    
    return 0;
}
