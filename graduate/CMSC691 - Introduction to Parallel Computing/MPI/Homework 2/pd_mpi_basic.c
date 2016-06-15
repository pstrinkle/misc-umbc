
/**************
 * Patrick Trinkle
 * tri1@umbc.edu
 * Spring 2009
 * CMSC691 - MPI
 * Project 3
 **************/

/**************
 * Includes
 **************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

/****************
 * Defines
 ****************/

#define END_OF_TIME 10
#define PARTICLES 1000000

/*****************
 * Data Structures
 *****************/

typedef struct
{
      float x, y, z, w;
} vec4D;

/***************
 * Global Variables
 ***************/

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

/*********************
 * Main Execution
 *********************/

int main( int argc, char *argv[] )
{
   int i, j, k;
   int numprocs, myid;
   int block = 0;
   float time, dt_inv_mass;
   double mytemp = 0.0;
   double starttime, endtime;
   MPI_Status status;
   
   
   temperature = 0;

   MPI_Init(&argc, &argv);

   // numprocs must evenly divide into 100
   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

   MPI_Comm_rank(MPI_COMM_WORLD, &myid);

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
      // I did optimize this, but provided no boost
      // so I let it be.
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

      // so we now have the end of time temperature calculated
      MPI_Send(&mytemp, 1, MPI_DOUBLE, 4, myid, MPI_COMM_WORLD);
   }
   else if (myid == 4)
   {
      // for loop while receiving until you've received four times
      unsigned int i = 0;
      double buf = 0.0;

      temperature = 0.0;

      for (i = 0; i < 4; ++i)
      {
	 MPI_Recv(
	    &buf,
	    1,
	    MPI_DOUBLE,
	    MPI_ANY_SOURCE,
	    MPI_ANY_TAG,
	    MPI_COMM_WORLD,
	    &status);

	 temperature += buf;
      }
      
      MPI_Send(&temperature, 1, MPI_DOUBLE, 5, myid, MPI_COMM_WORLD);
   }
   else
   {
      MPI_Recv(
	 &temperature,
	 1,
	 MPI_DOUBLE,
	 4,
	 MPI_ANY_TAG,
	 MPI_COMM_WORLD,
	 &status);

      printf("Finishing: %f\n", temperature);
   }
   
   endtime = MPI_Wtime();
   
   if (myid == 0)
   {
      printf("Time: %f\n", endtime - starttime);
   }
   
   MPI_Finalize();

   return (0); 
}

