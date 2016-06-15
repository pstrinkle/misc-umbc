package parser;

import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Tokenizer {
	
	private ArrayList<Token> buffer;
	private int EndOfFilecmd;
        Scanner reader;
	
	public Tokenizer() {
		this.buffer = new ArrayList<Token>();
		this.EndOfFilecmd = 0;
                reader = new Scanner(System.in);
                
		/* if there is no input then this process will take
                * forever and never run! and never finish building Grammar Object */
		//refreshBuffer();
	}
	
	public boolean endOfFile() {
		return (EndOfFilecmd == 1) ? true : false;
	}
	
	public Token getToken() {
		if ( buffer.size() < 1 )
			refreshBuffer();
                
                if ( buffer.size() == 0 )
                    return new Token(Token.dead);
                
		return buffer.remove(0);
	}
	
	public Token peekToken() {
		if ( buffer.size() < 1 )
			refreshBuffer();
                
                if ( buffer.size() == 0 )
                    return new Token(Token.dead);
                
		return buffer.get(0);
	}
	
	private void refreshBuffer() {
		
		Character temp;
		Token piece;
		
		String variable;
		String doublehldr;
		
		String charbuffer;
                String input;
                try {
		input = reader.nextLine();
                }
                catch(NoSuchElementException nsee) {
                    EndOfFilecmd = 1;
                    reader.close();
                    return;
                }
		
		//simplify chars
		charbuffer = input.toLowerCase();
                
		// for loop goes through charbuffer per char and makes tokens
		// the for loop auto increments, so if I used more than one char
		// i incremented the thing appropriately
		// this code assumes that words won't be broken by line basically
		// there is an order of elimination in the loop
		
		for ( int i = 0; i < charbuffer.length(); ++i )
		{                     
			if ( Character.isWhitespace(charbuffer.charAt(i)) || charbuffer.charAt(i) == '\0' || charbuffer.charAt(i) == '\n' )
			{
				// do nothing it's whitespace
			}

			// String doublehldr;
			// filter out double
			else if ( Character.isDigit(charbuffer.charAt(i)) )
			{
				// begin double string
				doublehldr = String.valueOf(charbuffer.charAt(i));
				i++;

				do {
					
					if ( i < charbuffer.length() && ( Character.isDigit(charbuffer.charAt(i)) || charbuffer.charAt(i) == '.' ) )
					{
						// add new char to string
						doublehldr += charbuffer.charAt(i);
						i++;
					}
				}
				while ( i < charbuffer.length() && ( Character.isDigit(charbuffer.charAt(i)) || charbuffer.charAt(i) == '.' ) );
				
				// make double number and then add to buffer of tokens
				Double tempdbl = new Double(doublehldr);
				piece = new Token(Token.dbl, tempdbl.doubleValue());
                                buffer.add(piece);
                        }
                        
                        // filter out ln log pow
			else if ( charbuffer.charAt(i) == 'l' && i < charbuffer.length() && charbuffer.charAt(i+1) == 'n' )
			{
				piece = new Token(Token.ln);
				i++; // to skip ahead of the 'n'
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == 'l' && i  + 1 < charbuffer.length() && charbuffer.charAt(i+1) == 'o' && charbuffer.charAt(i+2) == 'g' )
			{
				piece = new Token(Token.log);
				i += 2; // to skip ahead of the 'g'
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == 'p' && i  + 1 < charbuffer.length() && charbuffer.charAt(i+1) == 'o' && charbuffer.charAt(i+2) == 'w' )
			{
				piece = new Token(Token.pow);
				i += 2; // to skip ahead of the 'w'
                                buffer.add(piece);
			}
                    
                        // filter out variable
			
			else if ( Character.isLetter(charbuffer.charAt(i)) )
			{
				// clear temp variable
				variable = " ";            

				while ( i < charbuffer.length() && charbuffer.charAt(i) >= 'a' && charbuffer.charAt(i) <= 'z' )
				{
					variable += charbuffer.charAt(i);
                                        i++;
				}
				// variable holds all the letters in the variable name
				
				piece = new Token(Token.var, variable);
                                buffer.add(piece);
			}

                        // filter out ( , )
			
			else if ( charbuffer.charAt(i) == '(' || charbuffer.charAt(i) == ')' )
			{
				piece = new Token(Token.paren);
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == ',' )
			{
				piece = new Token(Token.comma);
                                buffer.add(piece);
			}
                        
			// filter out += -= *= /=
			// this code also makes sure it doesn't go out of range while looking for the next char
			
			else  if ( charbuffer.charAt(i) == '+' && i < charbuffer.length() && charbuffer.charAt(i+1) == '=' )
			{
				piece = new Token(Token.pluseq);
				i++;
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == '-' && i < charbuffer.length() && charbuffer.charAt(i+1) == '=' )
			{
				piece = new Token(Token.minuseq);
				i++;
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == '*' && i < charbuffer.length() && charbuffer.charAt(i+1) == '=' )
			{
				piece = new Token(Token.timeeq);
				i++;
                                buffer.add(piece);
			}
			else if ( charbuffer.charAt(i) == '/' && i < charbuffer.length() && charbuffer.charAt(i+1) == '=' )
			{
				piece = new Token(Token.diveq);
				i++;
                                buffer.add(piece);
			}
			
			//filter out + - * /
			else if ( charbuffer.charAt(i) == '+' ) {
                            piece = new Token(Token.plus);
                            buffer.add(piece);
                        }
			else if ( charbuffer.charAt(i) == '-' ) {
                            piece = new Token(Token.minus);
                            buffer.add(piece);
                        }
			else if ( charbuffer.charAt(i) == '*' ) {
                            piece = new Token(Token.times);
                            buffer.add(piece);
                        }
			else if ( charbuffer.charAt(i) == '/' ) {
                            piece = new Token(Token.divide);
                            buffer.add(piece);
                        }
                        else if ( charbuffer.charAt(i) == '=' ) {
                            piece = new Token(Token.equals);
                            buffer.add(piece);
                        }
	
		} // end of for loop
		
	}
	
} // end of class





















