/*	$Antares: sndvol.c,v 1.0 2017/02/26 21:26 sam Exp $	*/

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
#include <alsa/asoundlib.h>

#ifndef nil
#define nil	((void*)0)
#endif

#define SNDCARD "default"

int
main(void)
{
	long max, min, vol;
	snd_mixer_t *h;
	snd_mixer_elem_t *elem;
	snd_mixer_selem_id_t *selem;

	snd_mixer_open(&h, 0);
	snd_mixer_attach(h, SNDCARD);
	snd_mixer_selem_register(h, nil, nil);
	snd_mixer_load(h);
	snd_mixer_selem_id_malloc(&selem);
	snd_mixer_selem_id_set_name(selem, "Master");
	elem = snd_mixer_find_selem(h, selem);

	if (elem == nil) {
		snd_mixer_selem_id_free(selem);
		snd_mixer_free(h);
		snd_mixer_detach(h, SNDCARD);
		snd_mixer_close(h);
		fprintf(stderr, "Failed to get volume from %s\n", SNDCARD);
		return EXIT_FAILURE;
	}

	snd_mixer_handle_events(h);
	snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
	snd_mixer_selem_get_playback_volume(elem, 0, &vol);

	snd_mixer_selem_id_free(selem);
	snd_mixer_free(h);
	snd_mixer_detach(h, SNDCARD);
	snd_mixer_close(h);

	printf("%ld%%\n", (vol * 100) / max);

	return EXIT_SUCCESS;
}
