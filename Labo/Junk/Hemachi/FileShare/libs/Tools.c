#include "all.h"

void SortFilesByStamp(autoList_t *files) // files: 要素を再配置することに注意
{
	char *file;
	uint index;

	foreach (files, file, index)
	{
		updateFindData(file);
		setElement(files, index, (uint)xcout("%020I64d%s", lastFindData.time_write, file));
		memFree(file);
	}
	sortJLinesICase(files);

	foreach (files, file, index)
	{
		copyLine(file, file + 20);
	}
}
