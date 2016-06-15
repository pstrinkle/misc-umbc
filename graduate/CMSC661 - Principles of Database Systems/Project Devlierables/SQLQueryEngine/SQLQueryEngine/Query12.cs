using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query12
    {
        public Query12()
        {
            /* no code is god's code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("branch T");
            DataTable dto = new DataTable("branch S");
            List<string> fields = new List<string>();

            fields.Add("T.branch_name");            

            scan branch_T = new scan("branch");
            scan branch_S = new scan("branch");

            project p = new project(fields);
            distinct d = new distinct(fields);
                        
            renamefield t_branch_name = new renamefield("branch_name", "T.branch_name");
            renamefield t_assets = new renamefield("assets", "T.assets");
            renamefield s_assets = new renamefield("assets", "S.assets");
            renamefield s_branch_city = new renamefield("branch_city", "S.branch_city");

            select sel_city = new select("S.branch_city", "eq", "Brooklyn");

            List<string> joinon = new List<string>();
            joinon.Add("T.assets");
            joinon.Add("gt");
            joinon.Add("S.assets");
            joinon.Add("int");

            join j = new join(joinon);

            /* read in branch S */
            branch_S.open();

            dt = branch_S.cloneSchema();

            while (branch_S.hasMore())
            {
                dt.ImportRow(branch_S.next());
            }

            branch_S.close();

            /* read in branch T */
            branch_T.open();

            dto = branch_T.cloneSchema();

            while (branch_T.hasMore())
            {
                dto.ImportRow(branch_T.next());
            }

            branch_T.close();

            /* rename fields */
            t_branch_name.open(dto);
            t_assets.open(dto);

            s_branch_city.open(dt);
            s_assets.open(dt);

            /* select S.branch_city eq 'Brooklyn' */
            sel_city.open(dt);

            dt.Clear();

            while (sel_city.hasMore())
            {
                dt.ImportRow(sel_city.next());
            }

            sel_city.close();

            /* join */
            j.open(dto, dt);

            dt.Clear();

            dt = j.cloneSchema();

            while (j.hasMore())
            {
                dt.ImportRow(j.next());
            }

            j.close();

            /* distinct */
            d.open(dt);

            dt.Clear();

            while (d.hasMore())
            {
                dt.ImportRow(d.next());
            }

            d.close();

            /* project */
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

            m_stats.Add("count.query12", resultCnt);

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
                statBuilder.Append("distinct.query12." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(T.branch_name)");
            expression.Add("\t\t|");
            expression.Add("\tdistinct(T.branch_name)");
            expression.Add("\t\t|");
            expression.Add("\tjoin(T.assets > S.assets)");
            expression.Add("\t\t/\t\\");
            expression.Add("\tassets->T.assets\tassets->S.assets");
            expression.Add("\t\t|\t\t|");
            expression.Add("branch_name->T.branch_name\tselect(S.branch_city, eq 'Brooklyn')");
            expression.Add("\t\t|\t\t\t|");
            expression.Add("\t\tbranch T\t\tbranch_city->S.branch_city");
            expression.Add("\t\t\t\t\t|");
            expression.Add("\t\t\t\t\tbranch S");

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
