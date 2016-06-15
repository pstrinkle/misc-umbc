/* EmptyDeckException.java
 *
 * Author: Jason Gaertner
 * Email: jasong1@umbc.edu
 * Created on July 18, 2005, 9:28 PM
 * BlackJack Project 2
 * CMSC 331
 * Summer 05
 */

public class EmptyDeckException extends java.lang.Exception {
    
    /**
     * Creates a new instance of <code>EmptyDeckException</code> without detail message.
     */
    public EmptyDeckException() {
    }
    
    
    /**
     * Constructs an instance of <code>EmptyDeckException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public EmptyDeckException(String msg) {
	super(msg);
    }
}