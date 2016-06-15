using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query11
    {
        public Query11()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("borrower");
            DataTable dto = new DataTable("customer");
            List<string> fields = new List<string>();

            fields.Add("customer.customer_name");
            fields.Add("customer_city");

            scan sL = new scan("borrower");
            scan sR = new scan("customer");

            project p = new project(fields);

            renamefield rL = new renamefield("customer_name", "borrower.customer_name");
            renamefield rR = new renamefield("customer_name", "customer.customer_name");

            List<string> joinon = new List<string>();
            joinon.Add("borrower.customer_name");
            joinon.Add("eq");
            joinon.Add("customer.customer_name");
            joinon.Add("str");

            join j = new join(joinon);

            distinct d = new distinct(fields);

            /* Read in Borrower */
            sL.open();

            dt = sL.cloneSchema();

            /* get all tuples from SCAN */
            while (sL.hasMore())
            {
                dt.ImportRow(sL.next());
            }

            sL.close();

            rL.open(dt);

            /* Read in Customer */
            sR.open();

            dto = sR.cloneSchema();

            while (sR.hasMore())
            {
                dto.ImportRow(sR.next());
            }

            sR.close();

            rR.open(dto);

            /* compute join */
            j.open(dt, dto);

            dt.Clear();
            dt = j.cloneSchema();

            while (j.hasMore())
            {
                dt.ImportRow(j.next());
            }

            j.close();

            /* add distinct here */
            d.open(dt);

            dt.Clear();

            while (d.hasMore())
            {
                dt.ImportRow(d.next());
            }

            d.close();

            p.open(dt);

            dt.Clear();

            dt = p.cloneSchema();

            while (p.hasMore())
            {
                dt.ImportRow(p.next());
            }

            p.close();

            /* update stats */
            int resultCnt = dt.Rows.Count;

            m_stats.Add("count.query11", resultCnt);

            List<string> distinctCounter = new List<string>();

            /* really inefficient */
            foreach (DataColumn dc in dt.Columns)
            {
                distinctCounter.Clear();

                foreach (DataRow dr in dt.Rows)
                {
                    if (!distinctCounter.Contains(dr[dc.ColumnName].ToString()))
                        distinctCounter.Add(dr[dc.ColumnName].ToString());
                }

                StringBuilder statBuilder = new StringBuilder();
                statBuilder.Append("distinct.query11." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(customer.customer_name, customer_city)");
            expression.Add("\t\t\t|");
            expression.Add("\t\tdistinct(customer.customer_name, customer_city)");
            expression.Add("\t\t\t|");
            expression.Add("\tnatural-join(borrower.customer_name = customer.customer_name)");
            expression.Add("\t\t/\t\t\t\t\t\\");
            expression.Add("\t\t|\t\t\t\t\t|");
            expression.Add("\tcustomer_name->borrower.customer_name\tcustomer_name->customer.customer_name");
            expression.Add("\t\t|\t\t\t\t\t|");
            expression.Add("\t\tborrower\t\t\t\t\tcustomer");

            return expression;
        }

        public Dictionary<string, int> getStats()
        {
            return m_stats;
        }

        public DataTable getResults()
        {
            return m_outDT;
        }
        
        private Dictionary<string, int> m_stats;
        private DataTable m_outDT;
    }
}
