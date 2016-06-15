/* BlackJackDealer.java
 *
 * Author: Mike Simms
 * Email: simms1@umbc.edu
 * Created on July 14, 2005, 4:30 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

import java.io.*;
import java.util.Random;
import java.util.ArrayList;
import java.net.*;

public class BlackJackDealer {
      
    public BlackJackDealer() {
    }

    public static void main(String[] args) throws IOException {   

        ObjectOutputStream out = null;
        ObjectInputStream in = null;
        Socket clientSocket = null;
        ArrayList<Socket> socketList = null;
        Game theGame = null;
        int numClients = 0;
        
        //checks for how many clients are connecting
        try {
            int port = 1; //not 0, cause that would always find a server
            if (args.length > 1)
            {
               port = Integer.parseInt(args[0]);  
               numClients = Integer.parseInt(args[1]);
            }
            else
            {
                System.out.println("Requires a port number to be entered and a number of clients");
                System.exit(1);
            }
            
            ServerSocket srv = new ServerSocket(port);
            System.out.println("Server made, checking for client");       
            
            socketList = new ArrayList<Socket>();
//need to make this a wait
            int g = 0;
            while(g != numClients ){            
            clientSocket = srv.accept(); //accepts a client
            socketList.add(clientSocket); //adds a new client to arraylist
            g++;
            System.out.println("Client Found");
            }  //end of while loop 
        } catch (IOException e) {  
            System.out.println("Exception, couldn't make server");
            System.exit(1);
        }
        //sets up game object with number of players
        theGame = new Game(socketList.size());
        
        theGame.deal();
        //the dealer plays his hand
        theGame.dealerMove();
        
        try{     
            for(int k = 0; k < socketList.size(); k++){        
                clientSocket = socketList.get(k);
                out = new ObjectOutputStream(clientSocket.getOutputStream());
                in = (new ObjectInputStream(clientSocket.getInputStream()));
                //not sure if need
                //BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
                //send game object to client to have it deal cards
                out.writeObject(theGame);
                out.flush();
                theGame = (Game)in.readObject();
                theGame.killPlayer();
            }//end  for loop
               
        } catch (ClassNotFoundException e) {
          System.out.println("Class not found");
        }

        
        out.close();
	in.close();
	//stdIn.close();
	clientSocket.close();
    }
}