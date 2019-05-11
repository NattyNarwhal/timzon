#include <iconv.h>
#include <string.h>
#include <stdlib.h>

iconv_t e2a;

static void
init_iconv (void)
{
	/* XXX: This should use the system locales for PASE and XPF */
	e2a = iconv_open(ccsidtocs(1208), ccsidtocs(37));
	if (e2a == (iconv_t)(-1)) {
		/* XXX: fail */
	}
}

/*
 * Because EBCDIC strings are usually fixed-length and padded by ASCII, try to
 * cope by copying it to a fixed null-terminated buffer.
 */
size_t
ebcdic2utf (char *ebcdic, int ebcdic_len, char *utf)
{
	size_t inleft, outleft, ret;
	if (e2a == NULL) {
		init_iconv ();
	}
	inleft = outleft = ebcdic_len + 1;
	char *temp;
	temp = malloc(ebcdic_len + 1);
	strncpy(temp, ebcdic, ebcdic_len);
	temp[ebcdic_len] = '\0';
	ret = iconv(e2a, &temp, &inleft, &utf, &outleft);
	free (temp);
	return ret;
}

/*
 * Zoned decimal to integer conversion
 */
int
ztoi (char *zoned, int len)
{
	char *utf = malloc(len + 1);
	ebcdic2utf (zoned, len, utf);
	return atoi (utf);
}
