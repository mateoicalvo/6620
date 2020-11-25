#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef struct matrix {
	size_t rows;
	size_t cols;
	double* array;
} matrix_t;

/* prototypes */
char* read_line(FILE*);

matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2, int bs);

matrix_t* create_matrix(size_t rows, size_t cols);

void destroy_matrix(matrix_t* m);

int print_matrix(FILE* fp, matrix_t* m);

int
main(int argc, char** argv)
{
	/* matrixes */
	matrix_t *a, *b, *c;
	/* n (dimension) and block size */
	size_t n, bs;
	/* line buffer (init to null to simplify freeing on error) */
	char *line = NULL;
	/* line parsing auxiliar pointers */
	char *nptr, *endptr;
	/* auxiliar variables */
	long l;
	double e;
	size_t lineno = 1;
	struct timespec t0;
	struct timespec t1;
	double dt;
	size_t i;

	for(; !feof(stdin); lineno++) {
		a=b=c=NULL;

		line = read_line(stdin);

		if (!line) goto _exit_main;
		if (line[0] == 0) break;

		/* parse dimension */
		nptr = line;
		l = strtol(nptr, &endptr, 10);
		if (errno) {
			perror("");
			goto _exit_main;
		}
		if (nptr == endptr) {
			fprintf(stderr, "missing dimension");
			goto _exit_main;
		}
		if (l < 1) {
			fprintf(stderr, "invalid dimension");
			goto _exit_main;
		}
		n = (size_t) l;
#if 0
		/* parse block size */
		nptr = endptr;
		l = strtol(nptr, &endptr, 10);
		if (errno) {
			perror("");
			goto _exit_main;
		}
		if (nptr == endptr) {
			fprintf(stderr, "missing block size");
			goto _exit_main;
		}
		if (l < 1) {
			fprintf(stderr, "invalid block size");
			goto _exit_main;
		}
		bs = (size_t) l;

		if (n % bs) {
			fprintf(stderr, "block size doesn't match");
			goto _exit_main;
		}
#else
		bs = n;
#endif

		/* load matrix a */
		if (!(a = create_matrix(n, n)))
			goto _exit_main;
		
		for (i=0; i < n*n; i++) {
			nptr = endptr;
			e = strtod(nptr, &endptr);
			if (errno) {
				perror("");
				goto _exit_main;
			}
			if (nptr == endptr) {
				fprintf(stderr, "missing A matrix element");
				goto _exit_main;
			}
			a->array[i] = e;
		}

		/* load matrix b */
		if (!(b = create_matrix(n, n)))
			goto _exit_main;
		
		for (i=0; i < n*n; i++) {
			nptr = endptr;
			e = strtod(nptr, &endptr);
			if (errno) {
				perror("");
				goto _exit_main;
			}
			if (nptr == endptr) {
				fprintf(stderr, "missing B matrix element");
				goto _exit_main;
			}
			b->array[i] = e;
		}

		clock_gettime(CLOCK_REALTIME, &t0);

		/* multiply matrixes */
		if (!(c = matrix_multiply(a, b, bs)))
			goto _exit_main;

		clock_gettime(CLOCK_REALTIME, &t1);
			
		dt = (float) (t1.tv_sec - t0.tv_sec);
		dt = dt + ((float)(t1.tv_nsec - t0.tv_nsec)) / 1.0e9;

		if(print_matrix(stdout, c) == -1)
			goto _exit_main;

		fprintf(stderr, "time: %g\n", dt);

		free(line);
		destroy_matrix(a);
		destroy_matrix(b);
		destroy_matrix(c);
	}

	return 0;

_exit_main:
	fprintf(stderr, " at line %u\n", (unsigned) lineno);
	free(line);
	destroy_matrix(a);
	destroy_matrix(b);
	destroy_matrix(c);
	exit(1);
}

matrix_t*
matrix_multiply(matrix_t* m1, matrix_t* m2, int bs)
{
	size_t n, en, i, j, k, kk, jj;
	double sum;
	matrix_t* mr;

	n = m1->rows;

	if(!(mr = create_matrix(n,n))) return NULL;

	en = bs*(n/bs);

	for(i=0; i<n; i++)
		for(j=0; j<n; j++) 
			mr->array[i*n+j] = 0.0;

#if 1
	if (1) {
		size_t j;
		size_t dim = 1024*1024*10;
		int *v = malloc(dim*sizeof(int));
		for (j = 0; j < dim; ++j)
			v[j] = -1;
		free(v);
	}
#endif

	for(kk=0; kk<en; kk+=bs) 
		for(jj=0; jj<en; jj+=bs) 
			for(i=0; i<n; i++) 
				for(j=jj; j<jj+bs; j++) {
					sum = mr->array[i*n+j];
					for(k=kk; k<kk+bs; k++) 
						sum += m1->array[i*n+k] * m2->array[k*n+j];  
					mr->array[i*n+j] = sum;
				}
	return mr;
}

char*
read_line(FILE *fp)
{
#define DEF_LINE_SZ 1024

	int c;
	size_t len = 0, tam = DEF_LINE_SZ;
	char* str;

	str = malloc(tam);
	if (!str) {
	    	perror("");
		return NULL;
	}

	while (EOF != (c=fgetc(fp)) && c != '\n') {
		str[len++]=c;
		if (len==tam-1) {
			str = realloc(str, tam *= 2);
			if (!str) {
				perror("");
				return NULL;
			}
		}
	}

	if (c != EOF)
		str[len++]='\n';

	str[len++]='\0';
	return str;
}


matrix_t*
create_matrix(size_t rows, size_t cols)
{
	matrix_t * m;

	if (!(m = malloc(sizeof(matrix_t)))) {
		perror("");
		return NULL;
	}

	m->rows = rows;
	m->cols = cols;
	if (!(m->array = malloc(sizeof(double)*rows*cols))) {
		free(m);
		perror("");
		return NULL;
	}
	
	return m;
}

void
destroy_matrix(matrix_t* m)
{
	if (!m) return;
	free(m->array);
	free(m);
}
		
int
print_matrix(FILE* fp, matrix_t* m)
{
	size_t i, j;
	size_t n;
	n = m->rows;
	if (fprintf(fp, "%lu", (unsigned long) m->rows) < 0) {
		perror("");
		return -1;
	}
	for(i=0; i<n; i++)
		for (j=0; j<n; j++) 
			if (fprintf(fp, " %g", m->array[i*n+j]) < 0) {
				perror("");
				return -1;
			}
	if (fprintf(fp, "\n") < 0) {
		perror("");
		return -1;
	}
	return 0;
}
