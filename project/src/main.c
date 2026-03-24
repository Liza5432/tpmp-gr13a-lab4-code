#include "../includes/db.h"

int main(void) {
    sqlite3 *db;
    
    if (sqlite3_open("green.db", &db) != SQLITE_OK) {
        return 1;
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    Create_Tables(db);

    sqlite3_exec(db, "DELETE FROM orders;", 0, 0, 0);
    sqlite3_exec(db, "DELETE FROM composition_items;", 0, 0, 0);
    sqlite3_exec(db, "DELETE FROM compositions;", 0, 0, 0);
    sqlite3_exec(db, "DELETE FROM users;", 0, 0, 0);
    sqlite3_exec(db, "DELETE FROM flowers;", 0, 0, 0);

    Insert_Flower(db, "роза", "красная", 100.0);
    Insert_Flower(db, "лилия", "белая", 200.0);

    Safe_Price_Update(db, 1, 160.0);
    Safe_Price_Update(db, 1, 105.0);

    sqlite3_exec(db, "INSERT INTO compositions (composition_id, name) VALUES (1, 'весенний микс');", 0, 0, 0);
    sqlite3_exec(db, "INSERT INTO composition_items (composition_id, flower_id, quantity) VALUES (1, 1, 5);", 0, 0, 0);
    sqlite3_exec(db, "INSERT INTO users (user_id, username, password, role) VALUES (1, 'лиза', '123', 'клиент');", 0, 0, 0);

    Add_Order_Calc(db, "2026-03-24", "2026-03-25", 1, 1, 1);

    Reports_Select(db);
    Search_By_Date(db, "2026-03-24");

    Delete_Order_By_Id(db, 1);

    sqlite3_close(db);
    return 0;
}