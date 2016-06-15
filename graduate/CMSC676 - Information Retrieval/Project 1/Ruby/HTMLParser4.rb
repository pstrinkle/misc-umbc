#!/usr/bin/env ruby

# Course: CMSC676 - Information Retrieval
# Semester: Spring 2009
# Ruby doesn't have quite the notion of an enumeration
def endToken( byte )
  
  if (b.chr == ' ' || b.chr == '\n' || b.chr == '\r' || b.chr == '\t') then
  elsif (b.chr == ':' || b.chr == ';' || b.chr == '/' || b.chr == "+" || b.chr == "=") then
    return true
  end
  
  return false
end
def HTMLParserTokenize( filename )
  state = 0
  file = File.open( filename )
  file.each {
    |line|
    line.downcase.each_byte {
      |b|
      case b.chr
        when '<':
          if state == HTMLParserState::InsideToken then
            # end current token
            if templine.size > 0 then
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
          # we only go into specialstate if we are inside a token
          #  and by that i mean in the middle/end of a token
          if state == HTMLParserState::InsideToken && templine.size > 0 then
            templine.concat( b.chr )
            state = HTMLParserState::InsideSpecial
          end # end if state == insidetoken
        when ';':
          if state == HTMLParserState::InsideSpecial then
            templine.concat( b.chr )
            # we go back to regular token because we had to have 
            # been in this state before special
            state = HTMLParserState::InsideToken
          end # end if state == insidespecial
        else
          if state == HTMLParserState::InsideToken then
            if endToken( b ) then
              if templine.size > 0 then
                  termList[templine] += 1
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
# Is there an index directory?
files = Array.new
# Glob up the HTML Files in the Directory
# Tokenize each file
# We only want .html files
puts "Total Tokens: " + totalTokens.size.to_s
# Print out Total Terms List sorted by term