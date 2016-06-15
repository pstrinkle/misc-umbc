/******************************************
** Filename: BlackJackPlayer.java
** Author: Lukasz Kalmus
** Email: lka1@umbc.edu
** Date: July 18th, 2005 
** 
** CMSC 331 Summer 05 Project 2(Blackjack)
** 
** This file contains the client class, which represents 
** a player at a Blackjack table. 
*******************************************/

import java.io.*;
import java.net.*;

public class BlackJackPlayer {
        
   public static void main(String[] args) throws IOException {

      if ( args.length != 2 )
      {
          System.out.println("Not Enough Command Line Arguments");
          System.out.println("Format: IP/Hostname Port");
          System.exit(-1);
      }
      
      String hostName = args[0];
      int port = Integer.parseInt(args[1]);
      
      ObjectOutputStream out = null;
      ObjectInputStream in = null;
      Socket playerSocket = null;
   
      try {
         playerSocket = new Socket(hostName, port);
         out = new ObjectOutputStream(playerSocket.getOutputStream());
         in = new ObjectInputStream(playerSocket.getInputStream());
      }
      catch (UnknownHostException e) {
         System.err.println("Don't know about host: " + hostName);
         System.exit(1);
      }           
      catch (IOException e) {
         System.out.println("Could not get I/O for the connection to: " + hostName);
         System.exit(1);
      }
   
      BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
      String input;
      
      Game playerHand = null;
   
      try {
         playerHand = (Game)in.readObject();
         //playerHand.print();
      } 
      catch (ClassNotFoundException e) {
         System.out.println("Game not found");
      }
   
      System.out.println("Enter one of the following commands: hit, stay, split");
      System.out.println("You can only split if the values of your only two cards match");

      while ( playerHand.numHands() != 0 )
      {
          playerHand.print();               //testing
         input = " ";                      //stdIn.readLine();
         while ( !input.equalsIgnoreCase("stay") && !playerHand.Busted())
         {
            input = stdIn.readLine();      //testing
            if ( input.equalsIgnoreCase("hit") )
            {
               System.out.println("Command: hit"); 
               playerHand.hit();
               playerHand.print();
            }
            else if ( input.equalsIgnoreCase("split") )
            {
               System.out.println("Command: split");
               playerHand.split();
               playerHand.print();
            }
            else if (input.equalsIgnoreCase("stay")){
               //do nothing
            }
            else
            {
               System.out.println("Invalid Command: " + input);
            }
            // get next input from user
            //input = stdIn.readLine();
         }
         // staying only kills the top hand, the player may have more
         System.out.println(playerHand.stay());
      }
   
      out.writeObject(playerHand);
      out.flush();
   
      out.close();
      in.close();
      playerSocket.close();
   }
}

