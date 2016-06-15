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

            Dictionary<string, int> uniqueTermsDict = new Dictionary<string, int>();
            Dictionary<string, int> dfTermsDict = new Dictionary<string, int>();
            Dictionary<string, double> idfTermsDict = new Dictionary<string, double>();
            List<Dictionary<string, int>> termDictPerInput = new List<Dictionary<string, int>>();
            List<int> fileSizes = new List<int>();

            StreamWriter output;
            List<string> stopWords = new List<string>();
            DateTime start = DateTime.Now;

            // Process Input Parameters
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

            if (!indexdirtmpinfo.Exists)
            {
                System.Console.WriteLine("Creating /tmp directory");
                indexdirtmpinfo.Create();
            }
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
            int fileIndex = 0;
            List<FileInfo> srcfilelist = srcdirinfo.GetFiles("*.html").ToList();
            foreach (FileInfo file in srcfilelist)
            {
                HTMLParser fileTerms = new HTMLParser(file.FullName);
                StringBuilder newName = new StringBuilder(file.Name);
                fileSizes.Add(0);

                newName.Replace("html", "txt");
                StringBuilder outputpath = new StringBuilder(indexdirtmpinfo.FullName + "\\" + newName.ToString());

                if (File.Exists(outputpath.ToString()))
                {
                    File.Delete(outputpath.ToString());
                }

                // Parse the File (the output is a set of terms)
                Dictionary<string, int> localTermDict = new Dictionary<string, int>(fileTerms.tokenize());
                Dictionary<string, int> cleanTermDict = new Dictionary<string, int>();
                // have to use separate because it doesn't like it when i edit the primary while looping

                // Write out results to tmp files
                output = new StreamWriter(outputpath.ToString(), false);

                IOrderedEnumerable<KeyValuePair<string, int>> termssortedhashlist =
                    (from entry in localTermDict orderby entry.Key ascending select entry);
                foreach (KeyValuePair<string, int> k in termssortedhashlist)
                {
                    fileSizes[fileIndex] += k.Value;

                    if (!stopWords.Contains(k.Key))
                    {
                        output.WriteLine(k.Key + " : " + k.Value);

                        cleanTermDict.Add(k.Key, k.Value);

                        // Calculate the DF for each Term
                        if (dfTermsDict.ContainsKey(k.Key))
                        {
                            // indicating we found it in another doc
                            dfTermsDict[k.Key] += 1;
                        }
                        else
                        {
                            dfTermsDict.Add(k.Key, 1);
                        }

                        if (uniqueTermsDict.ContainsKey(k.Key))
                        {
                            uniqueTermsDict[k.Key] += k.Value;
                        }
                        else
                        {
                            uniqueTermsDict.Add(k.Key, k.Value);
                        }
                    }
                }
                output.Close();

                fileIndex++;
                termDictPerInput.Add(cleanTermDict);
            } // end foreach input file
            #endregion

            // fileSizes has the total number of terms for each input file (including stop words, etc)
            // termDictPerInput has the total terms and their frequencies per document (in document order)
            // dfTermsDict has all the document frequencies for each term
            // uniqueTerms has all the terms and their frequencies

            // Remove wors which only appear once in the corpus
            #region CleanTermsLists

            IEnumerable<KeyValuePair<string, int>> reallyUniqueTerms =
                (from entry in uniqueTermsDict where entry.Value == 1 select entry);

            foreach (KeyValuePair<string, int> k in reallyUniqueTerms)
            {
                dfTermsDict.Remove(k.Key);

                foreach (Dictionary<string, int> d in termDictPerInput)
                {
                    d.Remove(k.Key);
                }
            }
            
            #endregion

            // Computer the IDF for each term in one pass
            #region ComputeIDF
            int totalDoc = termDictPerInput.Count;
            foreach (KeyValuePair<string, int> k in dfTermsDict)
            {
                idfTermsDict.Add(k.Key, Math.Log10((double)totalDoc / (double)k.Value));
            }
            #endregion

            // Set up for end of processing print out
            #region RemainingDataProcessing

            int dictIndex = 0;
            foreach (FileInfo file in srcfilelist)
            {
                StringBuilder newName = new StringBuilder(file.Name);
                newName.Replace("html", "txt");

                StringBuilder outputpath = new StringBuilder(indexdirinfo.FullName + "\\" + newName.ToString());

                if (File.Exists(outputpath.ToString()))
                {
                    File.Delete(outputpath.ToString());
                }

                // Write out results to Permanent Files
                output = new StreamWriter(outputpath.ToString(), false);

                IOrderedEnumerable<KeyValuePair<string, int>> sortedTermsbyAlpha =
                (from entry in termDictPerInput[dictIndex] orderby entry.Key ascending select entry);

                foreach (KeyValuePair<string, int> k in sortedTermsbyAlpha)
                {
                    // Normalize Term Weights
                    double normWeight = (double)k.Value / (double)fileSizes[dictIndex];
                    double termWeight = normWeight * idfTermsDict[k.Key];

                    output.WriteLine(k.Key + " : " + termWeight.ToString());
                }
                output.Close();

                dictIndex++;
            }

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
            #endregion

            DateTime stop = DateTime.Now;
            Console.WriteLine("Total time: " + (stop - start).ToString());
        }
    }
}
