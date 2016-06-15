using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query6
    {
        public Query6()
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

            scan s = new scan("customer");

            project p = new project(fields);

            count c = new count("*", string.Empty, false);
            
            s.open();

            dt = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            c.loadFormAcces(m_form, m_resultTable);

            c.open(dt);

            dt.Clear();

            // because might be returning different columns
            dt = c.cloneSchema();

            while (c.hasMore())
            {
                dt.ImportRow(c.next());
            }

            c.close(); 

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

            m_stats.Add("count.query6", resultCnt);

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
                statBuilder.Append("distinct.query6." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(count(*))");
            expression.Add("\t\t|");
            expression.Add("\tcount(*)");
            expression.Add("\t\t|");
            expression.Add("\t\tcustomer");

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
