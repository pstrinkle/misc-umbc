using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SQLQueryEngine
{
    public class StatisticsManager
    {
        /* given the relation names it will auto build keys for common stats */
        public StatisticsManager(List<string> relations)
        {
            m_stats = new Dictionary<string, int>();
            scan sc = null;

            foreach (string s in relations)
            {
                /* build generic statistics keys and values */
                /* use string builders */

                sc = new scan(s);

                sc.open();

                StringBuilder sb = new StringBuilder();

                sb.Append("count.");
                sb.Append(s);

                int relationSize = sc.outSize();

                /* add statistic */
                m_stats.Add(sb.ToString(), relationSize);

                DataTable sample = new DataTable();

                sample = sc.cloneSchema();

                int buildsample = 0;

                while (sc.hasMore() && buildsample < 5)
                {
                    sample.ImportRow(sc.next());
                    buildsample++;
                }

                List<string> values = new List<string>();

                for (int j = 0; j < sample.Columns.Count; j++)
                {
                    /* for each column calculate distinctness and store */
                    string colName = sample.Columns[j].ColumnName;

                    values.Clear();

                    /* 5 is the sample size; could make #define so you can change ir
                     * or maybe even user specified */
                    int sampleSize = (5 > sample.Rows.Count) ? sample.Rows.Count : 5;

                    for (int i = 0; i < sampleSize; i++)
                    {
                        //DataRow temp = sample.Rows[i];

                        object value = sample.Rows[i][j];

                        StringBuilder valPair = new StringBuilder();

                        valPair.Append(colName + value.ToString());

                        /* new value */
                        if (!values.Contains(valPair.ToString()))
                        {
                            values.Add(valPair.ToString());
                        }
                    }

                    StringBuilder newstat = new StringBuilder();

                    newstat.Append("distinct" + "." + s + "." + colName);

                    int newstatValue = values.Count;

                    m_stats.Add(newstat.ToString(), newstatValue);
                }

                sample.Clear();

                sc.close();
            } /* end for each relation specified */

        }

        /* technically if you just do m_stats[key] = value it'll auto-add if it doesn't exist */
        /* will add missing keys */
        public void updateStat(string key, int value)
        {
            if (m_stats.ContainsKey(key))
                m_stats[key] = value;
            else
                m_stats.Add(key, value);
        }

        /* will add missing keys */
        public void batchUpdateStats(Dictionary<string, int> updates)
        {
            foreach (KeyValuePair<string, int> kvp in updates)
            {
                if (m_stats.ContainsKey(kvp.Key))
                    m_stats[kvp.Key] = kvp.Value;
                else
                    m_stats.Add(kvp.Key, kvp.Value);
            }
        }

        public int retrieveStat(string key)
        {
            int retVal = -1;

            if (m_stats.ContainsKey(key))
                retVal = m_stats[key];

            return retVal;
        }

        public void addStat(string key, int value)
        {
            m_stats.Add(key, value);
        }

        public void killStat(string key)
        {
            m_stats.Remove(key);
        }

        public void clearStats()
        {
            m_stats.Clear();
        }

        public void setZeroAll()
        {
            foreach (string key in m_stats.Keys)
            {
                m_stats[key] = 0;
            }
        }

        private Dictionary<string, int> m_stats;
    }
}
