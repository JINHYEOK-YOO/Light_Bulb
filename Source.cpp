/*** 2014707040 ������ ***/
#include <iostream>
using namespace std;

int n;	// �迭 ũ��
bool** input;	// �Է� �迭
bool** output;	// ��� �迭 (���� ����ġ)
bool* check;	// ������ ����ġ �� �ּ�ȭ�� ����
bool isSolved = false;	// �ַ�� ����
int minCount;	// ������ ����ġ �� �ּڰ�

/*** ����ġ �ѱ�/���� ***/
void Switch(int index)
{
	int i = index / n;	// ��
	int j = index % n;	// ��

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

/*** �� ĭ�� ���� ���������� Promising ***/
bool Promising(int index)
{
	if (index == -1)	// ��Ʈ ���
		return true;

	int i = index / n;	// ��
	int j = index % n;	// ��

	if (i == 0 || input[i - 1][j] == false)
		return true;
	else
		return false;
}

/*** ��� ĭ�� ���� ���� ������ ���� �ذ� ***/
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

/*** ��� ĭ�� ���� ���� �Լ� ***/
void TurnOff(int index)
{
	int count = 0;

	if (Promising(index))
	{
		if (Solve() == false)
		{
			if (index + 1 < n * n)
			{
				// ����ġ ������ ��
				check[index + 1] = true;
				Switch(index + 1);
				TurnOff(index + 1);

				// ����ġ ������ �ʾ��� ��
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

	/*** �Է� �� �Ҵ� ***/
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

	/*** ��� ***/
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

	/*** �޸� ���� ***/
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