using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query14
    {
        public Query14()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable branchData = new DataTable("temp");
            DataTable dt = new DataTable("temp");

            List<string> subfields = new List<string>();
            List<string> fields = new List<string>();

            subfields.Add("assets");
            fields.Add("branch_name");

            scan s = new scan("branch");

            project subp = new project(subfields);
            project p = new project(fields);
            
            select s1 = new select("branch_city", "eq", "Brooklyn");
            
            s.open();

            branchData = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                branchData.ImportRow(s.next());
            }

            s.close();

            /* execute sub query */
            dt = branchData.Copy();
            
            s1.open(dt);
            
            dt.Clear();

            while (s1.hasMore())
            {
                dt.ImportRow(s1.next());
            }

            s1.close();

            subp.open(dt);

            dt.Clear();

            List<int> values = new List<int>();

            while (subp.hasMore())
            {
                DataRow dr = subp.next();
                Object[] obs = dr.ItemArray;

                values.Add((int)obs[0]);
            }

            subp.close();

            int maximumvalue = values.Max();

            selectALL sAll = new selectALL("assets", "gt", maximumvalue);

            sAll.open(branchData);

            dt = branchData.Clone();

            while (sAll.hasMore())
            {
                dt.ImportRow(sAll.next());
            }

            sAll.close();

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

            m_stats.Add("count.query14", resultCnt);

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
                statBuilder.Append("distinct.query14." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("project(branch_name)");
            expression.Add("\t|");
            expression.Add("select(assets, > maxvalue)");
            expression.Add("/\t\\");
            expression.Add("branch\tmax(assets)->maxvalue");
            expression.Add("\t\t|");
            expression.Add("\tselect(branch_city, eq 'Brooklyn')");
            expression.Add("\t\t|");
            expression.Add("\t\tbranch");

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

