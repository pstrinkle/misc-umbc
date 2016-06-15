/* Card.java
 * 
 * Author: Jason Gaertner
 * Created on July 10, 2005, 10:56 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.io.*;

public class Card implements Serializable{
    
    // Suits of a card
    public static final String Heart   = "Hearts";
    public static final String Diamond = "Diamonds";
    public static final String Club    = "Clubs";
    public static final String Spade   = "Spades";
    
        // suits of a deck of cards
    public static final int hearts   = 0;
    public static final int diamonds = 1;
    public static final int clubs    = 2;
    public static final int spades   = 3;

    // face cards
    public static final String ace     = "A";
    public static final String king    = "K";
    public static final String queen   = "Q";
    public static final String jack    = "J";
    
    /** Creates a new instance of Card */
    public Card(String cardSuit, int cardValue) {
        suit = cardSuit;
        value = cardValue;
        face = "No";
    }
    
    /** creates a face card */
    public Card(String cardSuit, String cardValue){
        suit = cardSuit;
        if(cardValue.equals(king) || cardValue.equals(queen)
	    || cardValue.equals(jack)){
            value = 10;
            face = cardValue;
        }else if(cardValue.equals(ace)){
            value = 11;
            face = cardValue;
        }
    }

    /** creates a default card */
    public Card(){
        suit = "";
        value = 0;
        face = "No";
    }
    public String suit() {
        return suit;
    }
    
    public int value() {
        return value;
    }
    
    public String face() {
        return face;
    }
    
    public boolean isNotFaceCard(){
        return(face.equals("No"));
    }
    
    public void changeAceValue(){
	// sets ace value to 11 or 1
	// if not an ace does nothing
	if( face.equals(ace)){
	    if(value == 1)
		value = 11;
	    else if(value == 11)
		value = 1;
	}else
	    return;
    }
    
    public void print(){
	if(isNotFaceCard())
	    System.out.print(value);
	else
	    System.out.print(face);
	if(isNotFaceCard() && value == 10)
	    System.out.print(" of ");
	else
	    System.out.print("  of ");
	System.out.print(suit);
    }
    
    //suit of a card
    private String suit;
    
    // face value of a card
    private int value;
    
    // face card or not
    private String face;
}