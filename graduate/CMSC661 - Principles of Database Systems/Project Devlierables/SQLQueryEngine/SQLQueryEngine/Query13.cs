using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query13
    {
        public Query13()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("tempMain");
            DataTable dto = new DataTable("tempSecondary");

            List<string> fields = new List<string>();

            fields.Add("C.customer_name");
            fields.Add("customer_city");

            project p = new project(fields);
            distinct d = new distinct(fields);

            scan s1 = new scan("customer");
            scan s2 = new scan("borrower");
            scan s3 = new scan("loan");

            renamefield borRen = new renamefield("customer_name", "B.customer_name");
            renamefield borRen2 = new renamefield("loan_number", "B.loan_number");
            renamefield cusRen = new renamefield("customer_name", "C.customer_name");
            renamefield loaRen = new renamefield("loan_number", "L.loan_number");

            select sloan = new select("branch_name", "eq", "Perryridge");

            List<string> join1 = new List<string>();
            join1.Add("B.loan_number");
            join1.Add("eq");
            join1.Add("L.loan_number");
            join1.Add("str");

            List<string> join2 = new List<string>();
            join2.Add("C.customer_name");
            join2.Add("eq");
            join2.Add("B.customer_name");
            join2.Add("str");

            join j1 = new join(join1);
            join j2 = new join(join2);

            /* Read in borrower */
            s2.open();

            dt = s2.cloneSchema();

            while (s2.hasMore())
            {
                dt.ImportRow(s2.next());
            }

            s2.close();

            /* read in loan */
            s3.open();

            dto = s3.cloneSchema();

            while (s3.hasMore())
            {
                dto.ImportRow(s3.next());
            }

            s3.close();

            /* run select against loan */
            sloan.open(dto);

            dto.Clear();

            while (sloan.hasMore())
            {
                dto.ImportRow(sloan.next());
            }

            sloan.close();

            /* rename borrow and loan for join */
            loaRen.open(dto);

            borRen.open(dt);
            borRen2.open(dt);

            j1.open(dt, dto);

            // clean temporary storage
            dt.Clear();
            dto.Clear();

            /* obtain result of join */
            dto = j1.cloneSchema();

            while (j1.hasMore())
            {
                dto.ImportRow(j1.next());
            }

            j1.close();

            /* read in customer relation */
            s1.open();

            dt = s1.cloneSchema();

            while (s1.hasMore())
            {
                dt.ImportRow(s1.next());
            }

            s1.close();

            // rename customer column
            cusRen.open(dt);

            /* join customer with result of previous join */
            j2.open(dt, dto);

            dt.Clear();
            dto.Clear();

            dt = j2.cloneSchema();

            while (j2.hasMore())
            {
                dt.ImportRow(j2.next());
            }

            j2.close();

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

            m_stats.Add("count.query13", resultCnt);

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
                statBuilder.Append("distinct.query13." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("project(C.customer_name, customer_city)");
            expression.Add("\t|");
            expression.Add("distinct(C.customer_name, customer_city)");
            expression.Add("\t|");
            expression.Add("natural-join(C.customer_name = B.customer_name)");
            expression.Add("\t/\t\t\t\\");
            expression.Add("customer_name->C.customer_name\tnatural-join(B.loan_number = L.loan_number)");
            expression.Add("\t|\t\t\t\t/\t\t\\");
            expression.Add("\tcustomer\t\t\tloan_number->B.loan_number\tloan_number->L.loan_number");
            expression.Add("\t\t\t\t\t|\t\t|");
            expression.Add("\t\tcustomer_name->B.customer_name\t\tselect(branch_name, eq 'Perryridge')");
            expression.Add("\t\t\t\t\t|\t\t|");
            expression.Add("\t\t\t\t\tborrower\t\tloan");

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
