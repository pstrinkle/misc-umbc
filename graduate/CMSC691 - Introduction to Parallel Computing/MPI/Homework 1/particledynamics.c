//this is serial code

//get the value of END_OF_TIME from a terminal
#define PARTICLES 1000000

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
      float x, y, z, w;
} vec4D;

vec4D pos[PARTICLES];
vec4D vel[PARTICLES]; 

// current force being applied to the particles
vec4D force;

// inverse mass of the particles
float inv_mass[PARTICLES];

// step in time
float dt = 0.01f;

double temperature;  

int main() 
{
   int i, j, k;
   float time;
   float dt_inv_mass;
   int end_of_time = 0;
   
   // No error or type checking is done!
   printf("Enter end of time: ");
   scanf("%d", &end_of_time);
   
   printf("You entered: %d\n", end_of_time);
   
   // Initialize velocities with the random numbers between 0 and 1
   for (i = 0; i < PARTICLES; i++)
   {
      vel[i].x = drand48();
      vel[i].y = drand48();
      vel[i].z = drand48();
   }
   
   printf("Particle Velocities Initialized\n");
   
   // Initialize the x, y, z force components of each particle with 0.01
   force.x = 0.01;
   force.y = 0.01;
   force.z = 0.01;
   
   printf("Force Initialized\n");
   
   // Initialize Positions
   for (i = 0; i < 100; i++)
   {
      for (j = 0; j < 100; j++)
      {
	 for (k = 0; k < 100; k++)
	 {
	    pos[i*(100*100) + j*100 +k].x = i*0.1;
	    pos[i*(100*100) + j*100 +k].y = j*0.1;
	    pos[i*(100*100) + j*100 +k].z = k*0.1;
	 }
      }
   }
   
   printf("Positions Initialized\n");
   
   // Initialize mass
   for (i = 0; i < PARTICLES; ++i)
   {
      inv_mass[i] = 1.0;
   }
   
   printf("Inv_Masses Initialized\n");

   // For each step in time 
   for (time = 0; time < end_of_time; time += dt) 
   { 
      temperature = 0;
      
      // For each particle
      for (i = 0; i < PARTICLES; i++) 
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
	 temperature += (1.0/PARTICLES)*(vel[i].x * vel[i].x + vel[i].y*vel[i].y + vel[i].z*vel[i].z);
      }
   }
   
   printf("Finished: %f\n", temperature);

   return (0); 
}
