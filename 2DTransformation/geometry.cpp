#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <GL/glut.h>
#include "geometry.h"

template <> template <> Vec3<int>::Vec3(const Vec3<float>& v) : raw(), x(raw[0]), y(raw[1]), z(raw[2]) {
	x = int(floor(v.x) + .5);
	y = int(floor(v.y) + .5);
	z = int(floor(v.z) + .5);
}

template <> template <> Vec3<float>::Vec3(const Vec3<int>& v) : raw(), x(raw[0]), y(raw[1]), z(raw[2]) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Matrix::Matrix(int r, int c) : m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.f))), rows(r), cols(c) { }

int Matrix::nrows() {
	return rows;
}

int Matrix::ncols() {
	return cols;
}

Matrix Matrix::identity(int dimensions) {
	Matrix E(dimensions, dimensions);
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			E[i][j] = (i == j ? 1.f : 0.f);
		}
	}
	return E;
}

std::vector<float>& Matrix::operator[](const int i) {
	assert(i >= 0 && i < rows);
	return m[i];
}

Matrix Matrix::operator*(const Matrix& a) {
	assert(cols == a.rows);
	Matrix result(rows, a.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			result.m[i][j] = 0.f;
			for (int k = 0; k < cols; k++) {
				result.m[i][j] += m[i][k] * a.m[k][j];
			}
		}
	}
	return result;
}

Vec3f Matrix::operator*(const Vec3f& a)
{
	//Matrix ma(4, 1);
	Matrix ma(3, 1);
	ma[0][0] = a.x;
	ma[1][0] = a.y;
	//ma[2][0] = a.z;
	//ma[3][0] = 1.f;

	//ma[2][0] = a.z;
	ma[2][0] = 1.f;

	Matrix result(rows, ma.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < ma.cols; j++) {
			result.m[i][j] = 0.f;
			for (int k = 0; k < cols; k++) {
				result.m[i][j] += m[i][k] * ma.m[k][j];
			}
		}
	}

	return Vec3f(result[0][0] / result[2][0], result[1][0] / result[2][0], result[2][0] / result[2][0]);
}

Matrix Matrix::transpose() {
	Matrix result(cols, rows);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result[j][i] = m[i][j];
	return result;
}

Matrix Matrix::inverse() {
	assert(rows == cols);
	// augmenting the square matrix with the identity matrix of the same dimensions A => [AI]
	Matrix result(rows, cols * 2);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result[i][j] = m[i][j];
	for (int i = 0; i < rows; i++)
		result[i][i + cols] = 1;
	// first pass
	for (int i = 0; i < rows - 1; i++) {
		// normalize the first row
		for (int j = result.cols - 1; j >= 0; j--)
			result[i][j] /= result[i][i];
		for (int k = i + 1; k < rows; k++) {
			float coeff = result[k][i];
			for (int j = 0; j < result.cols; j++) {
				result[k][j] -= result[i][j] * coeff;
			}
		}
	}
	// normalize the last row
	for (int j = result.cols - 1; j >= rows - 1; j--)
		result[rows - 1][j] /= result[rows - 1][rows - 1];
	// second pass
	for (int i = rows - 1; i > 0; i--) {
		for (int k = i - 1; k >= 0; k--) {
			float coeff = result[k][i];
			for (int j = 0; j < result.cols; j++) {
				result[k][j] -= result[i][j] * coeff;
			}
		}
	}
	// cut the identity matrix back
	Matrix truncate(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			truncate[i][j] = result[i][j + cols];
	return truncate;
}

std::ostream& operator<<(std::ostream& s, Matrix& m) {
	for (int i = 0; i < m.nrows(); i++) {
		for (int j = 0; j < m.ncols(); j++) {
			s << m[i][j];
			if (j < m.ncols() - 1) s << "\t";
		}
		s << "\n";
	}
	return s;
}

void Line(Vec3i v0, Vec3i v1)
{
	int x0 = v0.x;
	int x1 = v1.x;
	int y0 = v0.y;
	int y1 = v1.y;

	glBegin(GL_POINTS);
	// 请在此添加你的代码
	  /********** Begin ********/
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	if (dx > dy) // x方向为步进方向
	{
		if (x0 > x1) //确保x0<x1，这样循环中x=x+1
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		int d = dx - 2 * dy;
		int d1 = 2 * dx - 2 * dy;
		int d2 = -2 * dy;
		int x = x0;
		int y = y0;
		int yIncr = (y1 > y0) ? 1 : -1; // 比较两端点y值大小决定y的增量值
		glVertex2i(x, y);
		//printf("%d, %d\n", x, y);
		for (int x = x0 + 1; x <= x1; x++)
		{
			if (d < 0)
			{
				y = y + yIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2i(x, y);
			//printf("%d, %d\n", x, y);
		}
	}
	else
	{
		if (y0 > y1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		int d = dy - 2 * dx;
		int d1 = 2 * dy - 2 * dx;
		int d2 = -2 * dx;
		int x = x0;
		int y = y0;
		int xIncr = (x1 > x0) ? 1 : -1;
		glVertex2i(x, y);
		//printf("%d, %d\n", x, y);
		for (int y = y0 + 1; y <= y1; y++)
		{
			if (d < 0)
			{
				x = x + xIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2i(x, y);
			//printf("%d, %d\n", x, y);
		}
	}
	glEnd();
}