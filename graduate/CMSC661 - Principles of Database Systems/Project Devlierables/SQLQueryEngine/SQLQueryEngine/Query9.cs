using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query9
    {
        public Query9()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void passForm(Form1 form, DataTable resultTable)
        {            
            m_form = form;
            m_resultTable = resultTable;
        }

        public void exec()
        {
            DataTable dt = new DataTable("temp");
            List<string> fields = new List<string>();

            scan s = new scan("account");

            project p = new project(fields);

            avg a = new avg("balance", "branch_name");

            select se = new select("avg(balance)", "gt", 700);

            s.open();

            dt = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            a.loadFormAcces(m_form, m_resultTable);

            a.open(dt);

            dt.Clear();

            // because might be returning different columns
            dt = a.cloneSchema();

            while (a.hasMore())
            {
                dt.ImportRow(a.next());
            }

            a.close();

            se.open(dt);

            dt.Clear();

            while (se.hasMore())
            {
                dt.ImportRow(se.next());
            }

            se.close();

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

            m_stats.Add("count.query9", resultCnt);

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
                statBuilder.Append("distinct.query9." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(branch_name, avg(balance))");
            expression.Add("\t\t|");
            expression.Add("\tselect(avg(balance), > 700)");
            expression.Add("\t\t|");
            expression.Add("\tavg(branch_name, balance)");
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
        private Form1 m_form;
        private DataTable m_resultTable;
        private DataTable m_outDT;
    }
}
