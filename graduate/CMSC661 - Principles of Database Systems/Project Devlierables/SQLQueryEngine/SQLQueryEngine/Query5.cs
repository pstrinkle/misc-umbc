using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query5
    {
        public Query5()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("temp");
            List<string> fields = new List<string>();
            
            scan s = new scan("loan");

            project p = new project(fields);
                        
            s.open();

            dt = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            /* add orderby here */            
            orderby orderOutput = new orderby("amount", "desc", "int", "loan_number", "asc", "str");

            orderOutput.open(dt);

            dt.Clear();

            while (orderOutput.hasMore())
            {
                dt.ImportRow(orderOutput.next());
            }

            orderOutput.close();

            p.open(dt);

            /* begin output */
            Aux.printschema(p.columns());

            while (p.hasMore())
            {
                Aux.printrow(p.next());
            }

            p.close();

            /* update stats */
            int resultCnt = dt.Rows.Count;

            m_stats.Add("count.query5", resultCnt);

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
                statBuilder.Append("distinct.query5." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\torderby(amount, desc, loan_number, asc)");
            expression.Add("\t|");
            expression.Add("\tproject(*)");
            expression.Add("\t|");
            expression.Add("\tloan");

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
