using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class selectALL
    {        
        /* could make it take a list of values but this is optimized */
        public selectALL(string field, string operation, int value)
        {
            this.m_op = operation;
            this.m_field = field;
            this.m_value = value;            
            this.m_dt = new DataTable();
            this.m_current_tuple = 0;
        }

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

                if (m_op.CompareTo("gt") == 0)
                {
                    if ((int)obs[columnIndex] > m_value)
                        add = true;
                }
                else if (m_op.CompareTo("lt") == 0)
                {
                    if ((int)obs[columnIndex] < m_value)
                        add = true;
                }

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
        }

        private string m_field;
        private int m_value;
        private string m_op;
        private DataTable m_dt;
        private int m_current_tuple;
    }
}
