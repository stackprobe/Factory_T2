/*
	MoveDevOutToHPStore.exe 入力フォルダ 出力フォルダ

	- - -
	実行例

	MoveDevOutToHPStore.exe C:\Dev\Game C:\home\HPStoreT2\Game
*/

#include "C:\Factory\Common\all.h"

int main(int argc, char **argv)
{
	char *rRootDir;
	char *destDir;
	autoList_t *rDirs;
	char *rDir;
	uint index;

	rRootDir = makeFullPath(nextArg());
	destDir  = makeFullPath(nextArg());

	cout("< %s\n", rRootDir);
	cout("> %s\n", destDir);

	errorCase(!existDir(rRootDir));
	errorCase(!existDir(destDir));
	errorCase(!_stricmp(rRootDir, destDir)); // ? 同じフォルダ

	rDirs = slsDirs(rRootDir);

	foreach (rDirs, rDir, index)
	{
		char *outDir = combine(rDir, "out");

		if (existDir(outDir))
		{
			autoList_t *files = slsFiles(outDir);
			char *file;
			uint file_index;

			foreach (files, file, file_index)
			{
				char *destFile = combine(destDir, getLocal(file));

				cout("< %s\n", file);
				cout("> %s\n", destFile);

				removeFileIfExist(destFile);
				moveFile(file, destFile);

				cout("COPY-OK\n");

				memFree(destFile);
			}
			releaseDim(files, 1);
		}
		memFree(outDir);
	}
	releaseDim(rDirs, 1);

	cout("COPY-OK!\n");
}
