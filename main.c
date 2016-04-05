#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: \n", (const char*)data);
    
    for(i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    
    return 0;
}

int main(int argc, char* argv[])
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char nameDatabase[100] = "Department.db";
    
    rc = sqlite3_open(nameDatabase, &db);
    
    const char* data = "Callback function called";
    
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stdout, "Opened database successfully\n");
    }
    
    int operation;
    int stop = 0;
    
    while(stop == 0)
    {
        printf("Choose operation:\n1)operation SELECT\n2)operation INSERT\n3)operation DELETE\n4)parameterized querie\n5)display photo into file\n6)transaction insert\n7)autocommit\n8)stop\n");
        
        scanf("%d", &operation);
        
        if(operation == 1)//SELECT
        {
            int param = 0;
            char s[40];
            printf("Choose parameter:\n1 - id\n2 - lastname\n3 - country\n4 - view all table\n");
            scanf("%d", &param);
            
            if(param ==  1)
            {
                printf("Input id:\n");
                scanf("%s", s);
                char sql[500] = "SELECT * from department where id=";
                strcat(sql, s);
                strcat(sql, ";");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            
            if(param ==  2)
            {
                printf("Input lastname:\n");
                scanf("%s", s);
                char sql[500] = "SELECT * from department where lastname = '";
                strcat(sql, s);
                strcat(sql, "';");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            
            if(param ==  3)
            {
                printf("Input country:\n");
                scanf("%s", s);
                char sql[500] = "SELECT * from department where country = '";
                strcat(sql, s);
                strcat(sql, "';");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            
            if(param ==  4)
            {
                char sql[500] = "SELECT * from department;";
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
            
            continue;
        }
        if(operation == 2)//INSERT
        {
            char s[40];
        
            char sql[500] = "INSERT INTO department (id, firstname, secondname, lastname, date_of_birth, town_of_birth, country_of_birth, addres, office, current_position, date_of_admission) values (";
        
            printf("Input values to insert:\n");
            
            printf("id: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, ", '");
            printf("firstname: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("secondname: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("lastname: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("date_of_birth: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("town_of_birth: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("country_of_birth: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("address: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("office: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "', '");
            printf("current_position");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, ", ");
            printf("date_of_admission: ");
            scanf("%s", s);
            strcat(sql, s);
            strcat(sql, "');");
            printf("\n");
        
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Records created successfully\n");
            }
            
            continue;
        }
        if(operation == 3)//DELETE
        {
            char id[100];
            
            printf("Input id: ");
            scanf("%s", id);
            
            char sql[500] = "DELETE from department where id = ";
            
            strcat(sql, id);
            strcat(sql, ";");
        
            rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
            
            continue;
        }
        if(operation == 4)//parameterized querie
        {
            int p = 0;
            printf("Choose parameter:\n1 - id\n2 - firstname\n3 - secondname\n4 - lastname\n");
            scanf("%d", &p);
            
            char paramValue[50];
            printf("Input value of parameter:\n");
            scanf("%s", paramValue);
            
            if(p == 1)
            {
                char sql[500] = "SELECT * from department where id = ";
                strcat(sql, paramValue);
                strcat(sql, ";");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            if(p == 2)
            {
                char sql[500] = "SELECT * from department where firstname = '";
                strcat(sql, paramValue);
                strcat(sql, "';");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            if(p == 3)
            {
                char sql[500] = "SELECT * from department where secondname = '";
                strcat(sql, paramValue);
                strcat(sql, "';");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            if(p == 4)
            {
                char sql[500] = "SELECT * from department where lastname = '";
                strcat(sql, paramValue);
                strcat(sql, "';");
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
            }
            
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
            
            continue;
        }
        if(operation == 5)//display photo into file
        {
            FILE *fp = fopen("photoFile.jpg", "wb");
            
            char id[100];
            
            printf("Input id: ");
            scanf("%s", id);
            
            char sql[500] = "SELECT photo from department where id = ";
            strcat(sql, id);
            strcat(sql, ";");
            
            sqlite3_stmt *pStmt;
            
            rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
            
            if( rc != SQLITE_OK )
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "Operation done successfully\n");
            }
            
            rc = sqlite3_step(pStmt);
            
            int bytes = 0;
            
            if(rc == SQLITE_ROW)
            {
                bytes = sqlite3_column_bytes(pStmt, 0);
            }
            
            fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);
            
            if(ferror(fp))
            {
                fprintf(stderr, "fwrite () failed\n");
                return 1;
            }
            
            int r = fclose(fp);
            
            if(r == EOF)
            {
                fprintf(stderr, "Cannot close file handler\n");
            }
            
            rc = sqlite3_finalize(pStmt);
            
            continue;
        }
        if (operation == 6)//transaction insert
        {
            char sql[500] = "BEGIN TRANSACTION; INSERT INTO department (id, firstname, secondname, lastname, date_of_birth, town_of_birth, country_of_birth, addres, office, current_position, date_of_admission) values (";
            
            char buf[50];
            
            fprintf(stdout, "Enter id: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, ", '");
            fprintf(stdout, "Enter firstname: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter secondname: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter lastname: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter date_of_birth: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter town_of_birth: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter country_of_birth: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter addres: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter office: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter current_position: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "', '");
            fprintf(stdout, "Enter date_of_admission: ");
            scanf("%s", buf);
            strcat(sql, buf);
            strcat(sql, "');COMMIT;");
            
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
            
            if(rc != SQLITE_OK)
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }
            else
            {
                fprintf(stdout, "End of inserting.\n");
            }
            
            continue;
        }
        if (operation == 7)//autocommit
        {
            fprintf(stdout, "By default, SQLite version 3 operates in autocommit mode.\n");
            printf("Autocommit: %d\n", sqlite3_get_autocommit(db));
            continue;
        }
        if(operation == 8)//stop
        {
            stop = 1;
        }
    }
    sqlite3_close(db);
}