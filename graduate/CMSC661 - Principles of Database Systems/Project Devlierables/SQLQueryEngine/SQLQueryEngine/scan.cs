using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace SQLQueryEngine
{
    public class scan
    {
        /* Sets up class */
        public scan(string tablename)
        {
            this.m_tablename = tablename;
            this.m_dt = new DataTable(m_tablename);
            this.m_current_tuple = 0;
        }

        /* opens database connection and retreives tuples from tablename*/
        public void open()
        {
            StringBuilder cmdString = new StringBuilder();
            cmdString.Append("select * from ");
            cmdString.Append(m_tablename);
            cmdString.Append(";");

            SqlConnection sqlConn = new SqlConnection("Trusted_Connection=yes;" +
                                       "database=cmsc661; " +
                                       "connection timeout=30");

            SqlCommand command = new SqlCommand(cmdString.ToString(), sqlConn);

            SqlDataAdapter sqlDA = new SqlDataAdapter();
            sqlDA.SelectCommand = command;

            DataSet ds = null;

            try
            {
                sqlConn.Open();

                ds = new DataSet();
                sqlDA.Fill(ds, m_tablename);
            }
            catch (SqlException sqlE)
            {
                Console.WriteLine(sqlE.Message.ToString());
            }

            /* copy data from ds to our records */
            m_dt = ds.Tables[0].Copy();

            try
            {
                sqlConn.Close();
            }
            catch (SqlException sqlE)
            {
                Console.WriteLine(sqlE.Message.ToString());
            }
            finally
            {
                sqlConn.Close();
            }
        }

        public DataTable cloneSchema()
        {
            return m_dt.Clone();
        }

        /* returns next tuple */
        public DataRow next()
        {
            DataRow dr = m_dt.Rows[m_current_tuple];

            m_current_tuple++;

            return dr;
        }

        /* contains more tuples? */
        public Boolean hasMore()
        {
            Boolean success = false;

            /* there are more rows than the current tuple count */
            if (m_dt.Rows.Count > m_current_tuple)
                success = true;

            return success;
        }

        /* frees memory */
        public void close()
        {
            m_dt.Clear();
        }

        public int outSize()
        {
            return m_dt.Rows.Count;
        }

        private DataTable m_dt;
        private int m_current_tuple;
        private string m_tablename;
    }
}
