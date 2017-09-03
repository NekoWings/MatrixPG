// MatrixPG.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define LEN 10
int MatrixOri[LEN][LEN] = { 0 };//原始矩阵
int MatrixT[LEN][LEN] = { 0 };//变化矩阵
int MatrixFlag[LEN][LEN] = { 0 };//标记矩阵
int T;//阈值
int JUDGE;//选上选下（不考虑相等）

void inMatrix();//读取矩阵文件
void buildMatrix();//创建矩阵文件
void printMatrixOri();//打印矩阵
void printMatrixT();
int selectConditions();//选择区域增长条件

using namespace std;
class point
{
public:
	int x;
	int y;
	point(int a=0, int b=0)
	{
		this->x = a;
		this->y = b;
	}
	void selectSeed()
	{
		cout << "Please input SEED POINT\n"
			<< "x:";
		do {
			cin >> this->x;
		} while ((x > LEN) || (x < 0));

		cout << "y:";
		do {
			cin >> this->y;
		} while ((y > LEN) || (y < 0));

		cout << "seed num:" << MatrixOri[this->x][this->y] << endl;
	}
};

static point connet4s[4] = { point(0,-1),point(-1,0) ,point(0,1) ,point(1,0) };
static point connet8s[8] = { point(-1,-1),point(-1,0),point(-1,1) ,point(0,-1) ,point(0,1),point(1,-1) ,point(1,0) ,point(1,1) };
void setFlag(point p);//标记
int aves4(int tx, int ty);
int aves8(int tx, int ty);
point selectSeed();

int main()
{
	printf("Functions:\n");
	printf("0-----EXIT\n");
	printf("  -----selectSeed()\n");
	printf("  -----selectConditions()\n");
	printf("1-----buildMatrix()\n");
	printf("2-----inMatrix();\n");
	printf("3-----printMatrixOri()\n");

	int sel;
	while (cin >> sel)
	{
		switch (sel)
		{
		case 1:
			buildMatrix();
			break;
		case 2:
			inMatrix();
			break;
		case 3:
			printMatrixOri();
			break;
		default:
			cout << "exit\n" << endl;
			break;
		}
		if (sel == 0)
			break;
	}

	point seed = selectSeed();
	setFlag(seed);
	int condition = selectConditions();

	//BUILD QUEUE
	queue <point> seeds;
	seeds.push(seed);

	//DATE PROCESSING
	switch (condition)
	{
	case 1://阈值增长
		while (!seeds.empty())
		{
			point seed = seeds.front();
			seeds.pop();
			setFlag(seed);

			for (size_t i = 0; i < 4; i++)
			{
				int tx = seed.x + connet4s[i].x;
				int ty = seed.y + connet4s[i].y;

				cout << "(" << tx << "," << ty << ")" << endl;//……………………

				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;
				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					if( (MatrixOri[tx][ty] > T)&& (JUDGE == 0))//Bigger than T
					{
						cout << "(" << tx << "," << ty << ")√num:" << MatrixOri[tx][ty] << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
					if ((MatrixOri[tx][ty] < T)&&(JUDGE==1))//Smaller than T
					{
						cout << "(" << tx << "," << ty << ")√num:" << MatrixOri[tx][ty] << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
				}
			}
		}
		cout << "grow end" << endl;

		printMatrixT(); system("pause");
		break;
	case 2://4邻域增长
		int ave4;
		while (!seeds.empty())
		{
			point seed = seeds.front();
			seeds.pop();
			setFlag(seed);

			for (size_t i = 0; i < 4; i++)
			{
				int tx = seed.x + connet4s[i].x;
				int ty = seed.y + connet4s[i].y;

				cout << "(" << tx << "," << ty << ")" << endl;//……………………

				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;

				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					ave4 = aves4(tx,ty);
					if ((ave4 > T) && (JUDGE == 0))//Bigger than T
					{
						cout << "(" << tx << "," << ty << ")√avenum:" << ave4 << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
					if ((ave4 < T) && (JUDGE == 1))//Smaller than T
					{
						cout << "(" << tx << "," << ty << ")√avenum:" << ave4 << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
				}
			}
		}
		cout << "grow end" << endl;
		printMatrixT(); system("pause");
		break;
	case 3://8邻域增长
		int ave8;
		while (!seeds.empty())
		{
			point seed = seeds.front();
			seeds.pop();
			setFlag(seed);

			for (size_t i = 0; i < 4; i++)
			{
				int tx = seed.x + connet4s[i].x;
				int ty = seed.y + connet4s[i].y;

				cout << "(" << tx << "," << ty << ")" << endl;//……………………

				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;

				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					ave8 = aves8(tx, ty);
					if ((ave8 > T) && (JUDGE == 0))//Bigger than T
					{
						cout << "(" << tx << "," << ty << ")√avenum:" << ave8 << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
					if ((ave8 < T) && (JUDGE == 1))//Smaller than T
					{
						cout << "(" << tx << "," << ty << ")√avenum:" << ave8 << endl;//……………………
						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue
						printMatrixT(); system("pause");//……………………
					}
				}
			}
		}
		cout << "grow end" << endl;
		printMatrixT(); system("pause");
		break;
	default:
		break;
	}
	//nuclear code
	//stack<point> seeds;
	system("pause");
    return 0;
}

void inMatrix()
{
	FILE *fp;
	char filename[20];

	cout << "Please input Original Matrix file name:";
	cin >> filename;

	errno_t err;

	while ((err = fopen_s(&fp, filename, "r") != 0))
	{
		cout << "- - - - - - - - - - - OPEN FAILED - - - - - - - - - - -\n"
			<< "Are u choose the wrong file?\n\n" << endl;

		cout << "Input again:";
		cin >> filename;
	}

	while (!feof(fp))
	{
		for (int i = 0; i < LEN; i++)
			for (int j = 0; j < LEN; j++)
				fscanf_s(fp, "%d", &MatrixOri[i][j], sizeof(int));
	}
	rewind(fp);

	/*while (!feof(fp))
	{
		for (int i = 0; i < LEN; i++)
			for (int j = 0; j < LEN; j++)
				fscanf_s(fp, "%d", &MatrixT[i][j], sizeof(int));
	}*/

	fclose(fp);
}
void buildMatrix()
{
	FILE *fp;
	char filename[20];

	cout << "Please input the filename that u want to build:";
	cin >> filename;

	errno_t err;

	while ((err = fopen_s(&fp, filename, "wb") != 0))
	{
		cout << "- - - - - - - - - - - BUILD FAILED - - - - - - - - - - -\n"
			<< "Are u tupe wrong filename?\n\n" << endl;

		cout << "Input again:";
		cin >> filename;
	}

	srand((unsigned)time(NULL));

	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			int t;
			t = rand() % 100 + 0;

			fprintf(fp, "%d \t", t);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	cout << "- - - - - - - - - - - - BUILD COMPLETE - - - - - - - - - - - -" << endl;
}
void printMatrixOri()
{
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			cout << setw(4) << MatrixOri[i][j];
		}
		cout << "\n";
	}		
}
void printMatrixT()
{
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			cout << MatrixT[i][j] << " ";
		}
		cout << "\n";
	}
}
point selectSeed()
{
	point seed;
	seed.selectSeed();
	cout << "SELECT COMPLETE" << endl;
	return seed;
}
void setFlag(point p)
{
	int x = p.x;
	int y = p.y;
	MatrixFlag[x][y] = 1;
}
int selectConditions()
{
	cout << "Please choose the growth conditions" << endl;
	printf("1-----阈值增长\n");
	printf("2-----4邻域平均值\n");
	printf("3-----8邻域平均值\n\n");

	int t=0,t2=0;
	while (cin >> t)
	{
		switch (t)
		{
		case 1:
			cout << "阈值增长\n" << endl;
			cout << "请输入阈值T：";
			cin >> T;
			cout << "若大于阈值T增长请扣0\n若大于阈值T增长请扣1\n";
			while (cin >> t2)
			{
				switch (t2)
				{
				case 0:
					JUDGE = 0;
					return 1;
					break;
				case 1:
					JUDGE = 1;
					return 1;
					break;
				default:
					cout << "error input" << endl;
					break;
				}
			}
			break;
		case 2:
			cout << "4邻域平均值\n" << endl;
			cout << "请输入阈值T：";
			cin >> T;
			cout << "若大于阈值T增长请扣0\n若大于阈值T增长请扣1\n";
			while (cin >> t2)
			{
				switch (t2)
				{
				case 0:
					JUDGE = 0;
					return 2;
					break;
				case 1:
					JUDGE = 1;
					return 2;
					break;
				default:
					cout << "error input" << endl;
					break;
				}
			}
			break;
		case 3:
			cout << "8邻域平均值\n" << endl;

			cout << "请输入阈值T：";
			cin >> T;
			cout << "若大于阈值T增长请扣0\n若大于阈值T增长请扣1\n";
			while (cin >> t2)
			{
				switch (t2)
				{
				case 0:
					JUDGE = 0;
					return 3;
					break;
				case 1:
					JUDGE = 1;
					return 3;
					break;
				default:
					cout << "error input" << endl;
					break;
				}
			}
			break;
		}
	}
}
int aves4(int tx, int ty)
{
	int ave=0;
	double sum = 0;
	double num = 4;
	for (size_t i = 0; i < 4; i++)
	{
		int x = tx + connet4s[i].x;
		int y = ty + connet4s[i].y;
		
		if (x<0 || y<0 || x>LEN || y>LEN)
		{
			num--;
			continue;
		}
		sum = sum + MatrixOri[x][y];
	}
	ave = (int)(sum / num - 0.5);
	//cout << ave << endl; system("pause");
	return ave;
}
int aves8(int tx, int ty)
{
	int ave = 0;
	double sum = 0;
	double num = 8;
	for (size_t i = 0; i < 8; i++)
	{
		int x = tx + connet8s[i].x;
		int y = ty + connet8s[i].y;

		if (x<0 || y<0 || x>LEN || y>LEN)
		{
			num--;
			continue;
		}
		sum = sum + MatrixOri[x][y];
	}
	ave = (int)(sum / num - 0.5);
	//cout << ave << endl; system("pause");
	return ave;
}