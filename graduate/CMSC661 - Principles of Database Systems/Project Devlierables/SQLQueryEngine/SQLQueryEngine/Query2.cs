using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query2
    {
        public Query2()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("temp");
            List<string> fields = new List<string>();

            fields.Add("account_number");

            scan s = new scan("account");

            project p = new project(fields);

            select s1 = new select("balance", "gte", 700);
            select s2 = new select("balance", "lte", 900);

            s.open();

            dt = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            /* add selects here */
            s1.open(dt);

            /* prepare for new set */
            dt.Clear();

            while (s1.hasMore())
            {
                dt.ImportRow(s1.next());
            }

            s1.close();

            s2.open(dt);

            dt.Clear();

            while (s2.hasMore())
            {
                dt.ImportRow(s2.next());
            }

            s2.close();

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

            m_stats.Add("count.query2", resultCnt);

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
                statBuilder.Append("distinct.query2." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(account_number)");
            expression.Add("\t\t|");
            expression.Add("\tselect(balance, between 700 and 900)");
            expression.Add("\t\t|");
            expression.Add("\t\taccount");

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
