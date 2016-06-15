package parser;

import java.text.NumberFormat;
import java.util.HashMap;

/**
 * @author Patrick Trinkle
 *         tri1@umbc.edu
 *         CMSC331
 * 	   Summer 2005
 *         Project 1
 */

/**
 * This Parser parses sentences of the following grammar:
 * A -> VAR Op A | E
 * Op -> ('='|'+='|'-='|'*='|'/=)
 * E -> T E'
 * E' -> ('+'|'-') TE' | epsilon
 * T -> F T'
 * T' -> ('*'|'/') FT' | epsilon
 * F -> VAR | DOUBLE | ('log'|'ln'|epsilon) '('E')' | 'pow''('E1','E2')'
 * 
 * The method this program uses is the recursive descent method.  The program runs until there
 * are no more expressions to evaluate.  This parser evaluates recursively.
 * 
 * More specifically this program reads in a stream of data, tokenizes the data and
 * then attempts to parse the data using the above EBNF.
 */


public class Grammar {
	
	private Tokenizer tokenizer;
	private HashMap<String, Double> variablestore;
	
	public Grammar()
	{
		this.tokenizer = new Tokenizer();
		this.variablestore = new HashMap<String, Double>();
	}
	
        public static void main(String[] args) {
		
            // Grammar builds Tokenizer which initiates Scanner and reads
            // in first line of input
            Grammar parserules = new Grammar();
            double value;
            
            System.out.println("You've begun the all-mighty Parser and Evaluater!");
            System.out.println();
            
            NumberFormat numberFormatter;
            String amountOut;
            numberFormatter = NumberFormat.getNumberInstance();
            
            do
            {
                // finds value by evaluating the expression
            	value = parserules.A();
                amountOut = numberFormatter.format(value);
                System.out.println(amountOut);
                System.out.println();
            }
            while( !parserules.endoffile() );
       	}
        
        public boolean endoffile() {
            return (tokenizer.endOfFile()) ? true : false;
        }
        
	/**
	 * @return double
	 */
	public double A()
	{
		//A -> VAR Op A | E
		Token first = tokenizer.getToken(); // pull first
		Token next = tokenizer.peekToken(); // peek next
                if ( first.getType() == Token.dead )
                    return 0.0;
   
		double current = 0;
		
		if ( first.isVar() )
		{
			if ( variablestore.containsKey( first.getValue() ) )
				current = (variablestore.get( first.getValue() )).doubleValue();
			// variablestore holds String, Double
			// variablestore.get() returns a Double
			// doubleValue() returns the double wrapped by Double
			// if it's not already declared we have issues!
			if ( next.getType() != Token.dead )
                        {
                            switch( next.getType() )
                            {
                            case Token.pluseq:
                                    current += A();
                                    break;
                            case Token.minuseq:
                                    current -= A();
                                    break;
                            case Token.timeeq:
                                    current *= A();
                                    break;
                            case Token.diveq:
                                    current /= A();
                                    break;
                            case Token.equals:
                                    current = A();
                                    break;
                            default:
                                    System.out.println ("Parse error.");
                            }
                            // insert back into hashmap with new number
                            variablestore.put(first.getValue(), current);   
                        }
                        else
                            System.out.println("Parse error.");        
                    }
                    else
                    	current = E();
                
            	return current;
	}
	
	/**
	 * @return double
	 */
        private double E()
	{
		//E -> T E'
		double value = T();
		
		return Eprime(value);
	}
	
	/**
	 * @return double
	 */
	private double Eprime(double value)
	{
		//E' -> '+' TE' | '-' TE' | epsilon
		
		//get + | -
		Token checker = tokenizer.peekToken();
		int type = checker.getType();
		
		if ( type != Token.dead && type == Token.plus )
		{
			Token trash = tokenizer.getToken(); // kill '+'
			double valueplus = T();
			return value + Eprime(valueplus);
		}
		else if ( type != Token.dead && type == Token.minus )
		{
			Token trash = tokenizer.getToken(); // kill '-'
			double valueminus = T();
			return value - Eprime(valueminus);
		}
		
		return value;
	}
	
	/**
	 * @return double
	 */
	private double T()
	{
		//T -> F T'
		double value = F();
		
		return Tprime(value);
	}
	
	/**
	 * @return double
	 */
	private double Tprime(double value)
	{
		//T' -> '*' FT' | '/' FT' | epsilon
		
		// get * | -
		Token checker = tokenizer.peekToken();
		int type = checker.getType();
		
		if ( type != Token.dead && type == Token.times )
		{
			Token trash = tokenizer.getToken(); // kill '*'
			double valuetimes = F();
			return value * Tprime(valuetimes);
		}
		else if ( type != Token.dead && type == Token.divide )
		{
			Token trash = tokenizer.getToken(); // kill '/'
			double valuedivide = F();
			return value / Tprime(valuedivide);
		}
		
		return value;
	}
	
	/**
	 * @return double
	 */
	private double F()
	{
		//F -> VAR | DOUBLE | 'log''('E')' | 'ln''('E')' | 'pow''('E1','E2')' | '(' E ')'
		
		// get end product or check for further movements
		Token first = tokenizer.getToken();
		Token trash;
		int type = first.getType();
		double value = 0, value1, value2;	
		
		switch( type ) {
		case Token.var:
			// pull from hashmap
			if ( variablestore.containsKey( first.getValue() ) )
				value = (variablestore.get( first.getValue() )).doubleValue();
			else
				System.out.println ("Parse Error, variable called not in memory.");
			break;
		case Token.dbl:
			value = first.getDValue();
			break;
			// log
		case Token.log:
			// log base 2
			trash = tokenizer.getToken(); // kill '('
			value = Math.log( E() ) / Math.log(2);
			trash = tokenizer.getToken(); // kill ')'
			break;
			// ln
		case Token.ln:
			trash = tokenizer.getToken(); // kill '('
			value = Math.log( E() );
			trash = tokenizer.getToken(); // kill ')'
			break;
		case Token.pow:
			trash = tokenizer.getToken(); // kill '('
			value1 = E();
			trash = tokenizer.getToken(); // kill ','
			value2 = E();
			trash = tokenizer.getToken(); // kill ')'
			value = Math.pow( value1, value2 );
			break;
		case Token.paren:
			value = E();
			trash = tokenizer.getToken(); // kill ')'
			break;
                case Token.comma:
                        value = A();
                        break;
		default:
			System.out.println ("Parse Error, out of place.");
		}
		return value;
	}
}



