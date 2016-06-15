using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace TrinkleSearchEngine
{
    class Query
    {
        public Query(string query)
        {
            // Queries must not have repeated terms
            Regex r = new Regex("(?<term>.+?)=(?<weight>.+)");

            double weightsum = 0.0;

            this.m_query = query;
            this.m_terms = new Dictionary<string, double>();
            this.m_results = new Dictionary<string, double>();

            // Break apart the query into terms with their weights
            List<string> termGroups = new List<string>(query.Split(' '));
            foreach (string t in termGroups)
            {
                Match m = r.Match(t);

                if (m.Success)
                {
                    double weight = Double.Parse(m.Groups["weight"].Value);

                    if (weight > 1.0 || weight < 0)
                    {
                        Console.WriteLine("Error: Invalid Weight for Token: " + t);
                    }
                    else
                    {
                        weightsum += weight;

                        Dictionary<string, int> breakup = new Dictionary<string, int>(HTMLParser.tokenize_string(m.Groups["term"].Value));

                        // Note if the term is kept as 1 term, the breakup is 1, and therefore the term maintains the entered weight
                        foreach (KeyValuePair<string, int> kvp in breakup)
                        {
                            this.m_terms.Add(kvp.Key, weight / breakup.Count);
                        }
                    }
                }
                else
                {
                    Console.WriteLine("Error: Incorrect Syntax");
                }
            }

            // Determine sum of values, and add extra bits to longest term
            if (weightsum < 1.0)
            {
                double extra = 1.0 - weightsum;
                string longest = string.Empty;

                // Find the longest term
                foreach (string s in this.m_terms.Keys)
                {
                    if (longest.Length < s.Length)
                    {
                        longest = String.Copy(s);
                    }
                }

                //Console.WriteLine("Adding Extra " + extra.ToString() + " to term: " + longest);

                this.m_terms[longest] += extra;
            }
            else if (weightsum > 1.0)
            {
                Console.WriteLine("Error: Total weights provided is greater than 1.0");
            }
        }

        // to query for results
        public List<string> getTokens()
        {
            return new List<string>(this.m_terms.Keys);
        }

        // return the original query to the user
        public string getQuery()
        {
            return this.m_query;
        }

        // returns the number of results (if any)
        public int getResultsCount()
        {
            return this.m_results.Count;
        }

        // sorts the results for the user
        public IOrderedEnumerable<KeyValuePair<string, double>> getResults()
        {
            IOrderedEnumerable<KeyValuePair<string, double>> sortedResults =
                (from entry in this.m_results orderby entry.Value descending select entry);

            return sortedResults;
        }

        // handles scoring documents (but they are not sorted until they're retrieved
        public void addResults(string term, RecordSet records)
        {
            double termweight = this.m_terms[term];
            Dictionary<string, double> doctfidf = records.getRecords();

            //Console.WriteLine("Term: " + term + " Weight: " + termweight.ToString());

            // for each document id in the records set, add the tf-idf value to the current doc score
            // based on the termweight
            foreach (string docID in doctfidf.Keys)
            {
                if (this.m_results.ContainsKey(docID))
                {
                    this.m_results[docID] += (termweight * doctfidf[docID]);
                }
                else
                {
                    this.m_results.Add(docID, (termweight * doctfidf[docID]));
                }

                //Console.WriteLine("DocID: " + docID + " Current Score: " + this.m_results[docID].ToString());
            }

            return;
        }

        // this keys on document Id, and maintains the accumulated score
        private Dictionary<string, double> m_results;

        // this keys on the term and returns the weight within the query
        private Dictionary<string, double> m_terms;

        // this contains the original query sent to the system
        private string m_query;
    }
}
