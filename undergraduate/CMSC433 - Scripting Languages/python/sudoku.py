#!/usr/bin/env python

# function to generate a Sudoku puzzle - canned for now
def get_puzzle():
    """
    Dynamically generates a symmetric Sudoku puzzle with a unique solution.
    
    @return: A 2 element tupple consisting of (2) 2-dimensional arrays.
    The first 2D array is a 9x9 grid which is the Sudoku problem with
    "givens" specified with the 1-9 value and "unknowns" noted by a 
    zero.  The second 2D array is a 9x9 grid containing the Sudoku solution.

    @rtype: list of lists
    @author: U{Daniel J. Hood<http://userpages.umbc.edu/~dhood2/>}
    @organization: U{CMSC 433 - Spring 2006<http://userpages.umbc.edu/~dhood2/courses/cmsc433/spring2006/>}

    
    """

    problem = [[5,3,0,0,7,0,0,0,0],
               [6,0,0,1,9,5,0,0,0],
               [0,9,8,0,0,0,0,6,0],
               [8,0,0,0,6,0,0,0,3],
               [4,0,0,8,0,3,0,0,1],
               [7,0,0,0,2,0,0,0,6],
               [0,6,0,0,0,0,2,8,0],
               [0,0,0,4,1,9,0,0,5],
               [0,0,0,0,8,0,0,7,9]]
    
    solution = [[5,3,4,6,7,8,9,1,2],
                [6,7,2,1,9,5,3,4,8],
                [1,9,8,3,4,2,5,6,7],
                [8,5,9,7,6,1,4,2,3],
                [4,2,6,8,5,3,7,9,1],
                [7,1,3,9,2,4,8,5,6],
                [9,6,1,5,3,7,2,8,4],
                [2,8,7,4,1,9,6,3,5],
                [3,4,5,2,8,6,1,7,9]]

    return (problem, solution)


# if module was run as stand alone script
if __name__ == '__main__':

    # fetch a puzzle
    problem, sol =  get_puzzle()

    # replace with strings
    for row in range(9):
        for col in range(9):
            if problem[row][col] == 0:
                problem[row][col] = " "
            else:
                problem[row][col] = str(problem[row][col])

    # print puzzle
    for row in range(9):
        print "%s %s %s | %s %s %s | %s %s %s" % tuple(problem[row])
        if (row == 2) or (row == 5):
            print ("-" * 6) + "+" + ("-" * 7) + "+" + ("-" * 6)
