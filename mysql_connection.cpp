#include <mysql_driver.h>
#include <mysql_connection.h>

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    try {
        // Create a MySQL driver object
        driver = sql::mysql::get_mysql_driver_instance();

        // Create a connection
        con = driver->connect("tcp://127.0.0.1:3306", "username", "password");

        // Connect to the "testdb" database
        con->setSchema("testdb");

        // Execute a simple query
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM testtable");

        // Display the results
        while (res->next()) {
            std::cout << "Message: " << res->getString("message") << std::endl;
        }

        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return 0;
}
