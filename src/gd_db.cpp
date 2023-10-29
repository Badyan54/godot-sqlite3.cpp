#include "gd_db.h"
#include <godot_cpp/core/class_db.hpp>
#include "sqlite3.h"

using namespace godot;

void SQLiteDB::_bind_methods() {
    ClassDB::bind_method(D_METHOD("open"), &SQLiteDB::open);
    ClassDB::bind_method(D_METHOD("close"), &SQLiteDB::close);
    ClassDB::bind_method(D_METHOD("execute_query", "query"), &SQLiteDB::execute_query);
    ClassDB::bind_method(D_METHOD("set_name", "dbName"), &SQLiteDB::set_name);
}

SQLiteDB::SQLiteDB() {
    db = nullptr;
}

SQLiteDB::~SQLiteDB() {
    close();
}


Error SQLiteDB::open() {
    int result = sqlite3_open(db_name.utf8().get_data(), &db);
    if (result != SQLITE_OK) {
        return FAILED;
    }
    return OK;
}

void SQLiteDB::set_name(const String &dbName){
    db_name = dbName;

}

void SQLiteDB::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void SQLiteDB::execute_query(const String &query) {
    if (db != nullptr) {
        char *error_message = nullptr;
        int result = sqlite3_exec(db, query.utf8().get_data(), nullptr, nullptr, &error_message);
        if (result != SQLITE_OK) {
            // Handle the error, e.g., by printing the error_message
            // and freeing the error_message memory.
            sqlite3_free(error_message);
        }
    }
}