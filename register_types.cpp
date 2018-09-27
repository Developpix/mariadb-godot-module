/* register_types.cpp */

#include "register_types.h"
#include "class_db.h"

#include "mariadb.h"

void register_mariadb_types() {

        ClassDB::register_class<MariaDB>();
}

void unregister_mariadb_types() {}
