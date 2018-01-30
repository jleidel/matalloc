/*
 * _2D_C_
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


#define DIM_X 5
#define DIM_Y 5

void print_mat_addr( uint64_t **mat ){
  uint64_t i = 0x00ull;
  uint64_t j = 0x00ull;

  for( i=0; i<DIM_X; i++ ){
    for( j=0; j<DIM_Y; j++ ){
      printf( "Address of Mat[%" PRIu64 "][%" PRIu64 "] = %p\n",
              i, j, &(mat[i][j]) );
    }
  }

  uint64_t p1 = (uint64_t)(&mat[0][0]);
  uint64_t p2 = (uint64_t)(&mat[1][0]);

  printf( "Row stride = %" PRIu32 "bytes\n",
          (uint32_t)(p2-p1));

  p1 = (uint64_t)(&mat[2][0]);
  p2 = (uint64_t)(&mat[2][1]);

  printf( "Column stride = %" PRIu32 "bytes\n",
          (uint32_t)(p2-p1));
}

void efficient_2d(){
  uint64_t **mat = NULL;
  uint64_t *ptr = NULL;
  uint64_t i = 0x00ull;
  uint64_t j = 0x00ull;

  // allocate the matrix
  ptr = malloc( DIM_X * DIM_Y * sizeof( uint64_t ) );
  mat = malloc( DIM_X * sizeof( uint64_t *) );

  for( i=0; i<DIM_X; i++ ){
    mat[i] = &(ptr[i*DIM_Y]);
  }

  // init to all zeros
  for( i=0; i<DIM_X; i++ ){
    for( j=0; j<DIM_Y; j++ ){
      mat[i][j] = 0x00ull;
    }
  }

  // print the matrix
  print_mat_addr( mat );

  // free the matrix
  free( mat );
  free( ptr );
}

void naive_2d(){
  uint64_t **mat = NULL;
  uint64_t i = 0x00ull;
  uint64_t j = 0x00ull;

  // allocate the matrix
  mat = malloc( DIM_X * sizeof( uint64_t *) );
  for( i=0; i<DIM_X; i++ ){
    mat[i] = malloc( DIM_Y * sizeof( uint64_t ) );
  }

  // init to all zeros
  for( i=0; i<DIM_X; i++ ){
    for( j=0; j<DIM_Y; j++ ){
      mat[i][j] = 0x00ull;
    }
  }

  // print the matrix
  print_mat_addr( mat );

  // free the matrix
  for( i=0; i<DIM_X; i++ ){
    free( mat[i] );
  }
  free( mat );
}

int main( int argc, char **argv ){
  printf( "2D MATALLOC TEST\n" );

  printf( "------------ 2D NAIVE MATRIX ------------\n" );
  naive_2d();

  printf( "------------ 2D EFFICIENT MATRIX ------------\n" );
  efficient_2d();

  return 0;
}
