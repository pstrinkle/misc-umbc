#!/usr/bin/env ruby

# Course: CMSC676 - Information Retrieval
# Semester: Spring 2009
# Professor: Dr Nicholas
# Student: Patrick Trinkle <tri1@umbc.ed>
# Date: 20090204
# Title: HTMLParser Object Definition
# Note: This was far trickier than doing it in C# or Perl or C, but has provided a good learning experience
#          Also this method is rather slow.  Doing it as a procedural script might be faster as it won't have to 
#          instantiate objects, etc.  But since speed wasn't a primary concern; I felt this approach was appropriate.

# Okay all special characters within a token (either in the middle or the end) are disregarded: be&#146s => bes
# Numbers are also ignored.
# Tokens are terminated by anything that isn't a letter or a '.'; unless it's in a special character code
# Also note: "good.neat" => "goodneat"

require 'fileutils'

# Ruby doesn't have quite the notion of an enumeration
class HTMLParserState
  InsideTag = 1
  InsideToken = 2
  InsideSpecial = 3
end

def HTMLParserTokenize( filename )
  state = 0
  templine = ""
  termList = Hash.new( 0 )

  file = File.open( filename )

  file.each {
    |line|

    line.downcase.each_byte {
      |c|      
      b = c.chr

      case b
        when '<':
          if state == HTMLParserState::InsideToken then
            # end current token
            if templine.size > 0 then
              templine.delete!( '.' )
              termList[templine] += 1
            end
            
            templine = ""
            state = HTMLParserState::InsideTag
          end
          if state != HTMLParserState::InsideTag then
            state = HTMLParserState::InsideTag
          end
        when '>':
          if state == HTMLParserState::InsideTag then
            state = HTMLParserState::InsideToken
          end # end if insidetag
        when '&':
          # we only go into specialstate if we are inside a token and by that i mean in the middle/end of a token
          if state == HTMLParserState::InsideToken && templine.size > 0 then
            state = HTMLParserState::InsideSpecial
          end # end if state == insidetoken
        when ';':
          if state == HTMLParserState::InsideSpecial then
            # we go back to regular token because we had to have been in this state before special
            state = HTMLParserState::InsideToken
          end # end if state == insidespecial
        else
          if state == HTMLParserState::InsideToken then
            if (b > 'z' || b < 'a') && b != '.' then
              if templine.size > 0 then
                templine.delete!( '.' )
                termList[templine] += 1
              end
              templine = ""
            elsif (b >= 'a' && b <= 'z') then # we currently ignore urls
              templine.concat( b )
            end # end if b.chr == ... 
          elsif state == HTMLParserState::InsideSpecial
            if (b == '\n' || b == ' ' || b == '\t' || b == '\r') then
              templine.delete!( '.' )
              termList[templine] += 1
            end
          end #end if state == HTMLParserState::InsideToken
      end #end case
      } #end each byte
    } #end each line
    
  file.close
  # we now have all the terms for that file
    
  return termList

end #end tokenize

# Main Execution

# Parse input parameters
directory = ""
index = ""

if ARGV.size != 2 then
  puts "usage: <input file directory> <index directory>"
  exit
else
  directory = ARGV[0]
  index = ARGV[1]
end

# Is there an index directory?
if File.exists? index then
  puts "Index Directory Already Exists"
else
  FileUtils.mkdir( index )
end

files = Array.new

# Glob up the HTML Files in the Directory
dir = Dir.open( directory )
files = dir.to_a
dir.close

# Tokenize each file
i, j = 0, 0
totalTokens = Hash.new( 0 )
temporaryList = Array.new

# We only want .html files
while i < files.size do
  if files[i] !~ /html$/ then
    files.delete_at( i )
    i -= 1
    else
      shortname = String.new( files[i] )
      shortname =~ /(.*?)\.html/
      temporaryList = HTMLParserTokenize( (files[i].insert 0, directory) ).to_a.sort
      outputFile = File.new( index + $1 + ".txt", "w" )
      j = 0
      while j < temporaryList.size do
        totalTokens[temporaryList[j][0]] += temporaryList[j][1]
        outputFile.puts temporaryList[j][0] + " : " + temporaryList[j][1].to_s
        j += 1
      end
      outputFile.close
      puts "Finished: " + files[i] + " Found: " + temporaryList.size.to_s + " Tokens"
    end
  i += 1
end

puts "Total Tokens: " + totalTokens.size.to_s

# Print out Total Terms List sorted by term
puts "Writing out Complete Term List by Term"
outputFile = File.new( index + "TermListSortedByTerm.txt", "w" )
temporaryList = totalTokens.to_a.sort
i =0
while i < temporaryList.size do
  outputFile.puts temporaryList[i][0] + " : " + temporaryList[i][1].to_s
  i += 1
end
outputFile.close

# Print out Total Terms List sorted by frequency
puts "Writing out Complete Term List by Frequency"
outputFile = File.new( index + "TermListSortedByFrequency.txt", "w" )
# reverse sort code: .sort {|a,b| -1*(a[1]<=>b[1]) }
temporaryList = totalTokens.sort {|a,b| a[1] <=> b[1]}.to_a
i = 0
while i < temporaryList.size do
  outputFile.puts temporaryList[i][0] + " : " + temporaryList[i][1].to_s
  #puts temporaryList[i].to_s
  i += 1
end
outputFile.close
