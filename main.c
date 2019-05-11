#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include "qwcrtvtz.h"
#include "ebcdic.h"

void
print_RTMZ0100_entry (RTMZ0100_entry *item)
{
	char utf[129];
	ebcdic2utf (item->name, 10, utf);
	printf ("Name: %s\n", utf);
	ebcdic2utf (&item->local_system_time, 1, utf);
	printf ("Local system time: %s\n", utf);
	ebcdic2utf (&item->dst, 1, utf);
	printf ("Daylight savings time: %s\n", utf);
	printf ("UTC offset: %d\n", item->utc_offset);
	ebcdic2utf (item->standard_abbr, 10, utf);
	printf ("Standard abbreviation: %s\n", utf);
	ebcdic2utf (item->standard_name, 50, utf);
	printf ("Standard name: %s\n", utf);
	ebcdic2utf (item->daylight_abbr, 10, utf);
	printf ("Daylight abbreviation: %s\n", utf);
	ebcdic2utf (item->daylight_name, 50, utf);
	printf ("Daylight name: %s\n", utf);
	ebcdic2utf (item->standard_msg, 7, utf);
	printf ("Standard message: %s\n", utf);
	ebcdic2utf (item->daylight_msg, 7, utf);
	printf ("Daylight message: %s\n", utf);
	ebcdic2utf (item->msg_name, 10, utf);
	printf ("Message name: %s\n", utf);
	ebcdic2utf (item->msg_library, 10, utf);
	printf ("Message library: %s\n", utf);
	ebcdic2utf (item->daylight_start_month, 2, utf);
	printf ("DST starting month: %s\n", utf);
	ebcdic2utf (&item->daylight_start_day, 1, utf);
	printf ("DST starting day: %s\n", utf);
	ebcdic2utf (&item->daylight_start_day_of_month, 1, utf);
	printf ("DST starting day of month: %s\n", utf);
	ebcdic2utf (item->daylight_start_time, 6, utf);
	printf ("DST starting time: %s\n", utf);
	ebcdic2utf (item->daylight_end_month, 2, utf);
	printf ("DST ending month: %s\n", utf);
	ebcdic2utf (&item->daylight_end_day, 1, utf);
	printf ("DST endng day: %s\n", utf);
	ebcdic2utf (&item->daylight_end_day_of_month, 1, utf);
	printf ("DST ending day of month: %s\n", utf);
	ebcdic2utf (item->daylight_end_time, 6, utf);
	printf ("DST ending time: %s\n", utf);
	ebcdic2utf (item->description, 50, utf);
	printf ("Description: %s\n", utf);
	printf ("Daylight savings time shift: %d\n", item->daylight_shift);
	printf ("Year offset: %d\n", item->year_offset);
	ebcdic2utf (item->alternative_name, 50, utf);
	printf ("Alternative name: %s\n", utf);
	printf ("----\n");
}

int
main (int argc, char **argv)
{
	char *out = malloc(1000000);
	int outlen = 1000000;
	char format[] = FORMAT_RTMZ0100;
	char name[] = ALL;
	ERRC0100 err = { 0 };
	err.bytes_in = sizeof (err);
	qwcrtvtz((void*)out, &outlen, format, name, &err);
	// write (1, out, outlen);
	RTMZ0100_header *hdr = (RTMZ0100_header*)out;
	for (int i = 0; i < hdr->num_returned; i++) {
		RTMZ0100_entry *item;
		item = (RTMZ0100_entry*)(out + hdr->offset + (hdr->entry_length * i));
		print_RTMZ0100_entry (item);
	}
	return 0;
}
