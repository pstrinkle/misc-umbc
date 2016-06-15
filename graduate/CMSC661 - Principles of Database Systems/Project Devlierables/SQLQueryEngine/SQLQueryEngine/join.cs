using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class join
    {
        /* fields */
        /* Currently only runs distinct on 1 field */
        public join(List<string> join)
        {
            if (join.Count == 4)
            {
                m_fieldLeft = join.ToArray()[0];
                m_operation = join.ToArray()[1];
                m_fieldRight = join.ToArray()[2];
                m_type = join.ToArray()[3];
            }

            /* need to error otherwise */

            this.m_dt = new DataTable();
            this.m_current_tuple = 0;
        }

        public void open(DataTable dataLeft, DataTable dataRight)
        {
            // clean out any garbage
            m_dt.Clear();

            /* need to set up columns in m_result */
            /* add columns from left, then right */
            /* so inefficient but would not let me do otherwise */
            DataColumn temp = null;

            foreach (DataColumn dc in dataLeft.Columns)
            {
                temp = new DataColumn();
                temp.ColumnName = dc.ColumnName;
                temp.DataType = dc.DataType;

                m_dt.Columns.Add(temp);
            }

            foreach (DataColumn dc in dataRight.Columns)
            {
                temp = new DataColumn();
                temp.ColumnName = dc.ColumnName;
                temp.DataType = dc.DataType;

                m_dt.Columns.Add(temp);
            }
            
            /* loop through data tables looking for joinable tuples */
            int leftColIndex = dataLeft.Columns.IndexOf(m_fieldLeft);
            int rightColIndex = dataRight.Columns.IndexOf(m_fieldRight);
            Boolean add = false;

            foreach (DataRow dL in dataLeft.Rows)
            {
                Object[] leftVals = dL.ItemArray;

                string leftStr = string.Empty;
                int leftInt = 0;

                foreach (DataRow dR in dataRight.Rows)
                {
                    Object[] rightVals = dR.ItemArray;

                    string rightStr = string.Empty;
                    int rightInt = 0;
                    add = false;

                    /* comparisons */
                    if (m_type.CompareTo("str") == 0)
                    {
                        leftStr = (string)leftVals[leftColIndex];
                        rightStr = (string)rightVals[rightColIndex];

                        switch (m_operation)
                        {
                            case "eq":
                                if (leftStr.CompareTo(rightStr) == 0)
                                    add = true;
                                break;
                            default:
                                break;
                        } /* end switch on operation */
                    }
                    else // int
                    {
                        leftInt = (int)leftVals[leftColIndex];
                        rightInt = (int)rightVals[rightColIndex];

                        switch (m_operation)
                        {
                            case "eq":
                                if (leftInt == rightInt)
                                    add = true;
                                break;
                            case "gt":
                                if (leftInt > rightInt)
                                    add = true;
                                break;
                            case "lt":
                                if (leftInt < rightInt)
                                    add = true;
                                break;
                            case "gte":
                                if (leftInt >= rightInt)
                                    add = true;
                                break;
                            case "lte":
                                if (leftInt <= rightInt)
                                    add = true;
                                break;
                            default:
                                break;
                        } /* end switch on operation */
                    }

                    if (add)
                    {
                        /* create row and add to m_results */
                        /* note columns were added left to right */
                        DataRow newRow = m_dt.NewRow();

                        List<object> newValues = new List<object>();

                        newValues.AddRange(leftVals);
                        newValues.AddRange(rightVals);

                        // newValues should contain new tuple
                        int i = 0;
                        for (i = 0; i < m_dt.Columns.Count; i++)
                        {
                            newRow[i] = newValues.ToArray()[i];
                        }

                        m_dt.Rows.Add(newRow);
                    } /* end of if add */

                } /* end inner foreach */
            } /* end outer foreach */
        }

        public DataTable cloneSchema()
        {
            return m_dt.Clone();
        }

        public Boolean hasMore()
        {
            Boolean success = false;

            if (m_dt.Rows.Count > m_current_tuple)
                success = true;

            return success;
        }

        public DataRow next()
        {
            DataRow dr = m_dt.Rows[m_current_tuple];
            m_current_tuple++;

            return dr;
        }

        public DataColumnCollection columns()
        {
            return m_dt.Columns;
        }

        public void close()
        {
            m_dt.Clear();
        }

        private string m_fieldLeft;
        private string m_fieldRight;
        private string m_operation;
        private string m_type;
        private DataTable m_dt;
        private int m_current_tuple;
    }
}
