#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/oasis.h"

#if defined(_MSC_VER)
#include "../wingetopt/wingetopt.h"
#else
#include <unistd.h>
#endif



void doit()
{

	aggregate_areaperil_to_areaperil q;
	char line[4096];
	int lineno = 0;
	fgets(line, sizeof(line), stdin); // skip header line
	lineno++;
	while (fgets(line, sizeof(line), stdin) != 0)
	{
#ifdef AREAPERIL_TYPE_LONG
		int ret = sscanf(line, "%ld,%ld",  &q.aggregate_areaperil_id, &q.areaperil_id);
#else
		int ret = sscanf(line, "%d,%d", &q.aggregate_areaperil_id, &q.areaperil_id);
#endif 

		if (ret != 2) {
			fprintf(stderr, "Invalid data in line %d:\n%s", lineno, line);
			return;
		}
		else
		{
			fwrite(&q, sizeof(q), 1, stdout);
		}
		lineno++;
	}

}

void help()
{
	fprintf(stderr, "-h help\n-v version\n");
}

int main(int argc, char* argv[])
{

	int opt;

	while ((opt = getopt(argc, argv, (char *) "vh")) != -1) {
		switch (opt) {
		case 'v':
			fprintf(stderr, "%s : version: %s\n", argv[0], VERSION);
			exit(EXIT_FAILURE);
			break;
		case 'h':
		default:
			help();
			exit(EXIT_FAILURE);
		}
	}
	initstreams("", "");
	doit();

	return EXIT_SUCCESS;

}