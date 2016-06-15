using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query10
    {
        public Query10()
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
            DataTable dto = new DataTable("temp");
            List<string> fields = new List<string>();

            fields.Add("branch_name");
            fields.Add("count(distinct customer_name)");

            scan sdepositor = new scan("depositor");
            scan saccount = new scan("account");

            count c = new count("customer_name", "branch_name", true);

            renamefield renDep = new renamefield("account_number", "depositor.account_number");
            renamefield renAcc = new renamefield("account_number", "account.account_number");

            List<string> joinon = new List<string>();
            joinon.Add("depositor.account_number");
            joinon.Add("eq");
            joinon.Add("account.account_number");
            joinon.Add("str");

            join j = new join(joinon);

            project p = new project(fields);

            /* read in depositor */
            sdepositor.open();

            dt = sdepositor.cloneSchema();

            /* get all tuples from SCAN */
            while (sdepositor.hasMore())
            {
                dt.ImportRow(sdepositor.next());
            }

            sdepositor.close();

            /* read in account */
            saccount.open();

            dto = saccount.cloneSchema();

            while (saccount.hasMore())
            {
                dto.ImportRow(saccount.next());
            }

            saccount.close();

            /* rename fields before join */
            renAcc.open(dto);
            renDep.open(dt);

            /* join relations */
            j.open(dt, dto);

            dt.Clear();
            dto.Clear();

            dt = j.cloneSchema();

            while (j.hasMore())
            {
                dt.ImportRow(j.next());
            }

            c.loadFormAcces(m_form, m_resultTable);

            /* count */
            c.open(dt);

            dt.Clear();

            dt = c.cloneSchema();

            while (c.hasMore())
            {
                dt.ImportRow(c.next());
            }

            c.close();

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

            m_stats.Add("count.query10", resultCnt);

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
                statBuilder.Append("distinct.query10." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("\tproject(branch_name, count(distinct customer_name))");
            expression.Add("\t\t\t|");
            expression.Add("\tcount(branch_name, distinct customer_name)");
            expression.Add("\t\t\t|");
            expression.Add("\tnatural-join(depositor.account_number = account.account_number)");
            expression.Add("\t\t/\t\t\t\t\t\\");
            expression.Add("\t\t|\t\t\t\t\t|");
            expression.Add("\taccount_number->depositor.account_number\taccount_number->account.account_number");
            expression.Add("\t\t|\t\t\t\t\t|");
            expression.Add("\t\tdepositor\t\t\t\t\taccount");

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
