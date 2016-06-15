using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    class Aux
    {
        /* print output schema */
        public static void printschema(DataColumnCollection columns)
        {
            StringBuilder sb = new StringBuilder();

            /* print out each column name tab delimited */
            foreach (DataColumn c in columns)
            {
                sb.Append(c.ColumnName);
                sb.Append("\t");
            }

            Console.WriteLine(sb.ToString());
        }

        /* print tuple */
        public static void printrow(DataRow row)
        {
            /* prints the row, each column tab delimited */

            StringBuilder sb = new StringBuilder();

            Object[] obs = null;
            obs = row.ItemArray;

            foreach (object o in obs)
            {
                sb.Append(o.ToString());
                sb.Append("\t");
            }

            Console.WriteLine(sb.ToString());
        }

        /* print aggregate updates */
        public static void printUpdates(DataTable table)
        {
            // just do stuff.
            Console.WriteLine("Aggregate Update:");

            Aux.printschema(table.Columns);

            foreach (DataRow dr in table.Rows)
                Aux.printrow(dr);            
        }

        /* print query selection menu */
        public static List<string> printMenu()
        {
            /* prints implemented queries */
            List<string> items = new List<string>();
           
            items.Add("Query 1: select * from customer;\n");
            items.Add("Query 2: select account_number from account where balance between 700 and 900;\n");
            items.Add("Query 3: select customer_name from customer where customer_street like '%Hill';\n");
            items.Add("Query 4: select distinct customer_name from customer where customer_street like '%Hill';\n");
            items.Add("Query 5: select * from loan order by amount desc, loan_number asc;\n");
            items.Add("Query 6: select count(*) from customer;\n");
            items.Add("Query 7: select branch_name, avg(balance) from account group by branch_name;\n");
            items.Add("Query 8: select branch_city, sum(assets) as total_assets from branch group by branch_city order by total_assets desc;");
            items.Add("Query 9: select branch_name, avg(balance) from account group by branch_name having avg(balance) > 700;\n");
            items.Add("Query 10: select branch_name, count(distinct customer_name) from depositor, account where depositor.account_number = account.account_number group by branch_name;\n");                        
            items.Add("Query 11: select distinct customer.customer_name, customer_city from borrower, customer where borrower.customer_name = customer.customer_name;\n");
            items.Add("Query 12: select distinct T.branch_name from branch T, branch S where T.assets > S.assets and S.branch_city = 'Brooklyn';\n");
            items.Add("Query 13: select distinct C.customer_name, customer_city from customer C, borrower B, loan L where C.customer_name = B.customer_name and B.loan_number = L.loan_number and branch_name = 'Perryridge';\n");
            items.Add("Query 14: select branch_name from branch where assets > ALL (select assets from branch where branch_city = 'Brooklyn');\n");
            items.Add("Query 15: select distinct customer_name from borrower, loan, branch where borrower.loan_number = loan.loan_number and loan.branch_name = 'Perryridge' order by borrower.customer_name;\n");

            return items;
        }

        /* prints whatever you want */
        public static void print(string whateveryouwant)
        {
            Console.WriteLine(whateveryouwant);
        }
    }
}
