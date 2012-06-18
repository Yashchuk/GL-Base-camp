/*
 * Create a function that computes dot product of two vectors. 
 * Using this function determine two lines of matrix, dot product of which is the greatest. 
 * Swap these lines and print the resulting matrix.
 */

#include <iostream>

using namespace std;

/**
  * @brief	Function calculates dot(scalar) product of two vectors represented as float arrays
  * @param	[in]    vec1 Pointer to first vector
  * @param	[in]    vec2 Pointer to second vector
  * @param	[in]    vecSize Size of both vectors
  * @return	Dot(scalar) product
  */
float dotProduct(float *vec1, float *vec2, unsigned vecSize);

/**
  * @brief	Function swaps two rows with the greatest dot product
  * @param	[in,out]    matrix Matrix as 2d float array
  * @param	[in]		rows Number of rows in matrix
  * @param	[in]		columns Number of columns in matrix
  * @return	void
  */
void swapRowsWithGreatestDotProduct(float **matrix, unsigned rows, unsigned columns);

int main()
{
	unsigned rows, columns;

	cout << "Enter number of rows and columns in matrix:" << endl;
	cin >> rows >> columns;

	float **matrix = new float*[rows];
	for(unsigned i = 0; i < rows; i++)
	{
		matrix[i] = new float[columns];

		cout << "Enter " << i + 1 << " row" << endl;
		for(unsigned j = 0; j < columns; j++)
			cin >> matrix[i][j];

	}

	swapRowsWithGreatestDotProduct(matrix, rows, columns);

	cout << "Resulting matrix:" << endl;
	for(unsigned i = 0; i < rows; i++)
	{
		for(unsigned j = 0; j < columns; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}

	for(unsigned i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}

float dotProduct(float *vec1, float *vec2, unsigned vecSize)
{
	if(!vec1 || !vec2)
		return 0.0f;

	float result = 0.0f;

	for(unsigned i = 0; i < vecSize; i++)
	{
		result += vec1[i] * vec2[i];
	}

	return result;
}

void swapRowsWithGreatestDotProduct(float **matrix, unsigned rows, unsigned columns)
{
	if(!matrix || !columns || !rows)
		return;

	float max = 0.0f;
	unsigned row1 = 0, row2 = 0;

	// Find max dot product and fix row positions
	for(unsigned i = 0; i < rows - 1; i++)
	{
		for(unsigned j = i + 1; j < rows; j++)
		{
			float dot = dotProduct(matrix[i], matrix[j], columns);

			if(dot > max)
			{
				max = dot;
				row1 = i;
				row2 = j;
			}
		}
	}

	// Print values
	cout << "Rows with the greatest dot product are:" << endl;
	cout << row1 + 1 << ": ( ";
	for(unsigned i = 0; i < columns; i++)
		cout << matrix[row1][i] << " ";
	cout << ")" << endl;

	cout << row2 + 1 << ": ( ";
	for(unsigned i = 0; i < columns; i++)
		cout << matrix[row2][i] << " ";
	cout << ")" << endl;

	// Swap rows
	for(unsigned i = 0; i < columns; i++)
	{
		float temp = matrix[row2][i];
		matrix[row2][i] = matrix[row1][i];
		matrix[row1][i] = temp;
	}
}