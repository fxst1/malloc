#include <ftmalloc.h>
#include <string.h>

int		main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

	s1 = malloc(sizeof(char) * 10);
	s2 = malloc(sizeof(char) * 20);
	s3 = malloc(sizeof(char) * 30);

	free(s2);
	s4 = malloc(sizeof(char) * 10);

	s4[0] = 0;
	strcat(s4, "sffiodsjfiodjsfoijdsgoidfjgiojdfgoijfdgiojfdgoijfdiogjfdgiojfdgiojfdiogjfdiogjfdgoijfdgiojfdgiojfdgiojfdgiofdjgiodjfgiojfdgiofdjgiodsfpsdkfpskgpfdkgpodfkgopdfkgopdkfopgkdfopgkdfopgkopdfgkopdfkgopfdkg");

	show_alloc_mem();
	return (0);
	(void)s1;
	(void)s3;
}
