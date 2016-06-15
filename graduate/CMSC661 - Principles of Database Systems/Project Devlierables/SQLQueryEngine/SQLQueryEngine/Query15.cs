using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class Query15
    {
        public Query15()
        {
            /* No Code is God's Code */
            m_stats = new Dictionary<string, int>();            
            m_outDT = new DataTable();
        }

        public void exec()
        {
            DataTable dt = new DataTable("tempMain");
            DataTable dto = new DataTable("tempSecondary");

            List<string> fields = new List<string>();

            fields.Add("borrower.customer_name");

            project p = new project(fields);
            distinct d = new distinct(fields);

            scan scanBorrower = new scan("borrower");
            scan scanLoan = new scan("loan");
            scan scanBranch = new scan("branch");

            select s = new select("loan.branch_name", "eq", "Perryridge");

            renamefield renLoanLoanNumber = new renamefield("loan_number", "loan.loan_number");
            renamefield renBorLoanNumber = new renamefield("loan_number", "borrower.loan_number");
            renamefield renLoanBranchName = new renamefield("branch_name", "loan.branch_name");
            renamefield renBranchBranchName = new renamefield("branch_name", "branch.branch_name");
            renamefield renBorCustName = new renamefield("customer_name", "borrower.customer_name");

            List<string> joinloanbranch = new List<string>();
            joinloanbranch.Add("loan.branch_name");
            joinloanbranch.Add("eq");
            joinloanbranch.Add("branch.branch_name");
            joinloanbranch.Add("str");

            List<string> joinborrower = new List<string>();
            joinborrower.Add("borrower.loan_number");
            joinborrower.Add("eq");
            joinborrower.Add("loan.loan_number");
            joinborrower.Add("str");

            join joinlb = new join(joinloanbranch);
            join joinbo = new join(joinborrower);

            orderby o = new orderby("borrower.customer_name", "asc", "str");

            /* Read in loan */
            scanLoan.open();

            dt.Clear();
            dt = scanLoan.cloneSchema();

            while (scanLoan.hasMore())
            {
                dt.ImportRow(scanLoan.next());
            }

            scanLoan.close();

            /* rename loan fields */
            renLoanLoanNumber.open(dt);
            renLoanBranchName.open(dt);

            /* where loan.branch_name = 'Perryridge' */
            s.open(dt);

            dt.Clear();

            while (s.hasMore())
            {
                dt.ImportRow(s.next());
            }

            s.close();

            /* scan branch into dto */
            scanBranch.open();

            dto.Clear();
            dto = scanBranch.cloneSchema();

            while (scanBranch.hasMore())
            {
                dto.ImportRow(scanBranch.next());
            }

            scanBranch.close();

            /* rename branch_name to branch.branch_name */
            renBranchBranchName.open(dto);

            /* join loan, branch */
            joinlb.open(dt, dto);

            /* clean table to store results */
            dto.Clear();
            dto = joinlb.cloneSchema();

            while (joinlb.hasMore())
            {
                dto.ImportRow(joinlb.next());
            }

            joinlb.close();

            /* dto holds results of join */

            /* scan in borrower relation */
            scanBorrower.open();

            dt.Clear();
            dt = scanBorrower.cloneSchema();

            while (scanBorrower.hasMore())
            {
                dt.ImportRow(scanBorrower.next());
            }

            scanBorrower.close();

            /* rename borrower */
            renBorCustName.open(dt);
            renBorLoanNumber.open(dt);

            /* join borrower with dto */
            joinbo.open(dt, dto);

            dt.Clear();
            dto.Clear();

            dt = joinbo.cloneSchema();

            while (joinbo.hasMore())
            {
                dt.ImportRow(joinbo.next());
            }

            joinbo.close();

            /* dt holds final join results */
            
            /* run distinct filter */
            d.open(dt);

            dt.Clear();

            while (d.hasMore())
            {
                dt.ImportRow(d.next());
            }

            d.close();
            
            /* order by */
            o.open(dt);
            
            dt.Clear();

            while (o.hasMore())
            {
                dt.ImportRow(o.next());
            }

            o.close();

            p.open(dt);

            dt.Clear();
            dt = p.cloneSchema();

            while (p.hasMore())
            {
                dt.ImportRow(p.next());
            }

            p.close();

            /* dt holds results */

            /* update stats */
            int resultCnt = dt.Rows.Count;

            m_stats.Add("count.query15", resultCnt);

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
                statBuilder.Append("distinct.query15." + dc.ColumnName);

                m_stats.Add(statBuilder.ToString(), distinctCounter.Count);
            }

            m_outDT = dt.Copy();
        }

        public static List<string> express()
        {
            List<string> expression = new List<string>();

            expression.Add("orderby(borrower.customer_name)");
            expression.Add("\t|");
            expression.Add("project(customer_name)");
            expression.Add("\t|");
            expression.Add("distinct(customer_name)");
            expression.Add("\t|");
            expression.Add("natural-join(borrower.loan_number = loan.loan_number)");
            expression.Add("\t/\t\t\t\t\\");
            expression.Add("loan_number->borrower.loan_number\tnatural-join(loan.branch_name = branch.branch_name)");
            expression.Add("\t|\t\t\t\t/\t\t\t\\");
            expression.Add("\tborrower\t\tbranch_name->loan.branch_name\tbranch_name->branch.branch_name");
            expression.Add("\t\t\t\t\t|\t\t\t|");
            expression.Add("\t\t\tselect(branch_name, eq 'Perryridge')\t\tbranch");
            expression.Add("\t\t\t\t\t|");
            expression.Add("\t\t\t\t\tloan");

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
