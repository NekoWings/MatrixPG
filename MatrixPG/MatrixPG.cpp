// MatrixPG.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define LEN 10
#define LEN2 44
int MatrixOri[LEN][LEN] = { 0 };//原始矩阵
int MatrixT[LEN][LEN] = { 0 };//变化矩阵
int MatrixFlag[LEN][LEN] = { 0 };//标记矩阵
int T;//阈值
int JUDGE;//选上选下（不考虑相等）
int PO=1;//printOptions
			//打印设置

void setTable(int n);
void problemDescript();// Set Problem
void functionDescript();// Set Function
void readinMatrix();//读取矩阵文件
void createMatrix();//创建矩阵文件
void printMatrixOri();//打印原始矩阵
void printMatrixT();//打印变化矩阵
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
		cout << "||Please input SEED POINT\n\n"
			<< "||x:";
		do {
			cin >> this->x;
		} while ((x > LEN) || (x < 0));

		cout << "||y:";
		do {
			cin >> this->y;
		} while ((y > LEN) || (y < 0));

		cout << "/ / / / /Seed Num is:" << MatrixOri[this->x][this->y] << endl;
	}
};

static point connet4s[4] = { point(0,-1),point(-1,0) ,point(0,1) ,point(1,0) };//4邻域遍历
static point connet8s[8] = { point(-1,-1),point(-1,0),point(-1,1) ,point(0,-1) ,point(0,1),point(1,-1) ,point(1,0) ,point(1,1) };//8邻域遍历
void setFlag(point p);//标记
int printOptions();//打印设置
int aves4(int tx, int ty);//4邻域均值
int aves8(int tx, int ty);//8邻域均值
point selectSeed();

int main()
{
	problemDescript();
	functionDescript();
	
	int sel;
	while (cin >> sel)
	{
		switch (sel)
		{
		case 1:
			createMatrix();
			cout << endl;
			functionDescript();
			break;
		case 2:
			readinMatrix();
			cout << endl;
			functionDescript();
			break;
		case 3:
			printMatrixOri();
			cout << endl;
			functionDescript();
			break;
		default:
			cout << "/ / / / /EXIT/ / / / /\n" << endl;
			break;
		}
		if (sel == 4)
			break;
	}

	setTable(LEN2 / 2 - 2);
	cout << "选择种子";
	setTable(LEN2 / 2 - 2);
	cout << endl;
	point seed = selectSeed();
	setFlag(seed);
	int condition = selectConditions();

	setTable(LEN2 / 2 - 3);
	cout << "Grow START";
	setTable(LEN2 / 2 - 2);
	cout << endl;

	PO = printOptions();//打印设置

	//BUILD QUEUE (BFS)
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
				
				if(PO!=1)//Process Output
				cout << "||Point now:	(" << tx << "," << ty << ") " << MatrixOri[tx][ty] << endl;//PO2

				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;
				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					if( (MatrixOri[tx][ty] > T)&& (JUDGE == 0))//Bigger than T
					{
						if(PO!=1)//Process Output
						cout << "||Grow:	(" << tx << "," << ty << ")√ num:" << MatrixOri[tx][ty] << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if (PO == 3)system("pause");//PO3
					}
					if ((MatrixOri[tx][ty] < T)&&(JUDGE==1))//Smaller than T
					{
						if(PO!=1)//Process Output
						cout << "(" << tx << "," << ty << ")√num:" << MatrixOri[tx][ty] << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if (PO == 3)system("pause");//PO3
					}
				}
			}
		}
		setTable(LEN2 / 2 - 2);
		cout << "Grow END";
		setTable(LEN2 / 2 - 2);
		cout <<"\n"<< endl;

		setTable(LEN2 / 2 - 2);
		cout << "生长结果";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /对比/ / / / /" << endl;
		printMatrixOri(); system("pause");
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

				if(PO!=1)//Process Output
				cout << "||Point now: (" << tx << "," << ty << ") " << MatrixOri[tx][ty] << endl;//PO2

				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;

				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					ave4 = aves4(tx,ty);
					if ((ave4 > T) && (JUDGE == 0))//Bigger than T
					{
						if(PO!=1)//Process Output
						cout << "||Grow:	(" << tx << "," << ty << ")√ avenum:" << ave4 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
					if ((ave4 < T) && (JUDGE == 1))//Smaller than T
					{
						if(PO!=1)//Process Output
						cout << "||Grow:	(" << tx << "," << ty << ")√ avenum:" << ave4 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
				}
			}
		}
		setTable(LEN2 / 2 - 2);
		cout << "Grow END";
		setTable(LEN2 / 2 - 2);
		cout << "\n" << endl;

		setTable(LEN2 / 2 - 2);
		cout << "生长结果";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /对比/ / / / /" << endl;
		printMatrixOri(); system("pause");
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

				if(PO!=1)//Process Output
				cout << "||Point now: (" << tx << "," << ty << ") " << MatrixOri[tx][ty] << endl;//PO2


				if (tx<0 || ty<0 || tx>LEN || ty>LEN)
					continue;

				if (MatrixFlag[tx][ty] == 0)//unsigned
				{
					ave8 = aves8(tx, ty);
					if ((ave8 > T) && (JUDGE == 0))//Bigger than T
					{
						if (PO != 1)
						cout << "||Grow:	(" << tx << "," << ty << ")√ avenum:" << ave8 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
					if ((ave8 < T) && (JUDGE == 1))//Smaller than T
					{
						if (PO != 1)
						cout << "||Grow:	(" << tx << "," << ty << ")√ avenum:" << ave8 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//grow
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
				}
			}
		}
		setTable(LEN2 / 2 - 2);
		cout << "Grow END";
		setTable(LEN2 / 2 - 2);
		cout << "\n" << endl;

		setTable(LEN2 / 2 - 2);
		cout << "生长结果";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /对比/ / / / /" << endl;
		printMatrixOri(); system("pause");
		break;

	default:
		break;
	}
	//nuclear code
	//stack<point> seeds;
	setTable(LEN2 / 2 - 2);
	cout << "程序结束";
	setTable(LEN2 / 2 - 2);
	cout << endl;
	system("pause");
    return 0;
}

//问题描述函数
void problemDescript()
{
	setTable(LEN2);
	cout << endl;

	cout << "||" << "课设题目：矩阵区域增长（★★★★★）" << setw(51) << "||\n"
		<< "||" << "    由文件读入一个大矩阵，从键盘读入M，N在矩阵中选择一个种子点，然后选择区域增长的条||\n"
		<< "||" << "件，若种子点4邻域中有点符合增长条件，则进行区域增长，最后输出产生的区域，可用全是0, ||\n"
		<< "||" << "1 的矩阵表示。0表示不是该区域，1表示是该区域。也可采用图形界面输入区域增长的结果。  ||" << endl;

	setTable(LEN2);
	cout << "\n\n" << endl;
}

//功能描述函数
void functionDescript()
{
	setTable(LEN2 / 2 - 3);
	printf("Functions:");
	setTable(LEN2 / 2 - 3);
	cout << " -" << endl;
	printf("||	① Create Matrix File							      ||\n");
	printf("||	② Read Matrix File						              ||\n");
	printf("||	③ Print Matrix							              ||\n");
	printf("||	④ Select Conditions							      ||\n");
	setTable(LEN2);
	cout << "\n||Your Selection:";
}//

//矩阵文件创建函数
void createMatrix()
{
	FILE *fp;
	char filename[20];

	cout << "||Please input the filename that u want to build:";
	cin >> filename;

	errno_t err;

	while ((err = fopen_s(&fp, filename, "wb") != 0))
	{
		setTable(LEN2 / 2 - 4);
		cout << "BUILD FAILED";
		setTable(LEN2 / 2 - 4);
		cout << " -" << endl;
		cout << "\n/ / / / /Are u tupe wrong filename?/ / / / /\n\n" << endl;

		cout << "||Input again:";
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

	cout << endl;
	setTable(LEN2 / 2 - 4);
	cout << "BUILD COMPLETE";
	setTable(LEN2 / 2 - 4);
	cout << " -" << endl;
}

//矩阵文件读取函数
void readinMatrix()
{
	FILE *fp;
	char filename[20];

	cout << "||Please input Original Matrix file name:";
	cin >> filename;

	errno_t err;

	while ((err = fopen_s(&fp, filename, "r") != 0))
	{
		setTable(LEN2 / 2 - 4);
		cout << "BUILD FAILED";
		setTable(LEN2 / 2 - 4);
		cout << endl;
		cout << "\n/ / / / /Are u choose the wrong file?/ / / / /\n\n" << endl;

		cout << "||Input again:";
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

	cout << endl;
	setTable(LEN2 / 2 - 4);
	cout << "READ COMPLETE";
	setTable(LEN2 / 2 - 4);
	cout  << endl;
	cout << "||Print or not (Y/N)?";
	char temp;
	temp = getch();
	if ((temp == 'Y')|| (temp == 'y'))
	{
		cout << endl;
		printMatrixOri();
	}
	else if ((temp == 'N') || (temp == 'n'))
		cout << endl;
	else
		cout << "/ / / / /Wrong input/ / / / /" << endl;

}

//打印原始矩阵
void printMatrixOri()
{
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			if (MatrixT[i][j] == 1)
			{
				cout << setw(3) << MatrixOri[i][j] << "+";
				continue;
			}
			cout << setw(3) << MatrixOri[i][j]<<" ";
		}
		cout << "\n";
	}		
}

//打印变化矩阵
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

//选择增长条件
int selectConditions()
{
	cout << "||Please choose the growth conditions" << endl;
	printf("||	① 阈值增长\n");
	printf("||	② 4邻域平均值\n");
	printf("||	③ 8邻域平均值\n");
	setTable(LEN2); cout << "\n" << endl;
	cout << "||CHOOSE:";
	int t = 0, t2 = 0;
	while (cin >> t)
	{
		cout << "\n" << endl;
		switch (t)
		{
		case 1:
			setTable(LEN2 / 2 - 2);
			cout << "阈值增长";
			setTable(LEN2 / 2 - 2);

			cout << "\n||请输入阈值T：";
			cin >> T;

			cout << "/ / / / /若大于阈值T增长请扣0/ / / / /\n/ / / / /若大于阈值T增长请扣1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /数值大于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 0;
					return 1;
					break;
				case '1':
					cout << "/ / / / /数值小于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 1;
					return 1;
					break;
				default:
					cout << "/ / / / /error input/ / / / /" << endl;
					break;
				}
			}
			break;
		case 2:
			setTable(LEN2 / 2 - 3);
			cout << "4邻域平均值";
			setTable(LEN2 / 2 - 3);

			cout << "\n||请输入阈值T：";
			cin >> T;

			cout << "/ / / / /若大于阈值T增长请扣0/ / / / /\n/ / / / /若大于阈值T增长请扣1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /4邻域平均值大于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 0;
					return 2;
					break;
				case '1':
					cout << "/ / / / /4邻域平均值小于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 1;
					return 2;
					break;
				default:
					cout << "/ / / / /error input/ / / / /" << endl;
					break;
				}
			}
			break;
		case 3:
			setTable(LEN2 / 2 - 3);
			cout << "8邻域平均值";
			setTable(LEN2 / 2 - 3);

			cout << "\n||请输入阈值T：";
			cin >> T;

			cout << "/ / / / /若大于阈值T增长请扣0/ / / / /\n/ / / / /若大于阈值T增长请扣1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /8邻域平均值大于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 0;
					return 3;
					break;
				case '1':
					cout << "/ / / / /8邻域平均值小于阈值" << T << "时生长/ / / / /" << endl;
					JUDGE = 1;
					return 3;
					break;
				default:
					cout << "/ / / / /error input/ / / / /" << endl;
					break;
				}
			}
			break;
		default:
			cout << "/ / / / /error input/ / / / /" << endl;
			break;
		}
	}
}

//选择初始种子点
point selectSeed()
{
	point seed;
	seed.selectSeed();
	cout << endl;
	setTable(LEN2 / 2 - 4);
	cout << " SELECT COMPLETE";
	setTable(LEN2 / 2 - 4);
	cout << endl;
	return seed;
}

//标记函数
void setFlag(point p)
{
	int x = p.x;
	int y = p.y;
	MatrixFlag[x][y] = 1;
}

//4邻域均值
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

//8邻域均值
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

//划线函数
void setTable(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << setw(2) << " -";
	}
}

//打印设置函数
int printOptions()
{
	setTable(LEN2 / 2 - 2);
	cout << "打印设置";
	setTable(LEN2 / 2 - 2);

	cout << endl;
	cout << "||	① Only Result								      ||\n";//8.6
	cout << "||	② Automatic process and result						      ||\n";//6.6
	cout << "||	③ Manually process and result						      ||\n";//6.6
	setTable(LEN2); cout << endl;
	int t;
	while (1)
	{
		cout << "||CHOOSE:";
		t = getch();
		cout << endl;
		switch (t)
		{
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		default:
			cout << "/ / / / /error input/ / / / /\a" << endl;
			break;
		}
	}
}