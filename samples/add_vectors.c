#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define VECTOR_SIZE 32

USE_ARITHMETIC_OP_SET_FP32

int main(void) {
	// Allocate two 32-dimensional FP32 vectors
	MAKE_VECTOR_FAST(vf32_MyVector, float, VECTOR_SIZE, FP32)
  MAKE_VECTOR_FAST(vf32_MyOtherVector, float, VECTOR_SIZE, FP32)

	printf("Created 2 vectors each of size %lu bytes!\n", vf32_MyVector.sz_BufferSize);

	// Populate vector with simple pattern
	float f32_MyFloat = 0;
	for (size_t sz_Idx = 0; sz_Idx < VECTOR_SIZE; ++sz_Idx) {
    	vctwrite(&vf32_MyVector, sz_Idx, &f32_MyFloat);
    	vctwrite(&vf32_MyOtherVector, sz_Idx, &f32_MyFloat);

    	f32_MyFloat += 1.0F;
	}

	// Optional: verify that no data was overwritten
	float f32_OverwriteCheck = 0;
	for (size_t sz_Idx = 0; sz_Idx < VECTOR_SIZE; ++sz_Idx) {
    	vctread(&f32_OverwriteCheck, &vf32_MyVector, sz_Idx);
    	printf("ELEMENT AT %lu: %f\n", sz_Idx, f32_OverwriteCheck);
	}

  MAKE_VECTOR_FAST(vf32_MySum, float, VECTOR_SIZE, FP32)

  vctadd(&vf32_MySum, &vf32_MyVector, &vf32_MyOtherVector);

  float f32_MyElement = 0;
  for (size_t sz_Idx = 0; sz_Idx < VECTOR_SIZE; ++sz_Idx) {
      vctread(&f32_MyElement, &vf32_MySum, sz_Idx);
      printf("SUM AT %lu: %f\n, sz_Idx, f32_MyElement);
  }

  vcdstry(&vf32_MySum);
	vctdstry(&vf32_MyVector);
	vctdstry(&vf32_MyOtherVector);

	return EXIT_SUCCESS;
}
