using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class project
    {
        /* fields, empty list is * */
        public project(List<string> fields)
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

            m_dt = data.Copy();

            List<string> columnnamestoremove = new List<string>();

            if (m_f.Count > 0)
            {
                /* Skim off the columns not included */
                foreach (DataColumn d in m_dt.Columns)
                {
                    if (!m_f.Contains(d.ColumnName))
                    {
                        columnnamestoremove.Add(d.ColumnName);
                    }
                }

                foreach (string s in columnnamestoremove)
                {
                    m_dt.Columns.Remove(s);
                }
            }
            
            /* else means (*) */
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

        public DataTable cloneSchema()
        {
            return m_dt.Clone();
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
