using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TrinkleSearchEngine
{
    class Program
    {
        static void Main(string[] args)
        {
            StringBuilder srcdirpath = new StringBuilder(256);
            StringBuilder indexdirpath = new StringBuilder(256);
            StringBuilder indexdirtmppath = new StringBuilder(256);

            // globalTermsDict is the set of all terms and their global frequencies
            Dictionary<string, int> globalTermsDict = new Dictionary<string, int>();

            // idfTermsDict to calculated the idf for each term
            Dictionary<string, double> idfTermsDict = new Dictionary<string, double>();

            // termDocMatrix will tell us which documents have which term, by term
            // NOTE: Awesomely enough using this to find occurences cut the time to process 503 files by more than half
            // Before we were going through each document asking if it contained the term; now we just know a priori
            // Also used to calculate document frequencies
            Dictionary<string, List<string>> termDocMatrix = new Dictionary<string, List<string>>();

            // termsPerDoc is a list of term hashes for each document (term=>tf)
            Dictionary<string, Dictionary<string, int>> termsPerDoc = new Dictionary<string, Dictionary<string, int>>();
            
            // fileSizes holds the total count of all terms including stop words
            Dictionary<string, int> fileSizes = new Dictionary<string, int>();

            // stopWords is the set of stopwords
            List<string> stopWords = new List<string>();

            StreamWriter output;
            StreamWriter postings;
            
            DateTime start = DateTime.Now;

            // Note: We now use a document ID to identify the hash list for each document
            //       and the size of each document.  This hash of hashes is really quick.
            //       I would imagine it is pointer to a pointer construction.  Very quick lookup.
            //       Timing:
            //       For redone Part 2
            //       With just changing the current codebase to use a hash lookup for each list of things
            //       Can now go through the 503 documents in 36 seconds, whereas before it was 60+

            // Process Input Parameters
            #region ProcessInput
            if (args.Length != 2)
            {
                System.Console.WriteLine("Invalid Parameters");
                return;
            }
            else
            {
                srcdirpath.Append(args[0]);
                indexdirpath.Append(args[1]);
            }
            #endregion

            // Open up the Input Directories
            #region DirectoryHandling
            DirectoryInfo srcdirinfo = new DirectoryInfo(srcdirpath.ToString());
            DirectoryInfo indexdirinfo = new DirectoryInfo(indexdirpath.ToString());

            indexdirtmppath.Append(indexdirpath.ToString() + "/tmp");

            DirectoryInfo indexdirtmpinfo = new DirectoryInfo(indexdirtmppath.ToString());

            if (!srcdirinfo.Exists)
            {
                System.Console.WriteLine("Directory does not appear to exist");
                return;
            }

            if (!indexdirinfo.Exists)
            {
                System.Console.WriteLine("Creating /index directory");
                indexdirinfo.Create();
            }

            //if (!indexdirtmpinfo.Exists)
            //{
            //    System.Console.WriteLine("Creating /tmp directory");
            //    indexdirtmpinfo.Create();
            //}
            #endregion

            // Glob in all stop words
            #region StopWords
            // We're going to currently assume the stopwords.txt file is with the src files
            List<FileInfo> stopFileList = srcdirinfo.GetFiles("stoplist*").ToList();
            foreach (FileInfo file in stopFileList)
            {
                //its, lets, well, were are not duplicated
                HTMLParser stopW = new HTMLParser(file.FullName);
                Dictionary<string, int> s = new Dictionary<string, int>(stopW.tokenize());

                foreach (string str in s.Keys)
                {
                    stopWords.Add(str);
                }
            }

            #endregion

            // Iterate over all the HTML Files from the Source Directory
            #region IterateOverInputFiles
            List<FileInfo> srcfilelist = srcdirinfo.GetFiles("*.html").ToList();
            foreach (FileInfo file in srcfilelist)
            {
                HTMLParser fileTerms = new HTMLParser(file.FullName);
                StringBuilder newName = new StringBuilder(file.Name);

                newName.Replace("html", "txt");                
                string docID = newName.Replace(".txt", "").ToString();
                fileSizes.Add(docID, 0);

                // Parse the File (the output is a set of terms)
                Dictionary<string, int> localTermDict = new Dictionary<string, int>(fileTerms.tokenize());
                Dictionary<string, int> cleanTermDict = new Dictionary<string, int>();
                // have to use separate because it doesn't like it when i edit the primary while looping

                IOrderedEnumerable<KeyValuePair<string, int>> termssortedhashlist =
                    (from entry in localTermDict orderby entry.Key ascending select entry);
                foreach (KeyValuePair<string, int> k in termssortedhashlist)
                {
                    fileSizes[docID] += k.Value;

                    if (!stopWords.Contains(k.Key))
                    {
                        cleanTermDict.Add(k.Key, k.Value);

                        // this will hold all terms and their global counts
                        // so we can track down singletons
                        if (globalTermsDict.ContainsKey(k.Key))
                        {
                            globalTermsDict[k.Key] += k.Value;
                        }
                        else
                        {
                            globalTermsDict.Add(k.Key, k.Value);
                        }

                        // this is our term document matrix in memory
                        if (termDocMatrix.ContainsKey(k.Key))
                        {
                            termDocMatrix[k.Key].Add(docID);
                        }
                        else
                        {
                            termDocMatrix.Add(k.Key, new List<string>());
                            termDocMatrix[k.Key].Add(docID);
                        }
                    }
                }

                termsPerDoc.Add(docID, cleanTermDict);
            } // end foreach input file
            #endregion
            
            // Remove wors which only appear once in the corpus
            #region CleanTermsLists

            IEnumerable<KeyValuePair<string, int>> reallyUniqueTerms =
                (from entry in globalTermsDict where entry.Value == 1 select entry);

            foreach (KeyValuePair<string, int> k in reallyUniqueTerms)
            {
                // we know which docs have this unique term, can eliminate quickly!
                foreach (string dID in termDocMatrix[k.Key])
                {
                    termsPerDoc[dID].Remove(k.Key);
                }

                termDocMatrix.Remove(k.Key);
            }
            #endregion

            //StringBuilder debugpath = new StringBuilder(indexdirinfo.FullName + "\\");
            //foreach (KeyValuePair<string, Dictionary<string, int>> k in termsPerDoc)
            //{
            //    output = new StreamWriter(debugpath.ToString() + k.Key + ".txt", false);

            //    foreach (KeyValuePair<string, int> d in k.Value)
            //    {
            //        output.WriteLine(d.Key);
            //    }

            //    output.Close();
            //}

            // Computer the IDF for each term in one pass
            #region ComputeIDF
            int totalDoc = termsPerDoc.Count;
            Console.WriteLine("Computed " + totalDoc.ToString() + " input files");
            foreach (KeyValuePair<string, List<string>> k in termDocMatrix)
            {
                idfTermsDict.Add(k.Key, Math.Log10((double)totalDoc / (double)k.Value.Count));
            }
            #endregion

            // Could Write out Temporary Files Here
            // Would be beneficial to write out term document matrix

            // Print out Dictionary
            #region BuildDictionaryAndPostingsFile
            // Each fixed length record contains:
            // word(35 bytes), df(5 bytes), location of first record in posting file(5 bytes)
            StringBuilder dictionarypath = new StringBuilder(indexdirinfo.FullName + "\\dictionary.txt");
            StringBuilder postingsfilepath = new StringBuilder(indexdirinfo.FullName + "\\postings.txt");

            output = new StreamWriter(dictionarypath.ToString(), false);
            postings = new StreamWriter(postingsfilepath.ToString(), false);

            int recordIndex = 0;

            IOrderedEnumerable<KeyValuePair<string, List<string>>> sortedTermsfromMatrix =
                (from entry in termDocMatrix orderby entry.Key ascending select entry);

            foreach (KeyValuePair<string, List<string>> k in sortedTermsfromMatrix)
            {
                output.WriteLine(k.Key.PadRight(35) + ":" + k.Value.Count.ToString().PadLeft(5) + ":" + recordIndex.ToString().PadLeft(7));

                // instantly grab all occurences of the key and add to the postings file.
                foreach (string dID in k.Value)
                {
                    // so we know the docID of each document with the thing
                    double normWeight = (double)termsPerDoc[dID][k.Key] / (double)fileSizes[dID];
                    double termWeight = normWeight * idfTermsDict[k.Key];

                    string tmp = String.Format("{0:.######}", termWeight);

                    // works well if the max term weight is 9.999999
                    if (termWeight < 1.0)
                    {
                        tmp = tmp.Insert(0, "0");
                    }

                    postings.WriteLine(dID.PadRight(10) + ":" + tmp.PadRight(9, '0'));

                    recordIndex += 1;
                }
            }
            postings.Close();
            output.Close();
            #endregion

            //totaltermlist.Sort(
            //    delegate(KeyValuePair<string, string> firstPair, KeyValuePair<string, string> nextPair)
            //    {
            //        return firstPair.Value.CompareTo(nextPair.Value);
            //    }
            //);
            //totaltermlist.Sort((firstPair, nextPair) =>
            //{
            //    return firstPair.Value.CompareTo(nextPair.Value);
            //}
            //);

            DateTime stop = DateTime.Now;
            Console.WriteLine("Total time: " + (stop - start).ToString());
        }
    }
}
