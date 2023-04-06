#include<iostream>
#include<mysql.h>
using namespace std;
int main()
{
    cout<<"1"<<endl;
    mysql_library_init(0, NULL, NULL);
    MYSQL *db = mysql_init(NULL);
        cout<<"2"<<endl;
    if(mysql_real_connect(db,"localhost","root","123","testdb",0,NULL,0))
    {
        cout<<"connected"<<endl;
        int is_succeed = mysql_query(db,"select * from students");
        MYSQL_RES *result = mysql_store_result(db);
        if(result)
        {

            int num = mysql_num_rows(result);
            cout<<"testdb has num:"<<num<<endl;
            MYSQL_ROW row = mysql_fetch_row(result);
            int columns = mysql_field_count(db);
            MYSQL_FIELD *columns_info = mysql_fetch_fields(result);
            for(int i=0;i<columns;i++)
            {
                cout<<i+1<<"th's name is:"<<columns_info[i].name<<endl;
            }
            while(row)
            {
                unsigned long *column_size = mysql_fetch_lengths(result);
                for(int i=0;i<columns;i++)
                {
                    cout<<column_size[i]<<"  "<<(column_size[i] ? row[i]:"NULL");
                    cout<<"  ";
                }
                cout<<endl;
                row = mysql_fetch_row(result);
            }
            if(mysql_errno(db))
                cout<<mysql_error(db)<<endl;
            else
                cout<<"everything in right"<<endl;
        }
        mysql_free_result(result);
        mysql_query(db,"update students set score=0");
        int affected_num =  mysql_affected_rows(db);
        cout<<"affected row is:"<<affected_num<<endl;
        mysql_library_end();
    }
     cout<<"3"<<endl;
    return 0;
}