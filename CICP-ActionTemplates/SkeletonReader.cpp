/* Each row is a joint trajectory. Each column is a frame.
*/
#include "SkeletonReader.h"
#include <iostream>	// std::cout
#include <fstream>	// std::ifstream

#include <strsafe.h>

const unsigned int SkeletonReader::v[] = { 0, 9, 0, 1, 3, 4, 0, 5, 6, 7, 0, 8, 10, 11, 0, 12, 13, 14, 0, 15, 2, 0, 0, 0, 0 };

SkeletonReader::SkeletonReader()
{
	/*for (int i = 0; i < 26; ++i)
	{
	for (int j = 0; j < 45; ++j)
	{
	std::cout << M[i][j] << ' ';
	}
	std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 26; ++i)
	{
	for (int j = 0; j < 15; ++j)
	{
	std::cout << confi[i][j] << ' ';
	}
	std::cout << std::endl;
	}
	std::cout << std::endl;*/
}

SkeletonReader::~SkeletonReader()
{

}

actskeleton SkeletonReader::readSkeleton(const TCHAR* path, size_t numJoints)
{
	double** M;
	bool** confi;

	size_t num_frames = readMotionMatrix(path, numJoints, &M, &confi);
	/*for (int i = 0; i < 26; ++i)
	{
	for (int j = 0; j < 45; ++j)
	{
	std::cout << M[i][j] << ' ';
	}
	std::cout << std::endl;
	}
	std::cout << std::endl;*/
	actskeleton action = matrix2skeleton(M, confi, num_frames);

	deleteMatrix(M);
	deleteMatrix(confi);

	return action;
}

actskeleton SkeletonReader::matrix2skeleton(double** M, bool** confi, size_t num_frames)
{
	actskeleton action;
	posskeleton frame;

	//size_t num_frames = sizeof M[0] / sizeof(double);
	for (unsigned int f = 0; f < num_frames; ++f)
	{
		for (unsigned int j = 0; j < NUM_JOINTS; ++j)
		{
			frame.positions[j].rightleft = M[f][j*NUM_COORD];
			frame.positions[j].updown = M[f][j*NUM_COORD + 1];
			frame.positions[j].fwdbwd = M[f][j*NUM_COORD + 2];

			frame.confidences[j] = confi[f][j];
		}
		action.poses.push_back(frame);
	}

	return action;
}

size_t SkeletonReader::readMotionMatrix(const TCHAR* path, size_t numJoints, double*** M, bool*** confi)
{
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	std::string fullPath;
	std::wstring ws(path);
	std::string pathS(ws.begin(), ws.end());

	// Prepare string for use with FindFile functions.First, copy the string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("*"));

	// Count the number of files in the directory.
	size_t numFiles = 0;
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			numFiles++;
		} while (FindNextFile(hFind, &ffd) != 0);
	}

	double** mix = nullptr;
	bool** cfi = nullptr;
	createMatrixD(&mix, numFiles - 2, numJoints*NUM_COORD);
	createMatrixB(&cfi, numFiles - 2, numJoints);

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return dwError;
	}
	FindNextFile(hFind, &ffd);
	// List all the files in the directory
	for (unsigned int f = 2; f < numFiles; ++f)	// We skip '.' and '..' files
	{
		FindNextFile(hFind, &ffd);
		ws = ffd.cFileName;
		std::string fileS(ws.begin(), ws.end());
		fullPath = pathS + fileS;
		readFrame(fullPath, mix[f - 2], cfi[f - 2]);
	}
	dwError = GetLastError();
	FindClose(hFind);

	(*M) = mix;
	(*confi) = cfi;

	return numFiles - 2;
}

int SkeletonReader::readFrame(std::string fileName, double* M, bool* confi)
{
	double confiJ;
	double threshold = 0.1;

	std::ifstream fileM(fileName);

	if (!fileM.is_open())
	{
		std::cout << "Can't open frame file\n";
		return -1;
	}

	double filler;
	unsigned int numJoints;
	fileM >> filler >> numJoints;

	for (unsigned int j = 0; j < numJoints; ++j)
	{
		if (v[j] != 0)
		{
			fileM >> M[(v[j] - 1)*NUM_COORD] >> M[(v[j] - 1)*NUM_COORD + 1] >> M[(v[j] - 1)*NUM_COORD + 2] >> filler >> filler >> filler >> filler >> confiJ;
			if (confiJ > threshold)
			{
				confi[v[j] - 1] = true;
			}
			else
			{
				confi[v[j] - 1] = false;
			}
		}
		else
		{
			fileM >> filler >> filler >> filler >> filler >> filler >> filler >> filler >> filler;
		}
	}

	return 0;
}

void SkeletonReader::createMatrixD(double*** matrix, size_t N, size_t M)
{
	*matrix = new double*[N];
	for (unsigned int n = 0; n < N; ++n) {
		(*matrix)[n] = new double[M];
	}
}
void SkeletonReader::createMatrixB(bool*** matrix, size_t N, size_t M)
{
	*matrix = new bool*[N];
	for (unsigned int n = 0; n < N; ++n) {
		(*matrix)[n] = new bool[M];
	}
}

void SkeletonReader::deleteMatrix(double** matrix)
{
	size_t rows = sizeof matrix / sizeof matrix[0];
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] matrix[i]; // delete array within matrix
	}
	delete[] matrix;	// delete actual matrix
}
void SkeletonReader::deleteMatrix(bool** matrix)
{
	size_t rows = sizeof matrix / sizeof matrix[0];
	for (unsigned int i = 0; i < rows; i++)
	{
		delete[] matrix[i]; // delete array within matrix
	}
	delete[] matrix;	// delete actual matrix
}
