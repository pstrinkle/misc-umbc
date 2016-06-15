/* Player.java
 *
 * Author: Patrick Trinkle
 * Email: tri1@umbc.edu
 * Created on July 14, 2005, 4:24 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.util.ArrayList;
import java.io.Serializable;

public class Player implements Serializable{
    
    private ArrayList<Hand> hands;
    
    /** Creates a new instance of Player */
    public Player() {
        hands = new ArrayList<Hand>(1);
        hands.add(new Hand());
    }
    
    public int getHandValue() {
        // always the top hand, because it's in play
        return hands.get(0).getValue();
    }
    
    public int numHands() {
        return hands.size();
    }
    
    public Hand getTopHand() {
        return hands.get(0);
    }
    
    public void killHand() {
        hands.remove(0);
    }
    
    public void receiveCard(Card card1) {
         hands.get(0).addCard(card1);
    }
    
    public void split(Card first, Card second) {
	Hand oldHand = getTopHand();
	Hand firsthand;
	Hand lasthand;

        if ( oldHand.getNumCards() == 2 && oldHand.getCard(0).value() == oldHand.getCard(1).value() )
	{
		// the values match and there are only two cards in this hand

            if ( !oldHand.getCard(0).isNotFaceCard() && !oldHand.getCard(1).isNotFaceCard() )
            {
                // both cards are face cards

                if ( oldHand.getCard(0).face().compareTo(oldHand.getCard(1).face()) == 0 )
		{
                    // both cards have same face
                    killHand();
                    firsthand = new Hand(oldHand.getCard(0), first);
                    lasthand = new Hand(oldHand.getCard(1), second);
                    // this splits up the two cards from the old and
                    // pairs them up & then inserts the cards back
                    
                    /* the first card from the top hand will remain such
                    * the second card from the top hand will show up as
                    * the first card in the last hand */
                    hands.add(0, firsthand);
                    hands.add(lasthand);
                }
            }
            else if ( oldHand.getCard(0).isNotFaceCard() && oldHand.getCard(1).isNotFaceCard() )
            {
		// the cards already match value
		killHand();
		firsthand = new Hand(oldHand.getCard(0), first);
		lasthand = new Hand(oldHand.getCard(1), second);

		hands.add(0, firsthand);
		hands.add(lasthand);
            }
            else
		System.out.println("The cards in top hand must match");
        }
	else
            System.out.println("The cards in top hand must match");
    }
    
    public void printHand() {
        // only print the hand in play?
        hands.get(0).print();
        System.out.println();
    }
    
    public void print() {
        int numHands = hands.size();
        
        for ( int i = 0; i < numHands; ++i )
        {
            hands.get(i).print();
            System.out.println();
        }
    }
}
