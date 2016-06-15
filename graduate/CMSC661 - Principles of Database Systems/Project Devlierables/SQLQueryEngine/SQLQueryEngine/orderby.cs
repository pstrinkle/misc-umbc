using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace SQLQueryEngine
{
    public class orderby
    {        
        public orderby(string field, string ordering, string dataType)
        {
            this.m_field = field;
            this.m_order = ordering;
            this.m_dataType = dataType;

            this.m_twoSort = false;

            this.m_dt = new DataTable();          
            this.m_current_tuple = 0;
        }

        public orderby(string firstfield, string firstordering, string firstdataType, 
            string secondfield, string secondordering, string seconddataType)
        {
            this.m_field = firstfield;
            this.m_order = firstordering;
            this.m_dataType = firstdataType;

            this.m_secondfield = secondfield;
            this.m_secondorder = secondordering;
            this.m_seconddataType = seconddataType;

            this.m_twoSort = true;
            
            this.m_dt = new DataTable();
            this.m_current_tuple = 0;
        }
        
        public void binAggregateopen(DataTable data)
        {
            // clean out any garbage
            m_dt.Clear();            
            m_dt = data.Clone();
            
            int fieldIndex = data.Columns.IndexOf(m_field);            

            DataSet container = new DataSet();
          
            List<string> strBinValues = new List<string>();
            List<int> intBinValues = new List<int>();
            
            /* build set of bins on first field; first pass*/
            foreach (DataRow row in data.Rows)
            {
                if (m_dataType.CompareTo("str") == 0)
                {
                    /* we are dealing with strings */
                    string value = (string)row.ItemArray[fieldIndex];

                    /* we have a bin */
                    if (container.Tables.Contains(value))
                    {
                        container.Tables[value].ImportRow(row);
                    }
                    else
                    {
                        DataTable newTable = new DataTable(value);
                        newTable = data.Clone();
                        newTable.TableName = value;

                        container.Tables.Add(newTable);                        

                        container.Tables[value].ImportRow(row);

                        /* for later sorting purposes */
                        strBinValues.Add(value);
                    }
                }
                else if (m_dataType.CompareTo("int") == 0)
                {
                    /* we are dealing with ints */
                    int value = (int)row.ItemArray[fieldIndex];

                    if (container.Tables.Contains(value.ToString()))
                    {
                        container.Tables[value.ToString()].ImportRow(row);
                    }
                    else
                    {
                        DataTable newTable = new DataTable(value.ToString());
                        newTable = data.Clone();
                        newTable.TableName = value.ToString();

                        container.Tables.Add(newTable);

                        container.Tables[value.ToString()].ImportRow(row);

                        /* for later sorting purposes */
                        intBinValues.Add(value);
                    }
                }
            } /* end of foreach on rows in Data */
            
            /* all values are in their bins */

            if (m_twoSort)
            {
                /* sort the values in each bin by second field and second ordering */
                foreach (DataTable bin in container.Tables)
                {
                    bin.DefaultView.Sort = m_secondfield + " " + m_secondorder;
                }

                /* bin contents should be sorted */
            }
            
            /* second pass */
            if (m_dataType.CompareTo("str") == 0)
            {
                /* default asc */
                strBinValues.Sort();

                if (m_order.CompareTo("desc") == 0)
                    strBinValues.Reverse();

                /* now I can pull out the tables in sorted order */
                foreach (string tableName in strBinValues)
                {
                    /* should be in sorted order */
                    foreach (DataRow row in container.Tables[tableName].Rows)
                    {
                        m_dt.ImportRow(row);
                    }

                    /* remove table from list */
                    container.Tables.Remove(tableName);
                }
            }
            else if (m_dataType.CompareTo("int") == 0)
            {                
                intBinValues.Sort(); /* default ASC */

                if (m_order.CompareTo("desc") == 0)
                    intBinValues.Reverse();
                
                /* now I can pull out the tables in sorted order */
                foreach (int tableName in intBinValues)
                {
                    /* should be in sorted order */
                    foreach (DataRow row in container.Tables[tableName.ToString()].Rows)
                    {
                        m_dt.ImportRow(row);
                    }

                    /* remove table from list */
                    container.Tables.Remove(tableName.ToString());
                }
            }
                        
            /* m_dt should be sorted by first field, first order, then second field second order */            
        }

        /* only handles strings and integers */
        public void open(DataTable data)
        {           
            /* set up a connection to the data server */
            SqlConnection sqlConn = new SqlConnection("Trusted_Connection=yes;" +
                                       "database=cmsc661; " +
                                       "connection timeout=30");
            try
            {
                sqlConn.Open();

                /* fix input data because column_names cannot have dots */
                foreach (DataColumn d in data.Columns)
                {
                    d.ColumnName = d.ColumnName.Replace(".", "_dot_");                    
                }

                this.m_field = this.m_field.Replace(".", "_dot_");

                if (this.m_twoSort)
                    this.m_secondfield = this.m_secondfield.Replace(".", "_dot_");

                /* assume we break it all into 2 blocks */
                DataTable firstBlock = new DataTable();
                DataTable secondBlock = new DataTable();

                firstBlock = data.Clone();
                secondBlock = data.Clone();

                for (int i = 0; i < data.Rows.Count; i++)
                {
                    if (i % 2 == 0)
                        firstBlock.ImportRow(data.Rows[i]);
                    else
                        secondBlock.ImportRow(data.Rows[i]);                    
                }

                firstBlock.TableName = "#temp1";
                secondBlock.TableName = "#temp2";

                StringBuilder firstInsert = new StringBuilder();
                firstInsert.Append("create table #temp1 ");
                firstInsert.Append("( ");

                StringBuilder secondInsert = new StringBuilder();
                secondInsert.Append("create table #temp2 ");
                secondInsert.Append("( ");

                int counter = 1;

                foreach (DataColumn col in data.Columns)
                {
                    firstInsert.Append(col.ColumnName + " ");
                    secondInsert.Append(col.ColumnName + " ");

                    if (col.DataType.ToString().CompareTo("System.Int32") == 0)
                    {
                        firstInsert.Append("int not null");
                        secondInsert.Append("int not null");
                    }
                    else if (col.DataType.ToString().CompareTo("System.String") == 0)
                    {
                        firstInsert.Append("varchar(15) not null");
                        secondInsert.Append("varchar(15) not null");
                    }

                    if (counter < data.Columns.Count)
                    {
                        firstInsert.Append(", ");
                        secondInsert.Append(", ");
                    }

                    counter++;
                }

                firstInsert.Append("); ");
                secondInsert.Append("); ");

                /* now I need to place them onto the data storage manager */                              
                SqlCommand firstCmd = new SqlCommand(firstInsert.ToString());
                firstCmd.Connection = sqlConn;
                firstCmd.ExecuteNonQuery();

                SqlCommand secondCmd = new SqlCommand(secondInsert.ToString());
                secondCmd.Connection = sqlConn;
                secondCmd.ExecuteNonQuery();

                StringBuilder firstInsertTuples = new StringBuilder();

                int columnCounter = 1;

                foreach (DataRow r in firstBlock.Rows)
                {
                    firstInsertTuples.Append("insert into #temp1 values (");

                    columnCounter = 1;

                    /* so we can properly quote or not quote data */
                    foreach (DataColumn d in firstBlock.Columns)
                    {
                        if (d.DataType.ToString().CompareTo("System.Int32") == 0)
                            firstInsertTuples.Append(r[d].ToString());
                        else if (d.DataType.ToString().CompareTo("System.String") == 0)
                            firstInsertTuples.Append("'" + r[d].ToString() + "'");

                        if (columnCounter < firstBlock.Columns.Count)
                            firstInsertTuples.Append(", ");

                        columnCounter++;
                    }

                    firstInsertTuples.Append(");");
                }

                SqlCommand firstBuild = new SqlCommand(firstInsertTuples.ToString());
                firstBuild.Connection = sqlConn;
                firstBuild.ExecuteNonQuery();

                StringBuilder secondInsertTuples = new StringBuilder();
                
                foreach (DataRow r in secondBlock.Rows)
                {
                    secondInsertTuples.Append("insert into #temp2 values (");

                    columnCounter = 1;

                    /* so we can properly quote or not quote data */
                    foreach (DataColumn d in secondBlock.Columns)
                    {
                        if (d.DataType.ToString().CompareTo("System.Int32") == 0)
                            secondInsertTuples.Append(r[d].ToString());
                        else if (d.DataType.ToString().CompareTo("System.String") == 0)
                            secondInsertTuples.Append("'" + r[d].ToString() + "'");

                        if (columnCounter < firstBlock.Columns.Count)
                            secondInsertTuples.Append(", ");

                        columnCounter++;
                    }

                    secondInsertTuples.Append(");");
                }

                SqlCommand secondBuild = new SqlCommand(secondInsertTuples.ToString());
                secondBuild.Connection = sqlConn;
                secondBuild.ExecuteNonQuery();

                /* free memory */
                firstBlock.Clear();
                secondBlock.Clear();

                /* second pass */
                StringBuilder queryFirstBlock = new StringBuilder();
                queryFirstBlock.Append("select * from #temp1 order by " + this.m_field + " " + this.m_order);

                StringBuilder querySecondBlock = new StringBuilder();
                querySecondBlock.Append("select * from #temp2 order by " + this.m_field + " " + this.m_order);

                int firstIndex = data.Columns.IndexOf(this.m_field);
                int secondIndex = -1;

                if (this.m_twoSort)
                {
                    queryFirstBlock.Append(", " + this.m_secondfield + " " + this.m_secondorder);
                    querySecondBlock.Append(", " + this.m_secondfield + " " + this.m_secondorder);

                    secondIndex = data.Columns.IndexOf(this.m_secondfield);
                }

                /* then I need to read them back in sorted order */
                DataSet ds = new DataSet();

                SqlCommand firstCommand = new SqlCommand(queryFirstBlock.ToString(), sqlConn);
                SqlCommand secondCommand = new SqlCommand(querySecondBlock.ToString(), sqlConn);

                SqlDataAdapter sqlDA = new SqlDataAdapter();
                sqlDA.SelectCommand = firstCommand;

                sqlDA.Fill(ds, "temp1");

                sqlDA.SelectCommand = secondCommand;

                sqlDA.Fill(ds, "temp2");

                m_dt = firstBlock.Clone(); /* because data.Clone() will give with dots */

                /* then I need to walk through both merging into one list */

                int total_count = data.Rows.Count;
                Boolean firstRow = false;
                Boolean remaining = false;
                
                while (m_dt.Rows.Count < total_count && remaining == false)
                {
                    firstRow = false;

                    /* if there are tuples to compare in both */
                    if (ds.Tables[0].Rows.Count > 0 && ds.Tables[1].Rows.Count > 0)
                    {
                        if (m_order.CompareTo("desc") == 0)
                        {
                            if (m_dataType.CompareTo("int") == 0)
                            {
                                if ((int)ds.Tables[0].Rows[0][firstIndex] > (int)ds.Tables[1].Rows[0][firstIndex])
                                {
                                    m_dt.ImportRow(ds.Tables[0].Rows[0]);
                                    firstRow = true;
                                }
                                else /* if a < b or a == b we just take b */
                                {
                                    m_dt.ImportRow(ds.Tables[1].Rows[0]);
                                    firstRow = false;
                                }                                
                            }
                            else if (m_dataType.CompareTo("str") == 0)
                            {
                                if (((string)ds.Tables[0].Rows[0][firstIndex]).CompareTo((string)ds.Tables[1].Rows[0][firstIndex]) == 1)
                                {
                                    m_dt.ImportRow(ds.Tables[0].Rows[0]);
                                    firstRow = true;
                                }
                                else
                                {
                                    m_dt.ImportRow(ds.Tables[1].Rows[0]);
                                    firstRow = false;
                                }
                            }
                        }
                        else /* order is asc */
                        {
                            if (m_dataType.CompareTo("int") == 0)
                            {
                                if ((int)ds.Tables[0].Rows[0][firstIndex] < (int)ds.Tables[1].Rows[0][firstIndex])
                                {
                                    m_dt.ImportRow(ds.Tables[0].Rows[0]);
                                    firstRow = true;
                                }
                                else /* if a > b or a == b we just take b */
                                {
                                    m_dt.ImportRow(ds.Tables[1].Rows[0]);
                                    firstRow = false;
                                }
                            }
                            else if (m_dataType.CompareTo("str") == 0)
                            {
                                if (((string)ds.Tables[0].Rows[0][firstIndex]).CompareTo((string)ds.Tables[1].Rows[0][firstIndex]) == -1)
                                {
                                    m_dt.ImportRow(ds.Tables[0].Rows[0]);
                                    firstRow = true;
                                }
                                else
                                {
                                    m_dt.ImportRow(ds.Tables[1].Rows[0]);
                                    firstRow = false;
                                }
                            }
                        }
                    }
                    else /* import remaining */
                    {
                        remaining = true;
                    }

                    /* pull off first tuple from whichever */
                    if (firstRow && !remaining)
                        ds.Tables[0].Rows.Remove(ds.Tables[0].Rows[0]);
                    else if (!firstRow && !remaining)
                        ds.Tables[1].Rows.Remove(ds.Tables[1].Rows[0]);
                }

                if (remaining) /* pick up any remaining tuples */
                {                    
                    while (ds.Tables[0].Rows.Count > 0)
                    {
                        m_dt.ImportRow(ds.Tables[0].Rows[0]);
                        ds.Tables[0].Rows.Remove(ds.Tables[0].Rows[0]);
                    }

                    while (ds.Tables[1].Rows.Count > 0)
                    {
                        m_dt.ImportRow(ds.Tables[1].Rows[0]);
                        ds.Tables[1].Rows.Remove(ds.Tables[1].Rows[0]);
                    }
                }

                /* add second sorting */
                if (this.m_twoSort)
                    m_dt.DefaultView.Sort = this.m_field + " " + this.m_order + ", " + this.m_secondfield + " " + this.m_secondorder;                
            }
            catch (SqlException sqlE)
            {
                Console.WriteLine(sqlE.Message.ToString());
            }

            /* close out our connection */
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
  
            /* fix tuples placing dots back in */
            foreach (DataColumn d in m_dt.Columns)
            {
                d.ColumnName = d.ColumnName.Replace("_dot_", ".");
            }

            /* fix tuples of reference object so I don't have to fix this in each query */
            foreach (DataColumn d in data.Columns)
            {
                d.ColumnName = d.ColumnName.Replace("_dot_", ".");
            }

            this.m_field = this.m_field.Replace("_dot_", ".");

            if (this.m_twoSort)
                this.m_secondfield = this.m_secondfield.Replace("_dot_", ".");

            /* test sorting */
            Aux.printschema(m_dt.Columns);

            foreach (DataRow r in m_dt.Rows)
                Aux.printrow(r);
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
        private string m_order;
        private string m_dataType;
        private string m_secondfield;
        private string m_secondorder;
        private string m_seconddataType;
        private Boolean m_twoSort;
        private DataTable m_dt;
        private int m_current_tuple;        
    }
}
