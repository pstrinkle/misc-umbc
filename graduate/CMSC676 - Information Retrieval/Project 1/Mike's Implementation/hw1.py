
class stateM(object):
     "take a char at a time and stores tokens \
      has function to write tokens to a file"
     def __init__(self): 
          self.state = 'read'
          self.currToken = ''
          self.fileTokens = {} #holds tokens for each file
          self.tokens = {} #holds tokens for all files
     def readChar(self,theChar):
          "Ignores all values in tags, \
           ends current token if a space, new line, tab, or tag is reached \
           if char a-z or 0-9 writes it to a token"
          theLowerChar = theChar.lower()
          #ignores everything in a tag
          if theChar == '<':
               self.state = 'ignore'
               self.writeToken()
          elif theChar == '>':
               self.state = 'read'
          elif theLowerChar in (' ','\n','\t'):
               self.writeToken()
          elif self.state == 'read' and (self.isLetter(theLowerChar) or self.isNumber(theLowerChar)):
               self.currToken += theLowerChar
     def isLetter(self,theChar):
          return theChar >= 'a' and theChar <= 'z'
     def isNumber(self,theChar):
          return theChar >= '0' and theChar <= '9'
     def writeToken(self):
          "if currToken isn't blank write it to fileTokens \
           and adds a count of it to tokens"
          if self.currToken != '':
                    #stores a file token, using a dict to remove dupes
                    self.fileTokens[self.currToken] = 1
                    #self.fileTokens.append(self.currToken)
                    #keeps a freq count of all tokens
                    if self.tokens.__contains__(self.currToken) :
                         self.tokens[self.currToken] = self.tokens[self.currToken]+1
                    else:
                         self.tokens[self.currToken] = 1
                    self.currToken = ''
     def writeToFile(self,theFile):
          "writes all fileTokens to theFile, clears fileTokens"
          f=open(theFile,'w');
          f.write('\n'.join(sorted(self.fileTokens.keys())))
          #f.write('\n'.join(self.fileTokens[0:]))
          f.close()
          self.fileTokens = {}
     def writeAllToFile(self,theValuesFile,theKeysFile):
          "writes all tokens and freq to theValues File sorted by freq \
           and to theKeys File sorted by the keys"
          f=open(theValuesFile,'w');
          for line in (sorted(self.tokens.iteritems())):
               f.write('%s:%s\n' % (line[0], line[1]))
          f.close()
          f=open(theKeysFile,'w');
          for line in (sorted(self.tokens.iteritems(), key=lambda (k,v):(v,k))):
               f.write('%s:%s\n' % (line[0], line[1]))
          f.close()

import sys         
def main():
     "loops though all files one char at a time \
      passes each char to the stat machine \
      at the end of the file writes all tokens to a file \
      at the end of all files writes the freq for all files"

     s=stateM()          
     for i in range(1, 504):
          f=open('%s/%03d.html' % (sys.argv[1],i) , 'r')
          while 1:
               aChar = f.read(1)          # read by character
               if not aChar: break
               s.readChar(aChar)
          f.close()
          s.writeToFile('%s/%03d.txt' % (sys.argv[2],i))
     s.writeAllToFile('%s/values.txt' % sys.argv[2] ,'%s/keys.txt' % sys.argv[2])
     
if __name__ == "__main__":   
     main()