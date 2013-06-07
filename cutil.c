#include "cutil.h"

/* isblank()がC99なのでその代用 */
int isspacetab(int c)
{
	return c == ' ' || c == '\t';
}
