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

require 'fileutils'

# Ruby doesn't have quite the notion of an enumeration
class HTMLParserState
  InsideTag = 1
  InsideToken = 2
  InsideSpecial = 3
end

# HTMLParser class handles file IO and tokenizing of an input html file
class HTMLParser
  def initialize( file )
    @filename = file
    @termList = Hash.new( 0 )
  end  
  def endToken( byte )
    b = byte
    if (b.chr == ' ' || b.chr == '\n' || b.chr == '\r' || b.chr == '\t') then
      return true
    elsif (b.chr == ',' || b.chr == '-' || b.chr == '"' || b.chr == '[' || b.chr == ']') then
      return true
    elsif (b.chr == ':' || b.chr == ';' || b.chr == '/') then
      return true
    end
    
    return false
  end
  def tokenize
    lineCnt, byteCnt, state, termCnt, i = 0, 0, 0, 0, 0
    templine = ""
    
    file = File.open( @filename )
    
    file.each {
      |line|
      
      line.downcase.each_byte {
        |b|
        byteCnt += 1

        case b.chr
          when '<':
            if state == HTMLParserState::InsideToken then
              # end current token
              if templine.size > 0 then
                @termList[templine] += 1
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
              templine.concat( b.chr )
              state = HTMLParserState::InsideSpecial
            end # end if state == insidetoken
          when ';':
            if state == HTMLParserState::InsideSpecial then
              templine.concat( b.chr )
              # we go back to regular token because we had to have been in this state before special
              state = HTMLParserState::InsideToken
            end # end if state == insidespecial
          else
            if state == HTMLParserState::InsideToken then
              if endToken( b ) then
                if templine.size > 0 then
                    @termList[templine] += 1
                end
                templine = ""
              elsif (b.chr >= 'a' && b.chr <= 'z') then # we currently ignore urls
                templine.concat( b.chr )
              end # end if b.chr == ... 
            elsif state == HTMLParserState::InsideSpecial then
              templine.concat( b.chr )
            end #end if state == HTMLParserState::InsideToken
        end #end case
        } #end each byte

      lineCnt += 1
      } #end each line
    
    file.close
    # we now have all the terms for that file
  end #end tokenize
  def getTokenHash
    return @termList
  end #end getTokenHash
end #end class HTMLParser


# Main Execution

# Parse input parameters
directory = ""
index = ""

if ARGV.size != 2 then
  puts "usage: <input file directory full path> <index directory full path>"
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

i = 0
files = Array.new
filesNames = Hash.new

# Glob up the HTML Files in the Directory
dir = Dir.open( directory )
files = dir.to_a
dir.close

# We only want .html files
while i < files.size do
  if files[i] !~ /html$/ then
    files.delete_at( i )
    i -= 1
    else
      shortname = String.new( files[i] )
      shortname =~ /(.*?)\.html/
      filesNames[$1] = files[i].insert 0, directory
    end
  i += 1
end

files.clear
files = filesNames.to_a.sort

puts "HTML File Count: " + files.size.to_s

# Tokenize each file
i, j = 0, 0

# files[i][0] => short filename
# files[i][1] => full path + short filename
# temporaryList[i][0] => term
# temporaryList[i][1] => count

totalTokens = Hash.new( 0 )
temporaryList = Array.new

while i < files.size do
  parser = HTMLParser.new( files[i][1] )
  parser.tokenize
  temporaryList = parser.getTokenHash.to_a.sort
  #puts "In file: " + files[i][0] + " Found: " + temporaryList.size.to_s
  # open output index file!
  outputFile = File.new( index + files[i][0] + ".txt", "w" )
  j = 0
  while j < temporaryList.size do
    totalTokens[temporaryList[j][0]] += temporaryList[j][1]
    outputFile.puts temporaryList[j][0] + " : " + temporaryList[j][1].to_s
    j += 1
  end
  outputFile.close
  i += 1
end

puts "Total Tokens: " + totalTokens.size.to_s

# Print out Total Terms List sorted by term
outputFile = File.new( index + "TermListSortedByTerm.txt", "w" )
temporaryList = totalTokens.to_a.sort
i =0
while i < temporaryList.size do
  outputFile.puts temporaryList[i][0] + " : " + temporaryList[i][1].to_s
  i += 1
end
outputFile.close

# Print out Total Terms List sorted by frequency
outputFile = File.new( index + "TermListSortedByFrequency.txt", "w" )
outputFile.close