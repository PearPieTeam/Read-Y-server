//
// Created by xRoBoTx on 22.02.2020.
//

#ifndef SERVERBACKEND_DATABASECONTROLLER_H
#define SERVERBACKEND_DATABASECONTROLLER_H

namespace ControllerDB {

    pqxx::connection* chatDB = new pqxx::connection("dbname=Chat user=Admin password=228995 host=127.0.0.1 port=5432");

    pqxx::work* chatDBWork = new pqxx::work(*chatDB);

}

#endif //SERVERBACKEND_DATABASECONTROLLER_H
