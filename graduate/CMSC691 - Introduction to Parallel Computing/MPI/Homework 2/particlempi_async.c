
/*************************************
 * Patrick Trinkle
 * tri1@umbc.edu
 * Spring 2009
 * CMSC691 - MPI
 * Project 2 - Asynchronous IO Version
 *************************************/

/*************************************
 * Includes
 *************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

/*************************************
 * Defines
 *************************************/

#define END_OF_TIME 1
#define PARTICLES 1000000

/* tags */
#define TOA 4
#define TOB 5

/*************************************
 * Data Structures
 *************************************/

typedef struct
{
      float x, y, z, w;
} vec4D;

/*************************************
 * Global Variables
 *************************************/

// particle position and velocity
vec4D pos[PARTICLES];
vec4D vel[PARTICLES]; 

// current force being applied to the particles
vec4D force;

// inverse mass of the particles
float inv_mass[PARTICLES];

// step in time
float dt = 0.01f;

double temperature;  

/****************************************************
 * Main Execution
 *
 * Uses 6 MPI Processes
 * P0-P3 Compute
 * P4 & P5 Output Results
 *
 * P0 & P1 Send data to P4
 * P2 & P3 Send data to P5
 * P4 Sends data to P5
 * P5 prints out the positions to an ascii text file
 *
 * P0-P3 Need to be in a worker group
 * P4,P5 Need to be in an I/O group
 *
 *****************************************************/

int main( int argc, char *argv[] )
{
   int i, j, k, numprocs, myid, serverA, serverB, ranks[2];
   int block = 0;
   float time, dt_inv_mass;
   double mytemp = 0.0;
   double starttime, endtime;
   FILE *out = NULL;

   temperature = 0;

   /* Currently world has everyone;
    * computers has 4 computing processes
    */

   MPI_Comm world, computers;
   MPI_Group world_group, computers_group;
   MPI_Status status, statuses[3];
   MPI_Request request, requests[3];

   MPI_Init(&argc, &argv);

   world = MPI_COMM_WORLD;

   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD, &myid);

   serverA = 4;
   serverB = 5;

   if (numprocs != 6)
   {
      printf("Huge Problem... Although could write adaptive code.\n");
   }

   MPI_Comm_group(world, &world_group);
   ranks[0] = serverA;
   ranks[1] = serverB;

   MPI_Group_excl(world_group, 2, ranks, &computers_group);
   MPI_Comm_create(world, computers_group, &computers);
   MPI_Group_free(&computers_group);

   // only 4 processors will be processing the data
   block = PARTICLES/4;

   if (myid == 0)
   {
      printf("block: %d\n", block);
   }

   starttime = MPI_Wtime();

   if (myid < 4)
   {
      // Initialize velocities with the random numbers between 0 and 1
      for (i = myid * block; i < block + (block * myid); ++i)
      {
	 vel[i].x = drand48();
	 vel[i].y = drand48();
	 vel[i].z = drand48();
      }
      
      if (myid == 0)
      {
	 printf("Particle Velocities Initialized\n");
      }
      
      // Initialize mass
      for (i = myid * block; i < block + (block * myid); ++i)
      {
	 inv_mass[i] = 1.0;
      }
      
      if (myid == 0)
      {
	 printf("Inv_Masses Initialized\n");
      }
      
      // Initialize the x, y, z force components of each particle with 0.01
      force.x = 0.01;
      force.y = 0.01;
      force.z = 0.01;
      
      if (myid == 0)
      {
	 printf("Force Initialized\n");
      }
      
      // Initialize Positions

      /* I did optimize this, but provided no boost
       * so I let it be. */
      for (i = 0; i < 100; ++i)
      {
	 for (j = 0; j < 100; ++j)
	 {
	    for (k = 0; k < 100; ++k)
	    {
	       pos[i*(100*100) + j*100 + k].x = i * 0.1;
	       pos[i*(100*100) + j*100 + k].y = j * 0.1;
	       pos[i*(100*100) + j*100 + k].z = k * 0.1;
	    }
	 }
      }

      if (myid == 0)
      {
	 printf("Particle Positions Initialized\n");
      }
      
      // For each step in time 
      for (time = 0; time < END_OF_TIME; time += dt) 
      {
	 mytemp = 0;
	 
	 // For each particle
	 // each processor handles 1/4th the particles per timeslice
	 for (i = myid * block; i < block + (block * myid); ++i)
	 {
	    // Compute the new position and velocity 
	    // as acted upon by the force f. 
	    pos[i].x = vel[i].x * dt + pos[i].x;
	    pos[i].y = vel[i].y * dt + pos[i].y;
	    pos[i].z = vel[i].z * dt + pos[i].z;
	    
	    dt_inv_mass = dt * inv_mass[i];
	    
	    vel[i].x = dt_inv_mass * force.x + vel[i].x;
	    vel[i].y = dt_inv_mass * force.y + vel[i].y;
	    vel[i].z = dt_inv_mass * force.z + vel[i].z;
	    
	    //updated line
	    mytemp += (1.0/PARTICLES) * (vel[i].x * vel[i].x 
					 + vel[i].y * vel[i].y 
					 + vel[i].z * vel[i].z);
	 }
      }

      /* vec4D pos[PARTICLES]
       * each vec4D is four floats
       * each buy only works on a block of it
       * therefore we're sending 4 * block MPI_FLOATS
       */

      if (myid == 0 || myid == 1)
      {
	 MPI_Isend(
	    &(pos[myid * block]), 
	    4 * block,
	    MPI_FLOAT,
	    serverA,
	    TOA,
	    world,
	    &request);
      }
      else
      {
	 MPI_Isend(
	    &(pos[myid * block]),
	    4 * block,
	    MPI_FLOAT,
	    serverB,
	    TOB,
	    world,
	    &request);
      }

      /* Do we need to waitall here? */

      MPI_Comm_free(&computers);
   }
   else if (myid == serverA)
   {
      /* we're waiting from data from either p0 or p1 */
      MPI_Irecv(&(pos[0]), 4 * block, MPI_FLOAT, 0, TOA, world, &requests[0]);
      MPI_Irecv(&(pos[block]), 4 * block, MPI_FLOAT, 1, TOA, world, &requests[1]);

      MPI_Waitall(2, requests, statuses);
  
      MPI_Isend(
	 &(pos[0]),
	 4 * block * 2,
	 MPI_FLOAT,
	 serverB,
	 TOB,
	 world,
	 &request);

      /* do we need to waitall here? */
   }
   else
   {
      unsigned int i, j;

      /* we're waiting for data from either p2, p3, or p4 */
      /* because we specify source we know right where it needs to end up */
      MPI_Irecv(
	 &(pos[2 * block]),
	 4 * block,
	 MPI_FLOAT,
	 2,
	 TOB,
	 world,
	 &requests[0]);
      MPI_Irecv(
	 &(pos[3 * block]),
	 4 * block,
	 MPI_FLOAT,
	 3,
	 TOB,
	 world,
	 &requests[1]);
      MPI_Irecv(&(pos[0]), 4 * block * 2, MPI_FLOAT, 4, TOB, world, &requests[2]);

      MPI_Waitall(3, requests, statuses);

      /* write output to a file */
      out = fopen("output_a.txt", "w");

      if (out != NULL)
      {
         fprintf(out, "pos[i] (x, y, z)\n");

         for (i = 0; i < PARTICLES; ++i)
         {
            fprintf(
               out,
               "pos[%d] (%f, %f, %f)\n",
               i,
               pos[i].x,
               pos[i].y,
               pos[i].z);
         }

         fclose(out);
      }

      endtime = MPI_Wtime();

      printf("Finishing\n");
      printf("Time: %f\n", endtime - starttime);
   }

   MPI_Finalize();

   return (0); 
}

