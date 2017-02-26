/*	$Antares: cpuperc.c,v 1.0 2017/02/26 21:10 sam Exp $	*/

/*
 * Copyright (c) 2017 Rodrigo González López
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef nil
#define nil	((void*)0)
#endif

#define PROCSTAT	"/proc/stat"
#define DELAY		1

typedef long long vlong;

int
main(void)
{
	int perc;
	vlong a[4], b[4];
	FILE *fp;

	fp = fopen(PROCSTAT, "r");
	if (fp == nil) {
		fprintf(stderr, "Failed to open %s\n", PROCSTAT);
		return EXIT_FAILURE;
	}

	if (fscanf(fp, "%*s %lld %lld %lld %lld",
	           &a[0], &a[1], &a[2], &a[3]) == EOF) {
		fprintf(stderr, "Error processing input from %s\n", PROCSTAT);
	}
	fclose(fp);

	sleep(DELAY);

	fp = fopen(PROCSTAT, "r");
	if (fp == nil) {
		fprintf(stderr, "Failed to open %s\n", PROCSTAT);
		return EXIT_FAILURE;
	}

	if (fscanf(fp, "%*s %lld %lld %lld %lld",
	           &b[0], &b[1], &b[2], &b[3]) == EOF) {
		fprintf(stderr, "Error processing input from %s\n", PROCSTAT);
	}
	fclose(fp);

	perc = 100 * ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2]))
			/ ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));
	printf("%d%%\n", perc);

	return EXIT_SUCCESS;
}
