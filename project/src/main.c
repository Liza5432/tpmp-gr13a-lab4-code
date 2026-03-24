#include "../includes/db.h"

int main(void) {
    sqlite3 *db;
    
    if (sqlite3_open("green.db", &db) != SQLITE_OK) {
        return 1;
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    Create_Tables(db);

    Insert_Flower(db, "роза", "красная", 150.0);
    Insert_Flower(db, "лилия", "белая", 200.0);

    Safe_Price_Update(db, 1, 240.0);
    Safe_Price_Update(db, 1, 155.0);

    sqlite3_exec(db, "INSERT OR IGNORE INTO compositions (composition_id, name) VALUES (1, 'классика');", 0, 0, 0);
    sqlite3_exec(db, "INSERT OR IGNORE INTO composition_items (composition_id, flower_id, quantity) VALUES (1, 1, 3);", 0, 0, 0);
    sqlite3_exec(db, "INSERT OR IGNORE INTO users (user_id, username, password, role) VALUES (1, 'лиза', '123', 'админ');", 0, 0, 0);

    Add_Order_Calc(db, "2026-03-24", "2026-03-25", 1, 1, 1);

    Reports_Select(db);
    Search_By_Date(db, "2026-03-24");

    Delete_Order_By_Id(db, 1);

    sqlite3_close(db);
    printf("тестирование завершено\n");
    return 0;
}