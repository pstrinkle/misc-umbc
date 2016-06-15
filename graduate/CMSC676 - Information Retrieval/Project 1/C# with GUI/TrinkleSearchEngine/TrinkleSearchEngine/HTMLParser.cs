using System;
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
            Unknown,
            InsideTag,
            InsideToken
        };

        public HTMLParser(string filename)
        {
            this.m_filename = filename;

            this.initialize();
        }

        private void initialize()
        {
            if (System.IO.File.Exists(this.m_filename))
            {
                this.m_nextToken = 0;

                this.m_tokens = new List<string>();

                this.m_state = ParserState.Initialized;
            }
            else
            {
                this.m_filestream = null;
            }

            return;
        }

        // this reads through the file and tokenizes all words
        public Boolean tokenize()
        {
            int bytesRead = 0;
            int b = 0;
            StringBuilder newToken = new StringBuilder();

            // open file
            this.m_filestream = System.IO.File.Open(this.m_filename, System.IO.FileMode.Open);

            // tokenize the file
            while (bytesRead < this.m_filestream.Length)
            {
                bytesRead++;

                b = this.m_filestream.ReadByte();
                
                switch (b)
                {
                    case '<':
                        if (this.m_state == ParserState.InsideTag)
                        {
                            System.Console.WriteLine("inside tag parse error");
                        }
                        else
                        {
                            // we just started a tag
                            this.m_state = ParserState.InsideTag;
                        }
                        break;
                    case '>':
                        if (this.m_state == ParserState.InsideTag)
                        {
                            // we just ended a tag
                            this.m_state = ParserState.Unknown;
                        }
                        break;
                    default:
                        // some other character?
                        if (b == ' ' || b == '\n' || b == '\r' || b == '.' || b == ',' || b == ';' || b == '"')
                        {
                            if (this.m_state == ParserState.InsideToken)
                            {
                                this.m_state = ParserState.Unknown;

                                string x = newToken.ToString().ToLower();

                                if (!this.m_tokens.Contains(x))
                                {
                                    this.m_tokens.Add(x);
                                }

                                newToken = new StringBuilder();
                            }
                        }
                        else
                        {
                            if (this.m_state == ParserState.InsideToken)
                            {
                                newToken.Append((char)b);
                            }
                            else if (this.m_state != ParserState.InsideTag)
                            {
                                this.m_state = ParserState.InsideToken;
                                newToken.Append((char)b);
                            }
                        }
                        break;
                }
            }

            this.m_tokens.Sort();
            this.m_filestream.Close();

            return true;
        }

        // this returns the next token in the list
        public String getToken()
        {
            String token = this.m_tokens[m_nextToken++];

            return token;
        }

        public int getTokenCount()
        {
            return this.m_tokens.Count;
        }

        private Boolean isAlphaNum(char b)
        {
            // check b range            

            return true;
        }

        // members related to the state of the machine
        private string m_filename;
        private ParserState m_state;
        private System.IO.FileStream m_filestream;

        // members related strictly to token storage
        private List<string> m_tokens;
        private int m_nextToken;
    }
}
