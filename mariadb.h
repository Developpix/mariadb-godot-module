/* mariadb.h */
#ifndef MARIADB_H
#define MARIADB_H

#include <stdlib.h>
#include <iostream>

#include "reference.h"

#include <mariadb/mysql.h>

class MariaDB : public Reference {
    GDCLASS(MariaDB, Reference);

protected:
    MYSQL *m_con;
    
    static void _bind_methods();

public:
    int initialize(String hostname, String username, String password, int port);
    int select_database(String dbname);
    Array execute(String request);
    int update(String request);

    MariaDB();
    ~MariaDB();
};

#endif 
