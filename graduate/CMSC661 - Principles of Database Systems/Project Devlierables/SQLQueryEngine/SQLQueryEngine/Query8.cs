using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query8
    {
        public Query8()
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
            List<string> empty = new List<string>();

            empty.Add("branch_city");
            empty.Add("total_assets");

            scan s = new scan("branch");
            project p = new project(empty);
            sum summation = new sum("assets", "branch_city");
            renamefield totalassets = new renamefield("sum(assets)", "total_assets");
            orderby assetOrdering = new orderby("total_assets", "desc", "int");

            s.open();

            dt = s.cloneSchema();

            /* get all tuples from SCAN */
            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            summation.loadFormAcces(m_form, m_resultTable);

            /* run sum aggregation */
            summation.open(dt);

            dt.Clear();

            dt = summation.cloneSchema();

            while (summation.hasMore())
            {
                dt.ImportRow(summation.next());
            }

            summation.close();

            totalassets.open(dt);

            assetOrdering.open(dt);

            dt.Clear();

            while (assetOrdering.hasMore())
            {
                dt.ImportRow(assetOrdering.next());
            }

            assetOrdering.close();

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

            m_stats.Add("count.query8", resultCnt);

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
                statBuilder.Append("distinct.query8." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\torderby(total_assets, desc)");
            expression.Add("\t\t|");
            expression.Add("\tproject(branch_city, total_assets)");
            expression.Add("\t\t|");
            expression.Add("\tsum(branch_city, assets->total_assets)");
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
        private Form1 m_form;
        private DataTable m_resultTable;
        private DataTable m_outDT;
    }
}
