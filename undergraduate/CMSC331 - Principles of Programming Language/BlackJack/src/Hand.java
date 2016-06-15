/* Hand.java
 *
 * Author: Patrick Trinkle
 * Email: tri1@umbc.edu
 * Created on July 14, 2005, 3:53 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.util.ArrayList;
import java.io.Serializable;

public class Hand implements Serializable{

    public static final int handSize     = 2;
    
    private ArrayList<Card> cards;
    
    /** Creates a new instance of Hand */
    public Hand() {
        cards = new ArrayList<Card>(0);
    }
    public Hand(Card card1, Card card2) {
        cards = new ArrayList<Card>(handSize);
        cards.add(card1);
        cards.add(card2);
    }
    
    public void addCard(Card card1) {
        cards.add(card1);
    }
    
    public Card getTopCard() {
        return cards.get(0);
    }
    
    public Card getCard( int index ) {
        return cards.get(index);
    }
    
    public int getValue() {
        int numCards = cards.size();
        int total = 0;
        
        for ( int i = 0; i < numCards; ++i )
            total += cards.get(i).value();
        
        return total;
    }
    
    public int getNumCards() {
        return cards.size();
    }
    
    public boolean isTwentyOne() {
        return ( getValue() == 21 ) ? true : false;
    }
    
    public boolean isBust() {
        return ( getValue() > 21 ) ? true : false;
    }
    
    public void print() {
        int numCards = cards.size();
        
        for ( int i = 0; i < numCards; ++i ){
            cards.get(i).print();
            System.out.println("  ");
        }
    }
}
