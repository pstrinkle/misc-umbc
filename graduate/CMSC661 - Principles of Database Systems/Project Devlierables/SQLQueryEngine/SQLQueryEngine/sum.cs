using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class sum
    {
        public sum(string field, string groupby)
        {
            if (groupby == null || groupby == string.Empty)
            {
                /* average of all tuples for the field*/
                this.m_groupby = false;
            }
            else
            {
                this.m_grouping = groupby;
                this.m_groupby = true;
            }

            this.m_field = field;
            this.m_current_tuple = 0;
            this.m_results = new DataTable(field);
        }

        public void loadFormAcces(Form1 form, DataTable resultTable)
        {
            m_update = resultTable;
            m_form = form;
        }

        /* currently only handles integer comparisons */
        public void open(DataTable data)
        {
            if (!m_groupby)
            {
                StringBuilder sb = new StringBuilder();
                sb.Append("sum(");
                sb.Append(m_field);
                sb.Append(")");

                DataColumn sumCol = new DataColumn(sb.ToString(), System.Type.GetType("System.Int32"));
                m_results.Columns.Add(sumCol);

                /* bulk average on the field specified */
                int sum = 0;

                int columnIndex = data.Columns.IndexOf(m_field);

                /* need to calculate sum of all for that field specified */
                foreach (DataRow dr in data.Rows)
                {
                    /* grab value of field and add to sum */
                    Object[] obs = dr.ItemArray;

                    sum += (int)obs[columnIndex];
                }

                List<int> value = new List<int>();
                value.Add(sum);

                m_results.Rows.Add(value.ToArray()[0]);
            }
            else
            {
                /* pack them into bins and calculate for the bins */

                /* track bins we have so far */
                Dictionary<string, int> bins = new Dictionary<string, int>();

                /* columns indices we care about from input */
                int valueIndex = data.Columns.IndexOf(m_field);
                int groupIndex = data.Columns.IndexOf(m_grouping);

                /* build result relation */
                /* m_grouping | sum */
                /* the counts and sum are all floats to handle any case where it's a value */
                DataColumn groupCol = new DataColumn(m_grouping, System.Type.GetType("System.String"));

                StringBuilder sb = new StringBuilder();
                sb.Append("sum(");
                sb.Append(m_field);
                sb.Append(")");

                DataColumn sumCol = new DataColumn(sb.ToString(), System.Type.GetType("System.Int32"));

                m_results.Columns.Add(groupCol);
                m_results.Columns.Add(sumCol);
                /* end build result table */

                int printBinsCounter = 0;

                string userAggregateInput = string.Empty;

                userAggregateInput = this.m_form.GetUserAggregateInput();

                /* note even if the userAggregateInput is invalid it will correctly fill */
                List<DataRow> completeRows = new List<DataRow>();

                if (userAggregateInput.CompareTo(string.Empty) == 0)
                {
                    DataRow[] rows = new DataRow[data.Rows.Count];
                    data.Rows.CopyTo(rows, 0);

                    completeRows.AddRange(rows);
                }
                else
                {
                    DataRow[] rows = data.Select(this.m_grouping + " = '" + userAggregateInput + "'");
                    completeRows.AddRange(rows);

                    DataRow[] other = data.Select(this.m_grouping + " <> '" + userAggregateInput + "'");
                    completeRows.AddRange(other);
                }

                /* begin parsing data */
                while (data.Rows.Count > 0)
                {
                    /* user has specified new input */
                    if (userAggregateInput.CompareTo(this.m_form.GetUserAggregateInput()) != 0)
                    {
                        completeRows.Clear();

                        userAggregateInput = this.m_form.GetUserAggregateInput();

                        DataRow[] rows = data.Select(this.m_grouping + " = '" + userAggregateInput + "'");
                        completeRows.AddRange(rows);

                        DataRow[] other = data.Select(this.m_grouping + " <> '" + userAggregateInput + "'");
                        completeRows.AddRange(other);
                    }

                    DataRow dr = completeRows[0];

                    Object[] obs = dr.ItemArray;

                    int value = (int)obs[valueIndex];
                    string group = (string)obs[groupIndex];

                    /* we have this group */
                    if (bins.ContainsKey(group))
                    {
                        int seekIndex;

                        /* we have a bin for this group */
                        bins.TryGetValue(group, out seekIndex);

                        Object[] obsInTable = m_results.Rows[seekIndex].ItemArray;

                        /* get current values in group */
                        int currentSum = (int)obsInTable[1];

                        currentSum += value;

                        /* should only return 1 item because we only have 1 row per group */
                        DataRow[] editRow = m_results.Select(m_grouping + " = '" + group + "'");

                        editRow[0][sumCol] = currentSum;
                    }
                    else
                    {
                        bins.Add(group, m_results.Rows.Count);

                        /* set values for m_results */
                        DataRow newRow = m_results.NewRow();

                        newRow[groupCol] = group;
                        newRow[sumCol] = value;

                        m_results.Rows.Add(newRow);
                    }

                    data.Rows.Remove(dr);
                    completeRows.RemoveAt(0);

                    System.Threading.Thread.Sleep(this.m_form.GetUserPause());

                    printBinsCounter++;

                    /* prints every five rows */
                    if (printBinsCounter == 3)
                    {
                        Aux.printUpdates(m_results);

                        printBinsCounter = 0;

                        m_update = m_results.Copy();

                        this.m_form.SetText("Aggregate Update");
                        this.m_form.SetDataView(m_update);
                    }
                } /* end for each tuple in input */
            } /* end (m_groupby) */
        }

        public DataTable cloneSchema()
        {
            return m_results.Clone();
        }

        public Boolean hasMore()
        {
            Boolean success = false;

            if (m_results.Rows.Count > m_current_tuple)
                success = true;

            return success;
        }

        public DataRow next()
        {
            DataRow dr = m_results.Rows[m_current_tuple];
            m_current_tuple++;

            return dr;
        }

        public void close()
        {
            m_results.Clear();
        }

        private string m_field;
        private string m_grouping;
        private Boolean m_groupby;
        private DataTable m_results, m_update;
        private int m_current_tuple;

        private Form1 m_form;
    }
}
