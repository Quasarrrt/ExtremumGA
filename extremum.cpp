// extremum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <math.h>
using namespace std;
const int GEN = 200;//���������� ���������
void Mutation(double ChildArray[2][GEN]);
void Crossover(double ChildArray[2][GEN], double GenArray[3][GEN], int ParrentIndex[2][GEN]);
int Selection(double forSumStepSelection[GEN], double SumValues);
double SumOfFunctionValues(double GenArray[3][GEN], double SumValues);
double Function(double x, double y)//������� � ������� � ���� ���������
{
	return y * pow(x, (1 / 2)) - 2 * pow(y, 2) - x + 14 * y;//maximum=28
}
void ChoiceParents(double GenArray[3][GEN])//�������� ���������
{
	for (int i = 0; i < GEN; i++) {
		GenArray[0][i] = ((double)((double)rand() / (RAND_MAX + 1.0) > 0.5 ? rand() : -1 * rand()) / RAND_MAX + rand() % 5);
		GenArray[1][i] = ((double)((double)rand() / (RAND_MAX + 1.0) > 0.5 ? rand() : -1 * rand()) / RAND_MAX + rand() % 5);
	}
}
void Sort(double GenArray[3][GEN])//��� �� ��������� ������ ��������� ������
{
	for (int j = 0; j < GEN; j++)
	{
		GenArray[2][j] = Function(GenArray[0][j], GenArray[1][j]);
	}


	for (int i = 0; i < GEN; i++)
	{
		for (int j = 0; j < GEN; j++)
		{
			if (GenArray[2][j] < GenArray[2][i])//�������� <, ������� >
			{
				double tmp = GenArray[0][i];
				GenArray[0][i] = GenArray[0][j];
				GenArray[0][j] = tmp;
				double tmp1 = GenArray[1][i];
				GenArray[1][i] = GenArray[1][j];
				GenArray[1][j] = tmp1;
				double tmp2 = GenArray[2][i];
				GenArray[2][i] = GenArray[2][j];
				GenArray[2][j] = tmp2;
			}
		}
	}
}
//���� � ������, ����� �������� �������, ������ �����, ������ ���������.
void CreateChildren(double forSumStepSelection[GEN], double SumValues, double ChildArray[2][GEN], double GenArray[3][GEN])
{
	int ParrentIndex[2][GEN];
	SumValues = SumOfFunctionValues(GenArray, SumValues);

	for (unsigned i = 0; i < GEN; i++) {
		ParrentIndex[0][i] = (Selection(forSumStepSelection, SumValues));
		ParrentIndex[1][i] = (Selection(forSumStepSelection, SumValues));
		if (ParrentIndex[0][i] == ParrentIndex[1][i]) {
			if ((rand() / (RAND_MAX + 1.0) < 0.5)) {
				if ((rand() / (RAND_MAX + 1.0) < 0.5)) {
					ParrentIndex[0][i] = Selection(forSumStepSelection, SumValues);
				}
				else {
					ParrentIndex[1][i] = Selection(forSumStepSelection, SumValues);
				}
			}
		}
	}

	Crossover(ChildArray, GenArray, ParrentIndex);//���������

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < GEN; j++)
		{
			GenArray[i][j] = ChildArray[i][j];
		}
	}
}
double SumOfFunctionValues(double GenArray[3][GEN], double SumValues)//����� �������� �������
{
	SumValues = 0;
	for (int i = 0; i < GEN; i++)
	{
		SumValues = GenArray[0][i];
	}
	return SumValues;
}
void SumInSteps(double GenArray[3][GEN], double forSumStepSelection[GEN])//����� �����
{
	int inter = 0;
	for (int i = 0; i < GEN; i++) {
		inter += GenArray[2][i];
		forSumStepSelection[i] = inter;
	}
}
int Selection(double forSumStepSelection[GEN], double SumValues)//��� ���������� �������� ������� �������
{
	double randomFitnessToChooseParent = (float)(rand()) / RAND_MAX * (SumValues / 3);
	int firstIndex = 0;
	int lastIndex = GEN - 1;
	int middle = (int)((firstIndex + lastIndex) / 2);
	int parentIndex = INT_MIN;
	do {
		(randomFitnessToChooseParent > forSumStepSelection[middle]) ? firstIndex = middle : lastIndex = middle;
		middle = (int)((firstIndex + lastIndex) / 2);
		if (abs(firstIndex - lastIndex) == 1) {
			parentIndex = lastIndex;
		}
	} while ((parentIndex < 0) && (firstIndex <= lastIndex));
	return parentIndex;
}
void Crossover(double ChildArray[2][GEN], double GenArray[3][GEN], int ParrentIndex[2][GEN])
//������� ����������, ��� � ���������� ���� �� ���������������, ��� � � ������� ����
{
	for (unsigned i = 0; i < GEN; i++) {
		if ((rand() / (RAND_MAX + 1.0)) > 0.6) {
			ChildArray[0][i] = GenArray[0][ParrentIndex[0][i]];
			ChildArray[1][i] = GenArray[1][ParrentIndex[1][i]];
		}
		else {
			if ((rand() / (RAND_MAX + 1.0)) < 0.6) {
				ChildArray[0][i] = GenArray[0][ParrentIndex[0][i]];
				ChildArray[1][i] = GenArray[1][ParrentIndex[1][i]];
			}
			else {
				ChildArray[0][i] = GenArray[0][ParrentIndex[0][i]];
				ChildArray[1][i] = GenArray[1][ParrentIndex[1][i]];
			}
		}
	}
	Mutation(ChildArray);
}

void Mutation(double ChildArray[2][GEN]) {//������� ��� �������
	for (unsigned i = 0; i < GEN; i++) {
		if ((rand() / (RAND_MAX + 1.0)) < 0.6) {
			if ((rand() / (RAND_MAX + 1.0)) < 0.5) {
				ChildArray[0][i] += 0.1;
				ChildArray[1][i] += 0.1;
			}
			else {
				ChildArray[0][i] -= 0.5;
				ChildArray[1][i] -= 0.5;
			}
		}
	}
}

void PrintGen(double GenArray[3][GEN])//������� ���������
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < GEN; j++)
		{
			cout << GenArray[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{
	double GenArray[3][GEN];//������ ��� ����� ���������
	ChoiceParents(GenArray);
	double forSumStepSelection[GEN];//������ ��� �������� ����� ������� � ����� ������������ ��� � ��������
	double SumValues = 0;//��� ������ ����� ���� �������� �������
	double ChildArray[2][GEN];//�������� ����� � �������������� ��������, ������������ � ������� �����
	for (int i = 0; i < 2000; i++)
	{
		Sort(GenArray);//��������� ������
		SumInSteps(GenArray, forSumStepSelection);//������� ��� ��������
		CreateChildren(forSumStepSelection, SumValues, ChildArray, GenArray);//������� ��������
	}
	PrintGen(GenArray);
	double result = GenArray[2][0];
	if (result > 0)//�������� �� ������
	{
		result = trunc(result);
	}
	else
	{
		result = floor(result);
	}
	cout << "Extremum of function z=y*sqrt(x)-2y^2-x+14y=" << result;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
