/*
	b16128.exe [/L] [/P]

		/L ... 小文字
		/P ... 表示のみ。(エディタを開かない)

	----

	b16128 == Hex(Base-16) 128 chars

	16 P 128 L 2 == 512

	----
	書式

	{BF80-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX-XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX}
	      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	                   32文字                           32文字                           32文字                           32文字

		X ... Hex(Base-16) char
*/

#include "C:\Factory\Common\all.h"
#include "C:\Factory\Common\Options\CRandom.h"

#define BASE16_CHARS "0123456789ABCDEF"

static char *MakeB16128(void)
{
	char *buff = strx("");
	uint index;

	buff = addLine(buff, "{BF80-");

	for (index = 0; index < 128; index++)
	{
		if (index && index % 32 == 0)
			buff = addChar(buff, '-');

		buff = addChar(buff, BASE16_CHARS[(uint)getCryptoRand64Mod(16)]);
	}
	buff = addChar(buff, '}');
	return buff;
}
int main(int argc, char **argv)
{
	char *b16128 = MakeB16128();

	if (argIs("/L"))
		toLowerLine(b16128);

	cout("%s\n", b16128);

	if (!argIs("/P")) // ? not Print only
		viewLine(b16128);

	memFree(b16128);
}
