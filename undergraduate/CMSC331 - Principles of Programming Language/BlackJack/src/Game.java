/* Game.java
 *
 * Author: Patrick Trinkle
 * Email: tri1@umbc.edu
 * Created on July 14, 2005, 4:30 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.io.Serializable;
import java.util.ArrayList;

public class Game implements Serializable {
    
    private Deck deck;
    private ArrayList<Player> players;
    private Player dealer;
    
    /** Creates a new instance of Game */
    public Game() {
        // set up dealer and one opponent
        players = new ArrayList<Player>(1);
        players.add(new Player());
        dealer = new Player();
        deck = new Deck();
        deck.shuffle(15);
    }
    
    public Game( int numPlayers ) {
        players = new ArrayList<Player>(numPlayers);
        
        for(int i = 0; i < numPlayers; i++)
            addPlayer();
        
        dealer = new Player();
        deck = new Deck();
        deck.shuffle(15);
    }
    
    public void addPlayer() {
        Player new_guy = new Player();
        players.add(new_guy);
    }
    
    public void deal() {
        int numPlayers = players.size();
        // deal dealer last
        
        //don't complain about double try/catch; it was being a pain
        // deal first card
        try {
           for ( int i = 0; i < numPlayers; ++i )
               players.get(i).receiveCard(deck.topCard());
           dealer.receiveCard(deck.topCard());
        }
        catch(EmptyDeckException e)
        {
            System.out.println(e);
        }
        // deal second card
        try {
           for ( int j = 0; j < numPlayers; ++j )
               players.get(j).receiveCard(deck.topCard());
           dealer.receiveCard(deck.topCard());
        }
        catch(EmptyDeckException e)
        {
            System.out.println(e);
        }
    }
//used to be void
    public void hit() {
        // returns new value of players hand
        try {
           players.get(0).receiveCard(deck.topCard());
        }
        catch(EmptyDeckException e)
        {
            System.out.println(e);
        }
        /* if isBust() it tries to look for an ace
         *if it finds an ace it changes it's value
         */
        if ( players.get(0).getTopHand().isBust() )
        {
            int numCards = players.get(0).getTopHand().getNumCards();

            // makes it faster for looking at cards
            Hand temp = players.get(0).getTopHand();
        
            for ( int i = 0; i < numCards; ++i )
            {
                if ( temp.getCard(i).value() == 11 ) {
                    players.get(0).getTopHand().getCard(i).changeAceValue();
                }
            }
            
        }//end of if         
    }
      
    public boolean Busted() {
        if (players.get(0).getTopHand().isBust())
            return true;
        else
            return false;  
    }
    
    public void dealerHit() {
        try {
            dealer.receiveCard(deck.topCard());
        }
        catch(EmptyDeckException e)
        {
            System.out.println(e);
        }
        /* if isBust() it tries to look for an ace
         *if it finds an ace it changes it's value
         */
        if ( dealer.getTopHand().isBust() )
        {
            int numCards = dealer.getTopHand().getNumCards();
            Hand temp = dealer.getTopHand();
            
            for ( int i = 0; i < numCards; ++i )
            {
                if ( temp.getCard(i).value() == 11 )
                    dealer.getTopHand().getCard(i).changeAceValue();
            }
        }
        
    }
    
    public void split() {
        try {
            Card first = deck.topCard();
            Card second = deck.topCard();
            players.get(0).split(first, second);
        }
        catch(EmptyDeckException e)
        {
            System.out.println(e);
        }
        
    }
    
    public String stay() {
        int dealerValue = dealer.getHandValue();
        int playerHand = players.get(0).getHandValue();
        String result = " ";
              
        if ( dealer.getTopHand().isBust() )
           result = "Player Wins \nDealer Busts with "+dealerValue+"\nPlayer has "+playerHand;
        else if ( players.get(0).getTopHand().isBust() )
            result = "Dealer Wins \nDealer has " + dealerValue + "\nPlayer Busted with "+playerHand;
        else if ( players.get(0).getTopHand().isTwentyOne() && dealer.getTopHand().isTwentyOne() )
            result = "Push, Dealer Wins \nDealer and Player had 21";
        else if ( players.get(0).getTopHand().isTwentyOne() )
            result = "Player Wins \nDealer has " + dealerValue + "\nPlayer has 21";
        else if ( dealer.getTopHand().isTwentyOne() )
            result = "Dealer Wins \nDealer has 21 \nPlayer has " + playerHand;
        else if ( dealerValue > playerHand )
            result = "Dealer Wins \nDealer has "+dealerValue+"\nPlayer has "+playerHand;
        else if ( playerHand > dealerValue )
            result = "Player Wins \nDealer has "+dealerValue+"\nPlayer has "+playerHand;
        else if ( playerHand == dealerValue )
            result = "Push, Dealer Wins \nDealer and Player tied at " + dealerValue;
        
        // remove used hand from Player
        players.get(0).killHand();
        
        return result;
    }
    
    public int numHands() {
        return players.get(0).numHands();
    }
    
    public void killPlayer() {
        players.remove(0);
    }
    
    public void dealerMove() {
       
        // not sure if this while loop will validate
        while ( dealer.getHandValue() < 17 )
            dealerHit();
        
    }
    
    public void print() {
        players.get(0).printHand();
    }
}
