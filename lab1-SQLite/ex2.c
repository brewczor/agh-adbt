#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/resource.h>

//komenda kompilacji
//gcc ex2.c -o build/ex2 -lsqlite3

const int MAX = 1000000;

struct rusage mem;

int main() {
	printf("SecondTask\n");
	clock_t c1,c2;
	char sql[1024]; //bufor
	int i; //licznik :)

	//nawiazanie polaczenia
	int rc;
	sqlite3 *db;
	char loc[]=":memory:";

	rc=sqlite3_open(loc,&db);
  	if (rc) {
   	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   	return 1;
  	}

	printf("Inserting\n");
	c1=clock();
	sqlite3_exec(db, "BEGIN TRANSATION", NULL, NULL, NULL);
	sqlite3_exec(db, "create table rec(id integer primary key, name varchar(20), desc varchar(90))", NULL, NULL, NULL); 
	for(i=0; i<MAX; i++) {
		sprintf(sql, "insert into rec values('%d', 'name', 'description')", i);
		sqlite3_exec(db, sql, NULL, NULL, NULL);
	}
	sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
	c2=clock();

	printf("time, c2-c1[s]: %f\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

	//searching
	printf("search\n");
	c1=clock();
	sqlite3_exec(db, "select * from values where id='999999'", NULL, NULL, NULL); 
	c2=clock();
	printf("time, c2-c1[s]: %f\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

	getrusage(RUSAGE_SELF,&mem);
	printf("Max mem usage[kB]: %ld\n", mem.ru_maxrss);
	
	//zamkniecie polaczenia
	sqlite3_close(db);
}
