using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Text.RegularExpressions;

namespace SQLQueryEngine
{
    public class select
    {
        public select(string fieldname, string operation, int value)
        {
            this.m_field = fieldname;
            this.m_op = operation;
            this.m_intValue = value;

            this.m_integerCmp = true;

            this.m_current_tuple = 0;
            this.m_dt = new DataTable();
        }

        public select(string fieldname, string operation, string value)
        {
            /* will handle LIKE */
            this.m_field = fieldname;
            this.m_op = operation;
            this.m_strValue = value;

            this.m_integerCmp = false;

            this.m_current_tuple = 0;
            this.m_dt = new DataTable();
        }

        /* currently only handles integer comparisons */
        public void open(DataTable data)
        {
            // clean out any garbage
            m_dt.Clear();
            m_dt = data.Clone();

            int columnIndex = data.Columns.IndexOf(m_field);
            Boolean add = false;


            foreach (DataRow dr in data.Rows)
            {
                Object[] obs = dr.ItemArray;

                add = false;

                if (m_integerCmp)
                {
                    if (m_op.CompareTo("gte") == 0)
                    {
                        if ((int)obs[columnIndex] >= m_intValue)
                            add = true;
                    }
                    else if (m_op.CompareTo("lte") == 0)
                    {
                        if ((int)obs[columnIndex] <= m_intValue)
                            add = true;
                    }
                    else if (m_op.CompareTo("gt") == 0)
                    {
                        if ((int)obs[columnIndex] > m_intValue)
                            add = true;
                    }
                    else if (m_op.CompareTo("lt") == 0)
                    {
                        if ((int)obs[columnIndex] < m_intValue)
                            add = true;
                    }
                    else if (m_op.CompareTo("eq") == 0)
                    {
                        if ((int)obs[columnIndex] == m_intValue)
                            add = true;
                    }
                    else // neq
                    {
                        if ((int)obs[columnIndex] != m_intValue)
                            add = true;
                    }
                }
                else
                {
                    if (m_op.CompareTo("like") == 0)
                    {
                        Regex likeness = new Regex(m_strValue);

                        Match m = likeness.Match((string)obs[columnIndex]);
        
                        if (m_op.CompareTo("like") == 0)
                        {
                            if (m.Success)
                                add = true;
                        }
                        else // not like
                        {
                                /* might just do this with regex feed */
                        }
                    }
                    else if (m_op.CompareTo("eq") == 0)
                    {
                        if (m_strValue.CompareTo((string)obs[columnIndex]) == 0)
                            add = true;
                    }
                }

                /* choose to import row */
                if (add)
                {
                    m_dt.ImportRow(dr);
                }
            } /* end of foreach */
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

        public void close()
        {
            m_dt.Clear();
        }

        private string m_field;
        private string m_op;
        private int m_intValue;
        private string m_strValue;

        private Boolean m_integerCmp;

        private DataTable m_dt;
        private int m_current_tuple;
    }
}
