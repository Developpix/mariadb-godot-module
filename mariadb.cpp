/* mariadb.cpp */

#include "mariadb.h"

using namespace std;

int MariaDB::initialize(String hostname, String username, String password, int port) {
    
    if(mysql_real_connect(m_con, hostname.utf8().get_data(), username.utf8().get_data(), password.utf8().get_data(), NULL, port, NULL, NULL) != NULL)
        return 0;
    else
        return 1;
    
}

int MariaDB::select_database(String dbname) {
    
    return mysql_select_db(m_con, dbname.utf8().get_data());
    
}

Array MariaDB::execute(String request) {

    Array arr = Array();
        
    if(!mysql_query(m_con, request.utf8().get_data())) {
        
        MYSQL_RES *res = mysql_store_result(m_con);
        
        Array columnsNames = Array();
        
        my_ulonglong nbRows = mysql_num_rows(res);
        unsigned int nbColumns = mysql_field_count(m_con);
        
        for(int c = 0; c < nbColumns; c++) {
            
            MYSQL_FIELD *column = mysql_fetch_field(res);
            columnsNames.append(String(column->name));
            
        }
        
        for(int i = 0; i < nbRows; i++) {
            
            Dictionary dict = Dictionary();
            MYSQL_ROW row = mysql_fetch_row(res);
            
            for(int j = 0; j < nbColumns; j++) {
                
                dict[columnsNames[j]] = String(row[j]);
                dict[j] = String(row[j]);
        
                
            }
            
            arr.append(dict);
            
        }
        
        mysql_free_result(res);
        
        return arr;
        
    } else {
     
        return arr;
        
    }
    
}

int MariaDB::update(String request) {

    return mysql_query(m_con, request.utf8().get_data());
    
}

void MariaDB::_bind_methods() {

    ClassDB::bind_method(D_METHOD("initialize", "hostname", "username", "password", "port"), &MariaDB::initialize);
    ClassDB::bind_method(D_METHOD("select_database", "dbname"), &MariaDB::select_database);
    ClassDB::bind_method(D_METHOD("execute", "request"), &MariaDB::execute);
    ClassDB::bind_method(D_METHOD("update", "request"), &MariaDB::update);
    
}

MariaDB::MariaDB() {
    m_con = mysql_init(NULL);
}

MariaDB::~MariaDB() {
    mysql_close(m_con);
}
