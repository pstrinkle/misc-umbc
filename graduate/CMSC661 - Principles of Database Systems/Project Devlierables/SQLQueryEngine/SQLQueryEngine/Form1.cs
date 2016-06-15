using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Threading;

namespace SQLQueryEngine
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
                        
            List<string> relations = new List<string>();

            relations.Add("customer");
            relations.Add("borrower");
            relations.Add("loan");
            relations.Add("branch");
            relations.Add("depositor");
            relations.Add("account");

            this.statman = new StatisticsManager(relations);

            List<string> items = Aux.printMenu();
            
            this.listBox1.Items.AddRange(items.ToArray());

            this.BtnForExecute.Visible = true;            
        }

        delegate void SetTextCallback(string text);
        delegate void SetDataViewSource(DataTable data);
        delegate string GetUserInput();
        delegate int GetPause();

        public void SetText(string text)
        {
            if (this.statusTxt.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.statusTxt.Text = text;
            }
        }

        public void SetDataView(DataTable data)
        {            
            if (this.dataGridView1.InvokeRequired)
            {
                SetDataViewSource d = new SetDataViewSource(SetDataView);
                this.Invoke(d, new object[] { data });
            }
            else
            {
                this.dataGridView1.DataSource = data;
            }
        }

        public string GetUserAggregateInput()
        {
            string output = string.Empty;

            if (this.userAggregate.InvokeRequired)
            {
                GetUserInput d = new GetUserInput(GetUserAggregateInput);
                output = (string)this.Invoke(d);
            }
            else
            {
                output = this.userAggregate.Text;
            }

            return output;
        }

        public int GetUserPause()
        {
            int output = 0;

            if (this.pauseTxtBox.InvokeRequired)
            {
                GetPause d = new GetPause(GetUserPause);
                output = (int)this.Invoke(d);
            }
            else
            {
                try
                {
                    output = Int32.Parse(this.pauseTxtBox.Text);
                }
                catch (Exception e)
                {
                    output = 0;
                }
            }

            if (output < 0)
                output = 0;

            return output;
        }

        private void displayStatistics(int queryId)
        {
            switch (queryId)
            {
                case 1:
                    /* print stats */
                    if (statman.retrieveStat("count.query1") == -1)
                    {
                        /* we have to calculate */
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.customer").ToString());

                        /* distinct tuple values */
                        this.listBox2.Items.Add("Distinct: customer_name: " + statman.retrieveStat("distinct.customer.customer_name").ToString());
                        this.listBox2.Items.Add("Distinct: customer_street: " + statman.retrieveStat("distinct.customer.customer_street").ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + statman.retrieveStat("distinct.customer.customer_city").ToString());
                    }
                    else
                    {
                        /* we have stats */
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query1").ToString());

                        /* distinct tuple values */
                        this.listBox2.Items.Add("Distinct: customer_name: " + statman.retrieveStat("distinct.query1.customer_name").ToString());
                        this.listBox2.Items.Add("Distinct: customer_street: " + statman.retrieveStat("distinct.query1.customer_street").ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + statman.retrieveStat("distinct.query1.customer_city").ToString());
                    }
                    break;
                case 2:
                    /* print stats */
                    if (statman.retrieveStat("count.query2") == -1)
                    {
                        /* we don't know */
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("count.account") / 3).ToString());
                        this.listBox2.Items.Add("Distinct: account_number: " + (statman.retrieveStat("distinct.account.account_number") / 3).ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query2").ToString());
                        this.listBox2.Items.Add("Distinct: account_number: " + statman.retrieveStat("distinct.query2.account_number").ToString());
                    }
                    break;
                case 3:
                    /* print stats */
                    if (statman.retrieveStat("count.query3") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("count.customer") / statman.retrieveStat("distinct.customer_name")).ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: 1");
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query3").ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: " + statman.retrieveStat("distinct.query3.customer_name").ToString());
                    }
                    break;
                case 4:
                    /* prints stats */
                    if (statman.retrieveStat("count.query4") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("count.customer") / statman.retrieveStat("distinct.customer_name")).ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: 1");
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query4").ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: " + statman.retrieveStat("distinct.query4.customer_name").ToString());
                    }
                    break;
                case 5:
                    /* print stats */
                    if (statman.retrieveStat("count.query5") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("count.loan")).ToString());
                        this.listBox2.Items.Add("Distinct: loan_number: " + (statman.retrieveStat("distinct.loan.loan_number")).ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + (statman.retrieveStat("distinct.loan.branch_name")).ToString());
                        this.listBox2.Items.Add("Distinct: amount: " + (statman.retrieveStat("distinct.loan.amount")).ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query5").ToString());
                        this.listBox2.Items.Add("Distinct: loan_number: " + statman.retrieveStat("distinct.query5.loan_number").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query5.branch_name").ToString());
                        this.listBox2.Items.Add("Distinct: amount: " + statman.retrieveStat("distinct.query5.amount").ToString());
                    }
                    break;
                case 6:
                    /* print stats */
                    this.listBox2.Items.Add("Estimated Tuples: 1");
                    break;
                case 7:
                    /* print stats */
                    if (statman.retrieveStat("count.query7") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("distinct.account.branch_name").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.account.branch_name").ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query7").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query7.branch_name").ToString());
                    }
                    break;
                case 8:
                    /* print stats */
                    if (statman.retrieveStat("count.query8") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("distinct.branch.branch_city").ToString());
                        this.listBox2.Items.Add("Distinct: branch_city: " + statman.retrieveStat("distinct.branch.branch_city").ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query8").ToString());
                        this.listBox2.Items.Add("Distinct: branch_city: " + statman.retrieveStat("distinct.query8.branch_city").ToString());
                    }
                    break;
                case 9:
                    /* print stats */
                    if (statman.retrieveStat("count.query9") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("distinct.account.branch_name") / 3).ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + (statman.retrieveStat("distinct.account.branch_name") / 3).ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query9").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query9.branch_name").ToString());
                    }
                    break;
                case 10:
                    /* print stats */
                    if (statman.retrieveStat("count.query10") == -1)
                    {
                        int d_dep = statman.retrieveStat("distinct.depositor.account_number");
                        int d_acc = statman.retrieveStat("distinct.account.account_number");

                        int d_depbranch_name = statman.retrieveStat("distinct.account.branch_name");

                        int minDistinct = (d_dep > d_acc) ? d_acc : d_dep;

                        int minimum = (d_depbranch_name < minDistinct) ? d_depbranch_name : minDistinct;

                        this.listBox2.Items.Add("Estimated Tuples: " + minimum.ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + minimum.ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query10").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query10.branch_name").ToString());
                    }
                    break;
                case 11:
                    /* print stats */
                    /* since we only care about the distinct pair of customer.cust_n, cust_city
                     * we really only return the minimum of the total tuples from join, distinct cust_n,
                     * and cust_city */
                    if (statman.retrieveStat("count.query11") == -1)
                    {
                        int d_borr_cust_n = statman.retrieveStat("distinct.borrower.customer_name");
                        int d_cust_cust_n = statman.retrieveStat("distinct.customer.customer_name");
                        int d_cust_cust_c = statman.retrieveStat("distinct.customer.customer_city");

                        int t_borr = statman.retrieveStat("count.borrower");
                        int t_cust = statman.retrieveStat("count.customer");

                        int max_d_cust_n = (d_borr_cust_n > d_cust_cust_n) ? d_borr_cust_n : d_cust_cust_n;

                        int t_join = (t_borr * t_cust) / max_d_cust_n;

                        int min_d_cust_n = (d_borr_cust_n < d_cust_cust_n) ? d_borr_cust_n : d_cust_cust_n;

                        int max_d_cust_n_cust_c = (min_d_cust_n > d_cust_cust_c) ? min_d_cust_n : d_cust_cust_c;

                        int minimum_ret = (max_d_cust_n_cust_c < t_join) ? max_d_cust_n_cust_c : t_join;

                        this.listBox2.Items.Add("Estimated Tuples: " + minimum_ret.ToString());
                        this.listBox2.Items.Add("Distinct: customer.customer_name: " + minimum_ret.ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + minimum_ret.ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query11").ToString());
                        this.listBox2.Items.Add("Distinct: customer.customer_name: " + statman.retrieveStat("distinct.query11.customer.customer_name").ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + statman.retrieveStat("distinct.query11.customer_city").ToString());
                    }
                    break;
                case 12:
                    /* print stats */
                    if (statman.retrieveStat("count.query12") == -1)
                    {
                        int d_branch_br_n = statman.retrieveStat("distinct.branch.branch_name");
                        int t_branch = statman.retrieveStat("count.branch");

                        this.listBox2.Items.Add("Estimated Tuples: " + (t_branch / 3).ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + d_branch_br_n.ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query12").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query12.T.branch_name").ToString());
                    }
                    break;
                case 13:
                    /* print stats */
                    if (statman.retrieveStat("count.query13") == -1)
                    {
                        int t_borrower = statman.retrieveStat("count.borrower");
                        int t_loan = statman.retrieveStat("count.loan");
                        int t_cust = statman.retrieveStat("count.customer");

                        int v_loan_branch_name = statman.retrieveStat("distinct.loan.branch_name");
                        int v_loan_loan_number = statman.retrieveStat("distinct.loan.loan_number");

                        int v_bor_loan_number = statman.retrieveStat("distinct.borrower.loan_number");
                        int v_cust_cust_name = statman.retrieveStat("distinct.customer.customer_name");
                        int v_cust_cust_city = statman.retrieveStat("distinct.customer.customer_city");
                        int v_bor_cust_name = statman.retrieveStat("distinct.borrower.customer_name");

                        int t_loanP = t_loan / v_loan_branch_name;
                        int v_loanP_loan_number = v_loan_loan_number / v_loan_branch_name;

                        int maxOf_bor_loan_num_and_loan_loan_num = (v_bor_loan_number > v_loanP_loan_number) ? v_bor_loan_number : v_loanP_loan_number;
                        int maxOf_cust_cust_name_and_loanP_cust_name = (v_cust_cust_name > v_bor_cust_name) ? v_cust_cust_name : v_bor_cust_name;

                        /* v_bor_cust_name is V(I,cust_name) */

                        int t_I = (t_borrower * t_loanP) / maxOf_bor_loan_num_and_loan_loan_num;

                        int t_X = (t_cust * t_I) / maxOf_cust_cust_name_and_loanP_cust_name;

                        /* t_X is tuples returned */

                        /* distinct C.customer_name, C.customer city */
                        int mindistinct_name = (t_X < v_cust_cust_name) ? t_X : v_cust_cust_name;
                        int mindistinct_city = (t_X < v_cust_cust_city) ? t_X : v_cust_cust_city;

                        this.listBox2.Items.Add("Estimated Tuples: " + t_X.ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: " + mindistinct_name.ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + mindistinct_city.ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query13").ToString());
                        this.listBox2.Items.Add("Distinct: customer_name: " + statman.retrieveStat("distinct.query13.customer_name").ToString());
                        this.listBox2.Items.Add("Distinct: customer_city: " + statman.retrieveStat("distinct.query13.customer_city").ToString());
                    }
                    break;
                case 14:
                    /* print stats */
                    if (statman.retrieveStat("count.query14") == -1)
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + (statman.retrieveStat("distinct.branch.branch_name") / 3).ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + (statman.retrieveStat("distinct.branch.branch_name") / 3).ToString());
                    }
                    else
                    {
                        this.listBox2.Items.Add("Estimated Tuples: " + statman.retrieveStat("count.query14").ToString());
                        this.listBox2.Items.Add("Distinct: branch_name: " + statman.retrieveStat("distinct.query14.branch_name").ToString());
                    }
                    break;
                case 15:
                    this.listBox2.Items.Add("Need to do");
                    break;
                default:
                    break;
            }
        }

        private void displayExpressionTrees(int queryId)
        {
            List<string> expressionItems = null;

            switch (queryId)
            {
                case 1:
                    expressionItems = Query1.express();
                    break;
                case 2:
                    expressionItems = Query2.express();
                    break;
                case 3:
                    expressionItems = Query3.express();
                    break;
                case 4:
                    expressionItems = Query4.express();
                    break;
                case 5:
                    expressionItems = Query5.express();
                    break;
                case 6:
                    expressionItems = Query6.express();
                    break;
                case 7:
                    expressionItems = Query7.express();
                    break;
                case 8:
                    expressionItems = Query8.express();
                    break;
                case 9:
                    expressionItems = Query9.express();
                    break;
                case 10:
                    expressionItems = Query10.express();
                    break;
                case 11:
                    expressionItems = Query11.express();
                    break;
                case 12:
                    expressionItems = Query12.express();
                    break;
                case 13:
                    expressionItems = Query13.express();
                    break;
                case 14:
                    expressionItems = Query14.express();
                    break;
                case 15:
                    expressionItems = Query15.express();
                    break;
                default:
                    break;

            }

            /* make sure queryId was valid */
            if (queryId <= 15 && queryId > 0)
            {
                foreach (string es in expressionItems)
                    this.listBox3.Items.Add(es);
            }
        }

        private void displayTupleCalculations(int rowCount, DataColumnCollection dcc)
        {
            int tupleSum = 0;
            foreach (DataColumn dc in dcc)
            {
                if (dc.DataType.ToString().CompareTo("System.String") == 0)
                    tupleSum += 15;
                else if (dc.DataType.ToString().CompareTo("System.Int32") == 0)
                    tupleSum += 4;
            }

            /* print out size stats */
            this.listBox2.Items.Add("Estimated Tuple Size: " + tupleSum.ToString() + " bytes");
            this.listBox2.Items.Add("Estimated Size of Returned Data: " + (rowCount * tupleSum).ToString() + " bytes");
        }

        private void setAsBusy()
        {
            this.BtnForExecute.Enabled = false;
            this.BtnForExecute.Visible = false;
            this.statusTxt.Text = "Processing...";
            this.dataGridView1.DataSource = null;
            this.listBox2.Items.Clear();
            this.listBox3.Items.Clear();
            UseWaitCursor = true;
        }

        private void setAsFree()
        {
            this.BtnForExecute.Enabled = true;
            this.BtnForExecute.Visible = true;            
            UseWaitCursor = false;
        }

        private void BtnForExecute_Click(object sender, EventArgs e)
        {
            setAsBusy();

            if (!backgroundWorker1.IsBusy)
            {
                displayStatistics(this.listBox1.SelectedIndex + 1);
                displayExpressionTrees(this.listBox1.SelectedIndex + 1);
                backgroundWorker1.RunWorkerAsync(this.listBox1.SelectedIndex + 1);
            }
            
            setAsFree();
        }

        private void BtnForClear_Click(object sender, EventArgs e)
        {
            this.dataGridView1.DataSource = null;
            this.listBox2.Items.Clear();
            this.listBox3.Items.Clear();
            this.statusTxt.Text = "Ready"; 
        }
        
        private StatisticsManager statman;        

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void dataViewClick(object sender, EventArgs e)
        {
            Clipboard.SetDataObject(this.dataGridView1.GetClipboardContent());
        }

        private void executeQuery(object sender, DoWorkEventArgs e)
        {                        
            int queryId = (int)e.Argument;

            DataTable output = new DataTable();

            switch (queryId)
            {
                case 1:
                    Query1 q1 = new Query1();

                    /* execute query */
                    q1.exec();

                    output = q1.getResults();

                    /*update stats */
                    if (statman.retrieveStat("count.query1") == -1)
                    {
                        statman.batchUpdateStats(q1.getStats());
                    }
                    break;
                case 2:
                    Query2 q2 = new Query2();

                    /* execute query */
                    q2.exec();

                    output = q2.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query2") == -1)
                    {
                        statman.batchUpdateStats(q2.getStats());
                    }
                    break;
                case 3:
                    Query3 q3 = new Query3();

                    /* execute query */
                    q3.exec();

                    output = q3.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query3") == -1)
                    {
                        statman.batchUpdateStats(q3.getStats());
                    }
                    break;
                case 4:
                    Query4 q4 = new Query4();

                    /* execute query */
                    q4.exec();

                    output = q4.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query4") == -1)
                    {
                        statman.batchUpdateStats(q4.getStats());
                    }
                    break;
                case 5:
                    Query5 q5 = new Query5();

                    /* execute query */
                    q5.exec();

                    output = q5.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query5") == -1)
                    {
                        statman.batchUpdateStats(q5.getStats());
                    }

                    break;
                case 6:
                    Query6 q6 = new Query6();

                    /* execute query */
                    q6.passForm(this, output);                    

                    q6.exec();

                    output = q6.getResults();

                    break;
                case 7:
                    Query7 q7 = new Query7();

                    /* execute query */
                    q7.passForm(this, output);
                    q7.exec();

                    output = q7.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query7") == -1)
                    {
                        statman.batchUpdateStats(q7.getStats());
                    }
                    break;
                case 8:
                    Query8 q8 = new Query8();

                    /* execute query */
                    q8.passForm(this, output);                    

                    q8.exec();

                    output = q8.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query8") == -1)
                    {
                        statman.batchUpdateStats(q8.getStats());
                    }
                    break;
                case 9:
                    Query9 q9 = new Query9();

                    /* execute query */
                    q9.passForm(this, output);                    

                    q9.exec();

                    output = q9.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query9") == -1)
                    {
                        statman.batchUpdateStats(q9.getStats());
                    }
                    break;
                case 10:
                    Query10 q10 = new Query10();

                    /* execute query */
                    q10.passForm(this, output);                    

                    q10.exec();

                    output = q10.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query10") == -1)
                    {
                        statman.batchUpdateStats(q10.getStats());
                    }
                    break;
                case 11:
                    Query11 q11 = new Query11();

                    /* execute query */
                    q11.exec();

                    output = q11.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query11") == -1)
                    {
                        statman.batchUpdateStats(q11.getStats());
                    }
                    break;
                case 12:
                    Query12 q12 = new Query12();

                    /* execute query */
                    q12.exec();

                    output = q12.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query12") == -1)
                    {
                        statman.batchUpdateStats(q12.getStats());
                    }
                    break;
                case 13:
                    Query13 q13 = new Query13();

                    /* execute query */
                    q13.exec();

                    output = q13.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query13") == -1)
                    {
                        statman.batchUpdateStats(q13.getStats());
                    }
                    break;
                case 14:
                    Query14 q14 = new Query14();

                    /* execute query */
                    q14.exec();

                    output = q14.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query14") == -1)
                    {
                        statman.batchUpdateStats(q14.getStats());
                    }
                    break;
                case 15:
                    Query15 q15 = new Query15();

                    /* execute query */
                    q15.exec();

                    output = q15.getResults();

                    /* update stats */
                    if (statman.retrieveStat("count.query15") == -1)
                    {
                        statman.batchUpdateStats(q15.getStats());
                    }
                    break;
                default:
                    Aux.print("Invalid option.");
                    output.Columns.Add("Invalid Option", System.Type.GetType("System.String"));
                    break;
            } /* end switch */

            e.Result = output;
        }

        private void progressUpdate(object sender, ProgressChangedEventArgs e)
        {
            
        }

        private void queryComplete(object sender, RunWorkerCompletedEventArgs e)
        {
            DataTable output = (DataTable)e.Result;

            this.statusTxt.Text = "Completed";
            this.dataGridView1.DataSource = output;

            displayTupleCalculations(output.Rows.Count, output.Columns);
        }

        private void dataGridView_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                this.dataGridView1.ContextMenu.Show(dataGridView1, new Point(e.X, e.Y));                             
            }
        }
    }
}
