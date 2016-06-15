/* Deck.java
 *
 * Author: Jason Gaertner
 * Email: jasong1@umbc.edu
 * Created on July 10, 2005, 10:56 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.util.Random;
import java.util.ArrayList;
import java.io.*;

public class Deck implements Serializable{
    
    public static final int deckSize     = 52;
    public static final int halfDeckSize = 26;
    public static final int numSuits     = 4;
    
    /** Creates a new instance of Deck */
    public Deck(){
        
        // create the deck of 52 cards
        deck = new ArrayList<Card>(deckSize);
	
	// creates a standard deck of cards
	// 2-10,Jack-Ace, Hearts, Diamonds, Clubs, Spades
        for(int i = 0; i < numSuits; i++){
	    Card card;
	    String suit = "";
            switch(i){
                case (Card.hearts):
                    suit = Card.Heart;
		    break;
                case (Card.diamonds):
                    suit = Card.Diamond;
		    break;
                case (Card.clubs):
                    suit = Card.Club;
		    break;
                case (Card.spades):
                    suit = Card.Spade;
		    break;
		default:
		    System.out.println("Error: Bad Suit");
	    }
	    
	    // initialize all card values in a suit
	    for(int j = 1; j <= 13; j++ ){
            if(j == 1)
            	card = new Card(suit, Card.ace);
	    else if(j == 11)
		card = new Card(suit, Card.jack);
            else if(j == 12)
               	card = new Card(suit, Card.queen);
            else if(j == 13)
               	card = new Card(suit, Card.king);
            else
               	card = new Card(suit, j);
	    deck.add(card);
	    }
    	}
    }
    
    public void shuffle(long timesToShuffle){
        ArrayList<Card> lefthand = new ArrayList<Card>(halfDeckSize);
        ArrayList<Card> righthand = new ArrayList<Card>(halfDeckSize);
        Random rand = new Random(System.currentTimeMillis());
        
        // split the deck
        for(int s = 0; s < timesToShuffle; s++){
	    // fill left hand and right hand
	    while(!deck.isEmpty()){
		int r = rand.nextInt(deck.size());
        	lefthand.add(deck.remove(r));
        	r = rand.nextInt(deck.size());
        	righthand.add(deck.remove(r));
	    }
        		
	    // reassemble the deck
	    for(int i = 0; i < halfDeckSize; i++){
	    	deck.add(righthand.remove(0));
	    	deck.add(lefthand.remove(0));
	    }
        }
    }
    
    public Card topCard() throws EmptyDeckException {
	if(deck.isEmpty()){
	    EmptyDeckException e = new EmptyDeckException("Error: "
		    + "Deck is Empty");
	    throw e;
	}
	else
	    return deck.remove(0);
    }
    
    public boolean isEmpty(){
	return deck.isEmpty();
    }
    
    public void print(){
    	// prints every card in a deck
    	for(int i = 0; i < deck.size(); i++){
	    Card card = deck.get(i);
	    card.print();
	    System.out.println();
    	}
    }
    
    private ArrayList<Card> deck;
}