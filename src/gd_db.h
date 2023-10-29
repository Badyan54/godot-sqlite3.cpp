#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <sqlite3.h>

namespace godot {

class SQLiteDB : public Object {
    GDCLASS(SQLiteDB, Object)

private:
    sqlite3 *db;
    String db_name;

protected:
    static void _bind_methods();

public:
    Error open();
    void close();
    void execute_query(const String &query);
    void set_name(const String &dbName);

    SQLiteDB();
    ~SQLiteDB();
};

}

#endif
