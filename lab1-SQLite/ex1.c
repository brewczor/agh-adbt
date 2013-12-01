#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/resource.h>

//ile alkowanych rekordow
const int RECCOUNT = 1000000;

//zdefiniowanie struktury
typedef struct {
	int id;
	char name[20];
	char desc[90];
} Record;

struct rusage mem;

//alokujemy pamiec dla jednego rekordu
Record * record_new(int n)
{
	Record *r = malloc(sizeof(Record));
	if(r == NULL) {
		fprintf(stderr, "Mem alloc error\n");
		return NULL;
	}
   
	r->id = n;

	strcpy(r->name, "name");
	strcpy(r->desc, "desc");

	return r;
}

//zwolnienie pamieci
void record_free (Record *r)
{
	free(r);
}

int main() {
	printf("First task\n");
	clock_t c1,c2;

	
	printf("Allocating\n");
	c1=clock();

	Record **tablica = malloc(RECCOUNT*sizeof(Record*)); //*tablica[RECCOUNT];
	int i;
	for(i=0; i<RECCOUNT; i++) 
	{
		tablica[i] = record_new(i);
	}

	c2=clock();

	printf("time, c2-c1[s]: %f\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

	printf("Finding\n");
	c1=clock();
	int x = RECCOUNT-1;
	for(i=0; i<RECCOUNT; i++) {
		if(tablica[i]->id == x) {
			printf("found :)\n");
			break;
		}
	}
	c2=clock();

	printf("time, c2-c1[s]: %f\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

	getrusage(RUSAGE_SELF,&mem);
	printf("Max mem usage[kB]: %ld\n", mem.ru_maxrss);

	return 0;
}
