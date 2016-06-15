using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TrinkleSearchEngine
{
    class RecordSet
    {
        public RecordSet(string record_as_string)
        {
            int recordCnt = record_as_string.Length / 22;

            m_records = new Dictionary<string, double>(recordCnt);


            // split the records into pieces
            for (int i = 0; i < recordCnt; i++)
            {
                string tmprecord = record_as_string.Substring(0, 20);
                record_as_string = record_as_string.Remove(0, 22);

                string docID = tmprecord.Substring(0, 10).Trim();
                double tfidf = Double.Parse(tmprecord.Substring(11, 9).Trim());

                //Console.WriteLine("DocID: " + docID + " Tf-idf: " + tfidf.ToString());

                m_records.Add(docID, tfidf);
            }
        }

        public Dictionary<string, double> getRecords()
        {
            return this.m_records;
        }

        private Dictionary<string, double> m_records;
    }
}
