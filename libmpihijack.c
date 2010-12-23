/*
 * 	libhijack.c -- function interposition library for MPI primitives
 *
 * 	Author: Javier Martinez Canillas <martinez.javier@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include <mpi.h>

int MPI_Init(int *argc, char ***argv)
{
	static int (*real_MPI_Init)(int *, char ***) = NULL;
	int result;

        fprintf(stderr,"MPI_Init interposition invoked argc=%d argv=%p\n", *argc, argv);

	real_MPI_Init = dlsym(RTLD_NEXT, "MPI_Init");
	
	if(!real_MPI_Init)
		return MPI_ERR_INTERN;

	result = real_MPI_Init(argc, argv);

	return result;
}

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, 
	     int tag, MPI_Comm comm )
{
	static int (*real_MPI_Send)(void *, int, MPI_Datatype, int, int, MPI_Comm) = NULL;

	int result;

	fprintf(stderr,"MPI_Send interposition invoked buf=%p count=%d dest=%d tag=%d\n", buf, count, dest, tag);

	real_MPI_Send = dlsym(RTLD_NEXT, "MPI_Send");

	if(!real_MPI_Send)
		return MPI_ERR_INTERN;

	result = real_MPI_Send(buf, count, datatype, dest, tag, comm);
     
	return result;
}

int MPI_Isend( void *buf, int count, MPI_Datatype datatype, int dest, int tag,
               MPI_Comm comm, MPI_Request *request)
{
	static int (*real_MPI_Isend)(void *, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *) = NULL;

	int result;

        fprintf(stderr,"MPI_Isend interposition invoked buf=%p count=%d dest=%d tag=%d\n", buf, count, dest, tag);

	real_MPI_Isend = dlsym(RTLD_NEXT, "MPI_Isend");

	if(!real_MPI_Isend)
		return MPI_ERR_INTERN;

	result = real_MPI_Isend(buf, count, datatype, dest, tag, comm, request);

	return result;
}

int MPI_Recv( void *buf, int count, MPI_Datatype datatype, int source, 
              int tag, MPI_Comm comm, MPI_Status *status )
{
	static int (*real_MPI_Recv)(void *, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status*) = NULL;

	int result;

	fprintf(stderr,"MPI_Recv interposition invoked buf=%p count=%d source=%d tag=%d status=%p\n", buf, count, source, tag, status);

	real_MPI_Recv = dlsym(RTLD_NEXT, "MPI_Recv");

	if(!real_MPI_Recv)
		return MPI_ERR_INTERN;

	result = real_MPI_Recv(buf, count, datatype, source, tag, comm, status);
      
	return result;
}


