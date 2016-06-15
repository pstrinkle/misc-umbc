using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class distinct
    {
        /* fields */
        /* Currently only runs distinct on 1 field */
        public distinct(List<string> fields)
        {
            m_f = new List<string>();

            foreach (string s in fields)
            {
                m_f.Add(s);
            }

            this.m_dt = new DataTable();
            this.m_current_tuple = 0;
        }

        public void open(DataTable data)
        {
            // clean out any garbage
            m_dt.Clear();

            m_dt = data.Clone();

            List<int> columnIndices = new List<int>();
            List<string> seenValues = new List<string>();

            /* getting all columns we care about */
            foreach (string s in m_f)
            {
                columnIndices.Add(data.Columns.IndexOf(s));
            }

            Boolean add = false;

            /* go through each row */
            foreach (DataRow dr in data.Rows)
            {
                Object[] obs = dr.ItemArray;
                string values = "";

                add = false;

                /* is this unique across all required columns */
                foreach (int index in columnIndices)
                {
                    values += obs[index].ToString();
                }

                if (!seenValues.Contains(values))
                {
                    add = true;
                    seenValues.Add(values);
                }

                /* choose to import row */
                if (add)
                {
                    m_dt.ImportRow(dr);
                }
            }
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
            m_f.Clear();
        }

        private List<string> m_f;
        private DataTable m_dt;
        private int m_current_tuple;
    }
}
