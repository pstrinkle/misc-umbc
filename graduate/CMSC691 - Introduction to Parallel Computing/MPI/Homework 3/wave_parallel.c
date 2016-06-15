/*
 * MPI homework 3 
 * parallel 2-d decomp version
 * Patrick Trinkle
 * Spring 2009
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define PI 3.1415926
#define GridSizeX 512
#define GridSizeY 1024

double grid[GridSizeX + 2][GridSizeY + 2]; //extra 2 grid points as boundary
double new_grid[GridSizeX + 2][GridSizeY + 2];
double old_grid[GridSizeX + 2][GridSizeY + 2];

main(int argc, char *argv[])
{
   int x, y;
   int itime, itime_max = 10;
   double starttime, endtime;
   FILE *out1 = NULL;

   // MPI Stuff
   MPI_Comm comm;
   MPI_Status status;
   MPI_Datatype datarow, datacol;

   int xdim = 2;
   int ydim = 4;

   int xsize = GridSizeX / xdim;
   int ysize = GridSizeY / ydim;

   int rank, size;
   int dim[2], period[2], reorder, coord[2];
   
   double dt, dx, dy, dtx2, dty2;

   dt = 0.01;
   
   dx = 2 * PI/GridSizeX;
   dy = 2 * PI/GridSizeY;
   
   dtx2 = dt * dt/(dx * dx);
   dty2 = dt * dt/(dy * dy);
   
   //interior
   //initialization 
   for (x = 1; x <= GridSizeX; x++)
   {
      for (y = 0; y <= GridSizeY; y++)
      {
	 grid[x][y] = 
	    sin(x * (2 * PI/ GridSizeX)) * cos(y * (2 * PI / GridSizeY));

	 old_grid[x][y] = grid[x][y] * 0.90; //assume some difference
	 new_grid[x][y] = 0;
      }
   }
   
   // setup MPI Stuff
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   MPI_Type_contiguous(ysize, MPI_DOUBLE, &datarow);
   MPI_Type_commit(&datarow);

   MPI_Type_vector(xsize, 1, GridSizeY, MPI_DOUBLE, &datacol);
   MPI_Type_commit(&datacol);

   if (size != xdim * ydim)
   {
      printf("Please run with %d processes.\n", xdim * ydim);
      fflush(stdout);
      
      MPI_Abort(MPI_COMM_WORLD, 1);
   }
   else if (rank == 0)
   {
     printf("Running with %d processes.\n", size);
   }

   dim[0] = xdim; /* row dim */
   dim[1] = ydim; /* column dim */
   period[0] = 0;
   period[1] = 1;
   reorder = 1;

   MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);
   MPI_Cart_coords(comm, rank, 2, coord);
   
   printf("Rank %d coordinates are (%d, %d)\n", rank, coord[0], coord[1]);

   int left, right, above, below; /* cartesian coords */
   
   MPI_Cart_shift(comm, 0, 1, &below, &above);
   MPI_Cart_shift(comm, 1, 1, &left, &right);

   printf(
	  "me: %d, below: %d, above: %d left: %d right: %d\n",
	  rank,
	  below,
	  above,
	  left,
	  right);

   /* for each row{ for each column } in our piece */
   int xstart = coord[0] * xsize + 1;
   int ystart = coord[1] * ysize + 1;
   
   printf(
	  "me (%d, %d): xs: %d, ys: %d\n",
	  coord[0],
	  coord[1],
	  xstart,
	  ystart);
   
   starttime = MPI_Wtime();

   for (itime = 0; itime < itime_max; itime++)
   {
      //interior grid points

      // ghost region IO

      // send top row & place in bottom
      if (above != MPI_PROC_NULL) {
	
	MPI_Send(&(grid[xstart + xsize - 1][ystart]),
		 1,
		 datarow,
		 above,
		 rank,
		 comm);
	
	MPI_Recv(
		 &(grid[xstart - 1][ystart]),
		 1,
		 datarow,
		 above,
		 above,
		 comm,
		 &status);
      }
      
      // send bottom row & place on top
      if (below != MPI_PROC_NULL) {
	MPI_Send(&(grid[xstart][ystart]), 1, datarow, below, rank, comm);
	
	MPI_Recv(
		 &(grid[xstart + xsize][ystart]),
		 1,
		 datarow,
		 below,
		 below,
		 comm,
		 &status);
      }
      
      // send column left & place right
      MPI_Send(&(grid[xstart][ystart]), 1, datacol, left, rank, comm);
      
      MPI_Recv(
	       &(grid[xstart][ystart + ysize]),
	       1,
	       datacol,
	       right,
	       right,
	       comm,
	       &status);
      
      // send column right & place left
      MPI_Send(
	       &(grid[xstart][ystart + ysize - 1]),
	       1,
	       datacol,
	       right,
	       rank,
	       comm);
      
      MPI_Recv(
	       &(grid[xstart][ystart - 1]),
	       1,
	       datacol,
	       left,
	       left,
	       comm,
	       &status);
      
      //integration width a finite difference scheme (centered, second order)
      for (x = xstart; x < xstart + xsize ; x++)
      {
	 for (y = ystart; y < ystart + ysize; y++)
	 {
	    new_grid[x][y] = 
	       2 * grid[x][y] - old_grid[x][y] 
	       + dtx2 * (grid[x + 1][y] - 2 * grid[x][y] + grid[x - 1][y])
	       + dty2 * (grid[x][y + 1] - 2 * grid[x][y] + grid[x][y - 1]);
	 }
      }

      //update
      for (x = xstart; x < xstart + xsize; x++)
      {
	 for (y = ystart; y < ystart + ysize; y++)
	 {
	    old_grid[x][y] = grid[x][y];
	    grid[x][y] = new_grid[x][y];
	 }
      }
   } // end time step 

   endtime = MPI_Wtime();

   char outfile[8] = "output1";
   outfile[6] += rank;

   out1 = fopen(outfile, "w");

   for (x = xstart; x < xstart + xsize; x++) {
     for (y = ystart; y < ystart + ysize; y++) {
       fprintf(out1, "%d %d  %lf \n ", x, y, grid[x][y]);
     }
     fprintf(out1, "\n");
   }

   fclose(out1);

   if (rank == 0) {
     printf("Time: %f\n", endtime - starttime);
   }

   MPI_Finalize();

   return 0;
}
