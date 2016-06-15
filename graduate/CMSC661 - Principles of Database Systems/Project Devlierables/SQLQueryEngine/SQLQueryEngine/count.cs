using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class count
    {
        public count(string field, string groupby, bool distinctOnly)
        {
            if (groupby == null || groupby == string.Empty)
            {
                /* there is no grouping on this count */
                /* bulk count */
                this.m_groupby = false;
            }
            else
            {
                this.m_grouping = groupby;
                this.m_groupby = true;
            }

            if (field.CompareTo("*") == 0)
            {
                this.m_cntfield = false;
            }
            else
            {
                this.m_field = field;
            }

            if (distinctOnly)
            {
                m_distinct = true;
            }
            else
            {
                this.m_distinct = false;
            }

            this.m_cnt = 0;
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
                /* bulk count on the field specified */
                /* need to put in distinct test here */

                DataColumn cntCol = null;

                if (!m_cntfield)
                {
                    cntCol = new DataColumn("count(*)", System.Type.GetType("System.Int32"));
                }
                else
                {
                    cntCol = new DataColumn("count(" + m_field + ")", System.Type.GetType("System.Int32"));
                }

                /* just counting the number of rows */
                m_cnt = data.Rows.Count;

                m_results.Columns.Add(cntCol);

                List<int> value = new List<int>();
                value.Add(m_cnt);

                m_results.Rows.Add(value.ToArray()[0]);
            }
            else
            {
                /* pack them into bins and calculate for the bins */

                /* track bins we have so far */
                Dictionary<string, int> bins = new Dictionary<string, int>();

                int valueIndex = data.Columns.IndexOf(m_field);
                int groupIndex = data.Columns.IndexOf(m_grouping);

                /* build result relation */
                /* m_grouping | count | sum | average */
                /* the counts and sum are all floats to handle any case where it's a value */
                DataColumn groupCol = new DataColumn(m_grouping, System.Type.GetType("System.String"));

                StringBuilder sb = new StringBuilder();
                sb.Append("count(");

                if (m_distinct)
                    sb.Append("distinct ");

                sb.Append(m_field);
                sb.Append(")");

                /* should make it a double; but this is to simplify other pieces */
                DataColumn countCol = new DataColumn(sb.ToString(), System.Type.GetType("System.Int32"));

                m_results.Columns.Add(groupCol);
                m_results.Columns.Add(countCol);
                /* end build result table */

                /* to handle distinct */
                List<string> valuesSeen = new List<string>();

                int printBinUpdates = 0;

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
                    /* will this not work with integers */
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

                    object value = obs[valueIndex];
                    string group = (string)obs[groupIndex];

                    /* we have this group */
                    if (bins.ContainsKey(group))
                    {
                        Boolean distinct_add = true;

                        if (m_distinct)
                        {
                            /* we care about distinct and we've seen this before */
                            if (valuesSeen.Contains(group.ToString() + value.ToString()))
                                distinct_add = false;
                        }

                        if (distinct_add)
                        {
                            int seekIndex;

                            /* we have a bin for this group */
                            bins.TryGetValue(group, out seekIndex);

                            Object[] obsInTable = m_results.Rows[seekIndex].ItemArray;

                            /* get current values in group */
                            int currentCount = (int)obsInTable[1];

                            currentCount++;

                            /* should only return 1 item because we only have 1 row per group */
                            DataRow[] editRow = m_results.Select(m_grouping + " = '" + group + "'");

                            editRow[0][countCol] = currentCount;
                        }
                    }
                    else
                    {
                        /* this is first time we've seen group */
                        bins.Add(group, m_results.Rows.Count);

                        /* add it to distinct filter (regardless if we care */
                        valuesSeen.Add(group.ToString() + value.ToString());

                        /* set values for m_results */
                        DataRow newRow = m_results.NewRow();

                        newRow[0] = group;
                        newRow[1] = 1;

                        m_results.Rows.Add(newRow);
                    } /* end if bins.ContainsKey(group) */

                    data.Rows.Remove(dr);
                    completeRows.RemoveAt(0);

                    System.Threading.Thread.Sleep(this.m_form.GetUserPause());

                    printBinUpdates++;

                    if (printBinUpdates == 5)
                    {
                        Aux.printUpdates(m_results);
                        printBinUpdates = 0;

                        m_update = m_results.Copy();

                        this.m_form.SetText("Aggregate Update");
                        this.m_form.SetDataView(m_update);
                    }
                } /* for each tuple */

            } /* end if group by */
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
        private int m_cnt;
        private string m_grouping;

        private Boolean m_groupby;
        private Boolean m_cntfield;
        private Boolean m_distinct;

        private DataTable m_results, m_update;
        private int m_current_tuple;

        private Form1 m_form;
    }
}
