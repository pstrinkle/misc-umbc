/*
 * MPI homework 3 
 * serial version
 * Shujia Zhou
 * April 15, 2009
*/ 

// include when building on MPI
#include "mpi.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926
#define GridSizeX 16
#define GridSizeY 32

main(int argc, char *argv[])
{
	int x, y;
	int itime, itime_max=10;

	double dt, dx, dy, dtx2, dty2;

	double grid[GridSizeX + 2][GridSizeY + 2]; //extra 2 grid points as boundary      
	double new_grid[GridSizeX + 2][GridSizeY + 2];
	double old_grid[GridSizeX + 2][GridSizeY + 2];

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
			grid[x][y] = sin(x * (2 * PI/ GridSizeX)) * cos(y * (2 * PI / GridSizeY));
			old_grid[x][y] = grid[x][y]*0.90; //assume some difference
			new_grid[x][y] = 0;
		}
	}

	//output initial configuration
	//in the format for gnuplot
	for (x = 1; x <= GridSizeX; x++)
	{
		for (y = 1; y <= GridSizeY; y++)
		{
			printf("%d %d  %lf \n ", x, y, grid[x][y]);
		}
		printf("\n");
	}

	printf("\n");

	for (itime = 0; itime < itime_max; itime++)
	{
		//boundary condition
		//along x is free boundary
		old_grid[0][y] = 0;
		grid[0][y] = 0;
		new_grid[0][y] = 0;

		old_grid[GridSizeX + 1][y] = 0;
		grid[GridSizeX + 1][y] = 0;
		new_grid[GridSizeX + 1][y] = 0;

		//along y is periodic boundary
		old_grid[x][0] = old_grid[x][GridSizeY];
		grid[x][0] = grid[x][GridSizeY];
		new_grid[x][0] = new_grid[x][GridSizeY];

		old_grid[x][GridSizeY + 1] = old_grid[x][1]; 
		grid[x][GridSizeY + 1] = grid[x][1]; 
		new_grid[x][GridSizeY + 1] = new_grid[x][1]; 

		//interior grid points
		//integration with a finite difference scheme (centered, second order)
		for (x = 1; x <= GridSizeX; x++)
		{
			for (y = 1; y <= GridSizeY; y++)
			{
				new_grid[x][y] = 
					2 * grid[x][y] - old_grid[x][y] 
					+ dtx2 * (grid[x + 1][y] - 2 * grid[x][y] + grid[x - 1][y])
					+ dty2 * (grid[x][y + 1] - 2 * grid[x][y] + grid[x][y - 1]);
			}
		}

		//update
		for (x = 1; x <= GridSizeX; x++)
		{
			for (y = 1; y <= GridSizeY; y++)
			{
				old_grid[x][y] = grid[x][y];
				grid[x][y] = new_grid[x][y];
			}
		}
	}

	//output final configuration
	//in the format for gnuplot
	for (x = 1; x <= GridSizeX; x++)
	{
		for (y = 1; y <= GridSizeY; y++)
		{
			printf("%d %d  %lf \n ", x, y, grid[x][y]);
		}
		printf("\n");
	}

	return 0;
}
