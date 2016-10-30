#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>



#ifndef W
// #define W 1440
// #define H 900

#define W 296
#define H 413

#endif

typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
}RGB;

int mzk(RGB (*buf)[W], int width_x, int height_y, int len)
{
	RGB color = {.R = 0xff};//buf[height_y][width_x];

	int i,j;
	for (i = 0; i < H; ++i)
	{
		for (j = 0; j < W; ++j)
		{
			if ((i >= height_y && i <= height_y + len)
				&&
				(j >= width_x && j <= width_x + len))
			{
				buf[i][j] = color;
			}
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{

	if(2 != argc)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return -1;
	}

	//open source
	int fds = open(argv[1], O_RDONLY);
	if(-1 == fds)
	{
		perror("open src file");
		return -1;
	}

	//create new file
	char destfile[20] = {0};
	strcat(strcat(destfile, "mzk."), argv[1]);
	int fdd = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(-1 == fdd)
	{
		perror("open des file");
		return -1;
	}

	//copy BMP head
	char header[54];
	read(fds, header, sizeof header);
	write(fdd, header, sizeof header);

//read src
	RGB buf[H][W];
//	lseek(fds, 54, SEEK_SET);
	int ret;
	ret = read(fds, buf, sizeof buf);

	mzk(buf, 50, 50, 100);

	write(fdd, buf, ret);


	//close src & new
	close(fds);
	close(fdd);

	return 0;
}

