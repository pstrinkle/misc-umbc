using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TrinkleSearchEngine
{    
    class HTMLParser
    {
        enum ParserState
        {
            Initialized = 0,
            InsideTag,
            InsideToken,
            InsideSpecial
        };

        public HTMLParser(string filename)
        {
            this.m_filename = filename;
            this.initialize();
        }

        private void initialize()
        {
            if (File.Exists(this.m_filename))
            {
                this.m_termfrequency = new Dictionary<string, int>();
                this.m_state = ParserState.Initialized;
            }
            else
            {
                this.m_filestream = null;
            }

            return;
        }

        // this reads through the file and tokenizes all words
        public Dictionary<string, int> tokenize()
        {
            this.m_state = ParserState.InsideToken;
            int bytesRead = 0;
            char b;
            StringBuilder newToken = new StringBuilder();

            // open file
            this.m_filestream = File.Open(this.m_filename, FileMode.Open, FileAccess.Read);

            // tokenize the file
            while (bytesRead < this.m_filestream.Length)
            {
                bytesRead++;

                b = (char)this.m_filestream.ReadByte();

                // toLower
                if ('A' <= b && b <= 'Z')
                {
                    b += ' ';
                }

                // process byte
                switch (b)
                {
                    case '<':
                        if (this.m_state == ParserState.InsideToken)
                        {
                            // end current token
                            if (newToken.Length > 1)
                            {
                                // add token! (it currently will possibly have periods!
                                string term = newToken.ToString();

                                // because we can only be inside special if we 
                                // were insidetoken; therefore this token ends in special
                                if (this.m_termfrequency.ContainsKey(term))
                                {
                                    this.m_termfrequency[term] += 1;
                                }
                                else
                                {
                                    this.m_termfrequency.Add(term, 1);
                                }

                                newToken = new StringBuilder();
                            }

                            this.m_state = ParserState.InsideTag;
                        }
                        else if (this.m_state != ParserState.InsideTag)
                        {
                            // we just started a tag
                            this.m_state = ParserState.InsideTag;
                        }
                        break;
                    case '>':
                        if (this.m_state == ParserState.InsideTag)
                        {
                            this.m_state = ParserState.InsideToken;
                        }
                        break;
                    case '&':
                        // # we only go into specialstate if we are inside a token and by that i
                        //   mean in the middle/end of a token
                        if (this.m_state == ParserState.InsideToken && newToken.Length > 0)
                        {
                            this.m_state = ParserState.InsideSpecial;
                        }
                        break;
                    case ';':
                        if (this.m_state == ParserState.InsideSpecial)
                        {
                            // we go back to regular token because we had to 
                            // have been in this state before special
                            this.m_state = ParserState.InsideToken;
                        }
                        break;
                    default:                        
                        if (this.m_state == ParserState.InsideToken)
                        {
                            if ((b > 'z' || b < 'a') && b != '.' && b != '\'')
                            {
                                if (newToken.Length > 1)
                                {
                                    string term = newToken.ToString();

                                    // because we can only be inside special if we were insidetoken;
                                    // therefore this token ends in special
                                    if (this.m_termfrequency.ContainsKey(term))
                                    {
                                        this.m_termfrequency[term] += 1;
                                    }
                                    else
                                    {
                                        this.m_termfrequency.Add(term, 1);
                                    }
                                }

                                newToken = new StringBuilder();
                            }
                            else if (b >= 'a' && b <= 'z')
                            {
                                newToken.Append(b);
                            }
                        }
                        else if (this.m_state == ParserState.InsideSpecial)
                        {
                            if (b == '\n' || b == ' ' || b == '\t' || b == '\r')
                            {
                                string term = newToken.ToString();

                                // because we can only be inside special if we 
                                // were insidetoken; therefore this token ends in special
                                if (this.m_termfrequency.ContainsKey(term))
                                {
                                    this.m_termfrequency[term] += 1;
                                }
                                else
                                {
                                    this.m_termfrequency.Add(term, 1);
                                }
                            }
                        }          
                        break;
                }
            }
            
            this.m_filestream.Close();

            return this.m_termfrequency;
        }

        public int getTokenCount()
        {
            return this.m_termfrequency.Count;
        }

        // members related to the state of the machine
        private string m_filename;
        private ParserState m_state;
        private FileStream m_filestream;

        // members related strictly to token storage
        private Dictionary<string, int> m_termfrequency;
    }
}
