// MatrixPG.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define LEN 10
#define LEN2 44
int MatrixOri[LEN][LEN] = { 0 };//ԭʼ����
int MatrixT[LEN][LEN] = { 0 };//�仯����
int MatrixFlag[LEN][LEN] = { 0 };//��Ǿ���
int T;//��ֵ
int JUDGE;//ѡ��ѡ�£���������ȣ�
int PO=1;//printOptions
			//��ӡ����

void setTable(int n);
void problemDescript();// Set Problem
void functionDescript();// Set Function
void readinMatrix();//��ȡ�����ļ�
void createMatrix();//���������ļ�
void printMatrixOri();//��ӡԭʼ����
void printMatrixT();//��ӡ�仯����
int selectConditions();//ѡ��������������

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

static point connet4s[4] = { point(0,-1),point(-1,0) ,point(0,1) ,point(1,0) };//4�������
static point connet8s[8] = { point(-1,-1),point(-1,0),point(-1,1) ,point(0,-1) ,point(0,1),point(1,-1) ,point(1,0) ,point(1,1) };//8�������
void setFlag(point p);//���
int printOptions();//��ӡ����
int aves4(int tx, int ty);//4�����ֵ
int aves8(int tx, int ty);//8�����ֵ
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
	cout << "ѡ������";
	setTable(LEN2 / 2 - 2);
	cout << endl;
	point seed = selectSeed();
	setFlag(seed);
	int condition = selectConditions();

	setTable(LEN2 / 2 - 3);
	cout << "Grow START";
	setTable(LEN2 / 2 - 2);
	cout << endl;

	PO = printOptions();//��ӡ����

	//BUILD QUEUE (BFS)
	queue <point> seeds;
	seeds.push(seed);

	//DATE PROCESSING
	switch (condition)
	{
	case 1://��ֵ����
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
						cout << "||Grow:	(" << tx << "," << ty << ")�� num:" << MatrixOri[tx][ty] << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if (PO == 3)system("pause");//PO3
					}
					if ((MatrixOri[tx][ty] < T)&&(JUDGE==1))//Smaller than T
					{
						if(PO!=1)//Process Output
						cout << "(" << tx << "," << ty << ")��num:" << MatrixOri[tx][ty] << endl;//PO2

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
		cout << "�������";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /�Ա�/ / / / /" << endl;
		printMatrixOri(); system("pause");
		break;
	case 2://4��������
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
						cout << "||Grow:	(" << tx << "," << ty << ")�� avenum:" << ave4 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
					if ((ave4 < T) && (JUDGE == 1))//Smaller than T
					{
						if(PO!=1)//Process Output
						cout << "||Grow:	(" << tx << "," << ty << ")�� avenum:" << ave4 << endl;//PO2

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
		cout << "�������";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /�Ա�/ / / / /" << endl;
		printMatrixOri(); system("pause");
		break;
	case 3://8��������
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
						cout << "||Grow:	(" << tx << "," << ty << ")�� avenum:" << ave8 << endl;//PO2

						MatrixT[tx][ty] = 1;//grow
						MatrixFlag[tx][ty] = 1;//Setflag
						seeds.push(point(tx, ty));//seed into queue

						if (PO != 1)printMatrixT();
						if(PO==3)system("pause");//PO3
					}
					if ((ave8 < T) && (JUDGE == 1))//Smaller than T
					{
						if (PO != 1)
						cout << "||Grow:	(" << tx << "," << ty << ")�� avenum:" << ave8 << endl;//PO2

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
		cout << "�������";
		setTable(LEN2 / 2 - 2);
		cout << endl;
		printMatrixT(); system("pause");
		cout << endl;
		cout << "/ / / / /�Ա�/ / / / /" << endl;
		printMatrixOri(); system("pause");
		break;

	default:
		break;
	}
	//nuclear code
	//stack<point> seeds;
	setTable(LEN2 / 2 - 2);
	cout << "�������";
	setTable(LEN2 / 2 - 2);
	cout << endl;
	system("pause");
    return 0;
}

//������������
void problemDescript()
{
	setTable(LEN2);
	cout << endl;

	cout << "||" << "������Ŀ���������������������" << setw(51) << "||\n"
		<< "||" << "    ���ļ�����һ������󣬴Ӽ��̶���M��N�ھ�����ѡ��һ�����ӵ㣬Ȼ��ѡ��������������||\n"
		<< "||" << "���������ӵ�4�������е��������������������������������������������򣬿���ȫ��0, ||\n"
		<< "||" << "1 �ľ����ʾ��0��ʾ���Ǹ�����1��ʾ�Ǹ�����Ҳ�ɲ���ͼ�ν����������������Ľ����  ||" << endl;

	setTable(LEN2);
	cout << "\n\n" << endl;
}

//������������
void functionDescript()
{
	setTable(LEN2 / 2 - 3);
	printf("Functions:");
	setTable(LEN2 / 2 - 3);
	cout << " -" << endl;
	printf("||	�� Create Matrix File							      ||\n");
	printf("||	�� Read Matrix File						              ||\n");
	printf("||	�� Print Matrix							              ||\n");
	printf("||	�� Select Conditions							      ||\n");
	setTable(LEN2);
	cout << "\n||Your Selection:";
}//

//�����ļ���������
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

//�����ļ���ȡ����
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

//��ӡԭʼ����
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

//��ӡ�仯����
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

//ѡ����������
int selectConditions()
{
	cout << "||Please choose the growth conditions" << endl;
	printf("||	�� ��ֵ����\n");
	printf("||	�� 4����ƽ��ֵ\n");
	printf("||	�� 8����ƽ��ֵ\n");
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
			cout << "��ֵ����";
			setTable(LEN2 / 2 - 2);

			cout << "\n||��������ֵT��";
			cin >> T;

			cout << "/ / / / /��������ֵT�������0/ / / / /\n/ / / / /��������ֵT�������1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /��ֵ������ֵ" << T << "ʱ����/ / / / /" << endl;
					JUDGE = 0;
					return 1;
					break;
				case '1':
					cout << "/ / / / /��ֵС����ֵ" << T << "ʱ����/ / / / /" << endl;
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
			cout << "4����ƽ��ֵ";
			setTable(LEN2 / 2 - 3);

			cout << "\n||��������ֵT��";
			cin >> T;

			cout << "/ / / / /��������ֵT�������0/ / / / /\n/ / / / /��������ֵT�������1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /4����ƽ��ֵ������ֵ" << T << "ʱ����/ / / / /" << endl;
					JUDGE = 0;
					return 2;
					break;
				case '1':
					cout << "/ / / / /4����ƽ��ֵС����ֵ" << T << "ʱ����/ / / / /" << endl;
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
			cout << "8����ƽ��ֵ";
			setTable(LEN2 / 2 - 3);

			cout << "\n||��������ֵT��";
			cin >> T;

			cout << "/ / / / /��������ֵT�������0/ / / / /\n/ / / / /��������ֵT�������1/ / / / /\n\n";
			while (t2 = getch())
			{
				switch (t2)
				{
				case '0':
					cout << "/ / / / /8����ƽ��ֵ������ֵ" << T << "ʱ����/ / / / /" << endl;
					JUDGE = 0;
					return 3;
					break;
				case '1':
					cout << "/ / / / /8����ƽ��ֵС����ֵ" << T << "ʱ����/ / / / /" << endl;
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

//ѡ���ʼ���ӵ�
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

//��Ǻ���
void setFlag(point p)
{
	int x = p.x;
	int y = p.y;
	MatrixFlag[x][y] = 1;
}

//4�����ֵ
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

//8�����ֵ
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

//���ߺ���
void setTable(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << setw(2) << " -";
	}
}

//��ӡ���ú���
int printOptions()
{
	setTable(LEN2 / 2 - 2);
	cout << "��ӡ����";
	setTable(LEN2 / 2 - 2);

	cout << endl;
	cout << "||	�� Only Result								      ||\n";//8.6
	cout << "||	�� Automatic process and result						      ||\n";//6.6
	cout << "||	�� Manually process and result						      ||\n";//6.6
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