#include <opencv2\opencv.hpp>

void info();
void MyFastestMeanFilter (IplImage *src, IplImage *dst, int k);

int main()
{
	IplImage *src, *dst;

	info(); // 시작 정보 출력
	
	// 경로 입력
	char path[1000] = {'\0'};

	while (true)
	{
		for (int i = 0; path[i] != '\0'; i++)
		  path[i] = '\0';

		printf("Input File Path: ");
		scanf("%s", path);

		src = cvLoadImage(path);
		if (src == NULL)
		{
			printf("Wrong File Path!\n");
			continue;
		}
		else
			break;
	}

	CvSize size = cvGetSize(src);
	dst = cvCreateImage(size, 8, 3);

	// k에 따라 함수 실행
	while (true)
	{
		int k;

		printf("Input Kernel Size K: ");
		scanf("%d", &k);

		if ((k > 0) && (k <= (size.height-1)/2) && (k <= (size.width-1)/2))
		{
			MyFastestMeanFilter (src, dst, k);

			cvShowImage("src", src);
			cvShowImage("dst", dst);
			cvWaitKey();

			continue;
		}

		else if ((k > (size.height-1)/2) || (k > (size.width-1)/2))
		{
			printf("Wrong Number!\n");

			continue;
		}

		else
			return -1;
	}


	return 0;
}

void info()
{
	printf("==================================================\n");
	printf("Dept. of Digital Contents, Sejong University\n");
	printf("Multimedia Programming Class\n");
	printf("Homework #3: Fast Mean Filter\n");
	printf("==================================================\n");
}

void MyFastestMeanFilter (IplImage *src, IplImage *dst, int k)
{
	CvSize size = cvGetSize(src);

	// 2차원 배열 동적 할당
	CvScalar ** sum = new CvScalar*[size.height];

	for (int i = 0; i < size.height; i++)
		sum[i] = new CvScalar[size.width];

	// Summed Area Table
	for (int y = 0; y < size.height; y++)
		for (int x = 0; x < size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			if ((x == 0) && (y == 0)) // (0, 0)의 색깔
			{
				sum[y][x].val[0] = f.val[0];
				sum[y][x].val[1] = f.val[1];
				sum[y][x].val[2] = f.val[2];
			}
			else if (y == 0) // 가로 누적
			{
				sum[y][x].val[0] = f.val[0] + sum[y][x-1].val[0];
				sum[y][x].val[1] = f.val[1] + sum[y][x-1].val[1];
				sum[y][x].val[2] = f.val[2] + sum[y][x-1].val[2];
			}
			else if (x == 0) // 세로 누적
			{
				sum[y][x].val[0] = f.val[0] + sum[y-1][x].val[0];
				sum[y][x].val[1] = f.val[1] + sum[y-1][x].val[1];
				sum[y][x].val[2] = f.val[2] + sum[y-1][x].val[2];
			}
			else // 나머지 값 누적
			{
				sum[y][x].val[0] = f.val[0] + sum[y][x-1].val[0] + sum[y-1][x].val[0] - sum[y-1][x-1].val[0];
				sum[y][x].val[1] = f.val[1] + sum[y][x-1].val[1] + sum[y-1][x].val[1] - sum[y-1][x-1].val[1];
				sum[y][x].val[2] = f.val[2] + sum[y][x-1].val[2] + sum[y-1][x].val[2] - sum[y-1][x-1].val[2];
			}
		}

		for (int y = k+1; y < size.height-k; y++)
			for (int x = k+1; x < size.width-k; x++)
			{	
				int Kernel = ((2*k)+1)*((2*k)+1); // Kernel의 한 변의 크기 : 2k+1
				CvScalar g = cvScalar(0, 0, 0); 
				g.val[0] = (sum[y+k][x+k].val[0] - sum[y+k][x-(k+1)].val[0] - sum[y-(k+1)][x+k].val[0] + sum[y-(k+1)][x-(k+1)].val[0]) / Kernel;
				g.val[1] = (sum[y+k][x+k].val[1] - sum[y+k][x-(k+1)].val[1] - sum[y-(k+1)][x+k].val[1] + sum[y-(k+1)][x-(k+1)].val[1]) / Kernel;
				g.val[2] = (sum[y+k][x+k].val[2] - sum[y+k][x-(k+1)].val[2] - sum[y-(k+1)][x+k].val[2] + sum[y-(k+1)][x-(k+1)].val[2]) / Kernel;
				
				cvSet2D(dst, y, x, g); 
			}

	// 동적 할당 해제
	for (int i = 0; i < size.height; i++)
		delete sum[i];
	delete sum;
}
