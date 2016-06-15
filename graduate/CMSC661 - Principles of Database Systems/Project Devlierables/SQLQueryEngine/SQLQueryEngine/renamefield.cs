using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class renamefield
    {
        /* fields, empty list is * */
        public renamefield(string fieldname, string newname)
        {
            this.m_oldfield = fieldname;
            this.m_newfield = newname;            
        }
        
        public void open(DataTable data)
        {
            foreach (DataColumn dc in data.Columns)
            {
                if (dc.ColumnName.CompareTo(m_oldfield) == 0)
                {
                    dc.ColumnName = m_newfield;
                }
            }
        }

        private string m_oldfield;
        private string m_newfield;                
    }
}
