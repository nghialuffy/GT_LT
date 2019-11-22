#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#define TRUE 1 
#define FALSE 0 
#define MAXINT 10001
#define FileInt "Input.inp"
#define FileOut "Output.out"
using namespace std;

/*Lưu lại những cạnh đã đi qua x->y*/
typedef struct Edge {
	int x, y;
};

// Biến
int **A;				//Ma trận hai chiều
int n;					//số đỉnh của đồ thị
int *D;					//Đánh dấu các cạnh đã cho vào cây khung
Edge *L;				//Mảng đánh dâu danh sách đỉnh, cạnh đã thêm vào cây khung nhỏ nhất
int Sum = 0;			//Độ dài của cây khung nhỏ nhất.

/*Đọc dữ liệu từ file*/
void NhapFile() {
	ifstream input(FileInt);
	input >> n;
	A = new int*[n];
	for (int i = 0; i < n; i++) {
		A[i] = new int[n];
		for (int j = 0; j < n; j++) {
			input >> A[i][j];
		}
	}

	input.close();
	return;
}

/*Ghi dữ liệu ra file*/
void XuatFile() {
	ofstream output(FileOut);
	if (output.fail()) {
		cout << "Failed to write this file!" << endl;
		return;
	}
	output << "Trong so cua cay khung nho nhat :" << Sum << endl;
	int **res = new int*[n];
	for (int i = 0; i < n; i++) {
		res[i] = new int[n];
		for (int j = 0; j < n; j++) {
			res[i][j] = 0;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		res[L[i].x][L[i].y] = A[L[i].x][L[i].y];
		res[L[i].y][L[i].x] = A[L[i].y][L[i].x];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			output << res[i][j] << " ";
		}
		output << endl;
	}
	for (int i = 0; i < n; i++) {
		delete[] res[i];
	}
	delete[] res;
	output.close();
	return;
}

/*Xóa con trỏ*/
void XoaConTro() {
	for (int i = 0; i < n; i++) {
		delete[] A[i];
	}
	delete[] A;
	delete[] D;
	delete[] L;
	return;
}

/*Thuật toán Kruskal*/
void Kruskal() {
	D = new int[n];
	L = new Edge[n - 1];

	int min, Dem = 0, T = 0, Temp;
	for (int i = 0; i < n; i++)
		D[i] = 0;

	do {
		/*Tìm cạnh nhỏ nhất của đồ thị suy ra hai đỉnh*/
		min = MAXINT;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (A[i][j] > 0 && min > A[i][j] && !(D[i] != 0 && D[i] == D[j])) {
					min = A[i][j];
					L[Dem].x = i;
					L[Dem].y = j;
				}
		/*Tạo ra cây mới*/
		if (D[L[Dem].x] == 0 && D[L[Dem].y] == 0) {
			T++;
			D[L[Dem].x] = D[L[Dem].y] = T;
		}
		/*Đưa đỉnh tương ứng vào cây*/
		if (D[L[Dem].x] == 0 && D[L[Dem].y] != 0)
			D[L[Dem].x] = D[L[Dem].y];
		/*Đưa đỉnh tương ứng vào cây*/
		if (D[L[Dem].x] != 0 && D[L[Dem].y] == 0)
			D[L[Dem].y] = D[L[Dem].x];
		/*Ghép 2 cây thành 1 cây mới*/
		if (D[L[Dem].x] != D[L[Dem].y] && D[L[Dem].y] != 0) {
			Temp = D[L[Dem].x];
			for (int i = 0; i < n; i++)
				if (Temp == D[i])
					D[i] = D[L[Dem].y];
		}
		Sum += min;
		Dem++;
	} while (Dem < n - 1);
	return;
}

/*Chương trình chính*/
int main() {
	NhapFile();
	Kruskal();
	XuatFile();
	XoaConTro();
	system("pause");
	return 0;
}