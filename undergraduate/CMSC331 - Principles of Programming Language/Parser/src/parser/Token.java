package parser;

public class Token {
	
	private double dvalue;
	private int type;
	private String value;
	
	public static final int var     = 0;
	public static final int pluseq  = 1;
	public static final int minuseq = 2;
	public static final int timeeq  = 3;
	public static final int diveq   = 4;
	public static final int equals  = 5;
	public static final int plus    = 6;
	public static final int minus   = 7;
	public static final int times   = 8;
	public static final int divide  = 9;
	public static final int paren   = 10;
	public static final int log     = 11;
	public static final int ln      = 12;
	public static final int pow     = 13;
	public static final int comma   = 14;
	public static final int dbl     = 15;
        public static final int dead    = 31337;
	
	public Token(int type, String value) {
		this.type = type;
		this.value = value;
		this.dvalue = 0;
	}
	
	public Token(int type) {
		this.type = type;
	}
	
	public Token(int type, double value) {
		this.type = type;
		this.dvalue = value;
	}
	
	public boolean isNumber() {
		return ( type == Token.dbl ) ? true : false;
	}
	
	public boolean isVar() {
		return ( type == Token.var ) ? true : false;
	}
	
	public String getValue() {
		return value;
	}
	
	public double getDValue() {
		return dvalue;
	}
	
	public int getType() {
		return type;
	}
	
}