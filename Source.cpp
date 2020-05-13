/*** 2014707040 유진혁 ***/
#include <iostream>
using namespace std;

int n;	// 배열 크기
bool** input;	// 입력 배열
bool** output;	// 출력 배열 (누를 스위치)
bool* check;	// 누르는 스위치 수 최소화를 위해
bool isSolved = false;	// 솔루션 유무
int minCount;	// 누르는 스위치 수 최솟값

/*** 스위치 켜기/끄기 ***/
void Switch(int index)
{
	int i = index / n;	// 행
	int j = index % n;	// 열

	input[i][j] = !input[i][j];
	if (i - 1 >= 0)
		input[i - 1][j] = !input[i - 1][j];
	if (i + 1 < n)
		input[i + 1][j] = !input[i + 1][j];
	if (j - 1 >= 0)
		input[i][j - 1] = !input[i][j - 1];
	if (j + 1 < n)
		input[i][j + 1] = !input[i][j + 1];
}

/*** 윗 칸의 불이 꺼져있으면 Promising ***/
bool Promising(int index)
{
	if (index == -1)	// 루트 노드
		return true;

	int i = index / n;	// 행
	int j = index % n;	// 열

	if (i == 0 || input[i - 1][j] == false)
		return true;
	else
		return false;
}

/*** 모든 칸의 불이 꺼져 있으면 문제 해결 ***/
bool Solve()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (input[i][j] == true)
				return false;
		}
	return true;
}

/*** 모든 칸의 불을 끄는 함수 ***/
void TurnOff(int index)
{
	int count = 0;

	if (Promising(index))
	{
		if (Solve() == false)
		{
			if (index + 1 < n * n)
			{
				// 스위치 눌렀을 때
				check[index + 1] = true;
				Switch(index + 1);
				TurnOff(index + 1);

				// 스위치 누르지 않았을 때
				check[index + 1] = false;
				Switch(index + 1);
				TurnOff(index + 1);
			}
		}
		else
		{
			isSolved = true;
			for (int i = 0; i < n * n; i++)
				if (check[i] == true)
					count++;
			if (minCount > count)
			{
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						output[i][j] = check[i*n + j];
				minCount = count;
			}
		}
	}
}


int main()
{
	char ch;

	/*** 입력 및 할당 ***/
	cin >> n;
	input = new bool*[n];
	output = new bool*[n];
	minCount = n*n;
	for (int i = 0; i < n; i++)
	{
		input[i] = new bool[n];
		output[i] = new bool[n];
	}
	check = new bool[n * n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> ch;
			if (ch == 'O')
				input[i][j] = true;
			else if (ch == '#')
				input[i][j] = false;
		}

	TurnOff(-1);

	cout << endl;

	/*** 출력 ***/
	if (isSolved)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (output[i][j] == true)
					cout << "O ";
				else
					cout << "# ";
			}
			cout << endl;
		}
	}
	else
		cout << "no solution.\n";

	/*** 메모리 해제 ***/
	for (int i = 0; i < n; i++)
	{
		delete[] input[i];
		delete[] output[i];
	}

	delete[] input;
	delete[] output;
	delete[] check;

	return 0;
}