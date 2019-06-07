#define MEOW_FFT_IMPLEMENTATION
#include "meow_fft.h"
#include <malloc.h>
#include <math.h>

// compile as: gcc example.c -lm

int  main(int argc, char** argv)
{
	unsigned          N   = 1024;
	float*            in  = (float*) malloc(sizeof(float) * N);
	Meow_FFT_Complex* out = (Meow_FFT_Complex*) malloc(sizeof(Meow_FFT_Complex) * N);

	// prepare data for "in" array.
	
	int i;
	for (i=0; i<N; i++){
		in[i]= (sin((double)i/10));
		}
	
	size_t workset_bytes = meow_fft_generate_workset_real(N, NULL);
	// Get size for a N point fft working on non-complex (real) data.

	Meow_FFT_Workset_Real* fft_real =
		(Meow_FFT_Workset_Real*) malloc(workset_bytes);

	meow_fft_generate_workset_real(N, fft_real);

	meow_fft_real(fft_real, in, out);
	out[0].r == 0;
	//out[0].j == out[N/2].r

	for (i=0; i<N; i++){
		printf("%f %f\n",in[i], out[i].r);
		}
	
	//meow_fft_real_i(fft_real, in, out);
	// result is not scaled, need to divide all values by N

	free(fft_real);
	free(out);
	free(in);
}
