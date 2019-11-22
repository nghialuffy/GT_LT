#include<iostream>
#include<conio.h>
#include <fstream>
using namespace std;
#define TRUE 1 
#define FALSE  0 
#define MAX  10001
#define FileInt "Input.inp"
#define FileOut "Output.out"

/*Lưu lại những cạnh đã đi qua x->y*/
typedef struct Edge {
	int x, y;
};

/*Biến*/
int **A;				//Ma trận hai chiều
int n;					//số đỉnh của đồ thị
int *D;					//Đánh dấu các cạnh đã cho vào cây khung
Edge *L;				//Mảng đánh dấu danh sách đỉnh, cạnh đã thêm vào cây khung nhỏ nhất
int Sum = 0;			//Độ dài của cây khung nhỏ nhất.

/*Đọc dữ liệu từ file*/
void NhapFile() {
	ifstream input(FileInt);
	if (input.fail())
	{
		cout << "Failed to open this file!" << endl;
		return;
	}
	input >> n;
	A = new int*[n + 1];
	D = new int[n + 1];
	L = new Edge[n];
	//Khỏi tạo ma trận trọng số của đồ thị A[i][j] = MAX. Nhập ma trận
	for (int i = 1; i <= n; i++) {
		D[i] = TRUE;		//Gán nhãn cho các đỉnh chua cho vào cây khung
		A[i] = new int[n + 1];
		for (int j = 1; j <= n; j++) {
			input >> A[i][j];
			if (A[i][j] == 0) {
				A[i][j] = MAX;
			}
		}
	}
	input.close();
}

/*Ghi dữ liệu ra file*/
void XuatFile() {
	ofstream output(FileOut);
	if (output.fail()) {
		cout << "Failed to write this file!" << endl;
		return;
	}
	output << "Trong so cua cay khung nho nhat :" << Sum << endl;
	int **res = new int*[n + 1];
	for (int i = 1; i <= n; i++) {
		res[i] = new int[n + 1];
		for (int j = 1; j <= n; j++) {
			res[i][j] = 0;
		}
	}
	for (int i = 1; i <= n - 1; i++) {
		res[L[i].x][L[i].y] = A[L[i].x][L[i].y];
		res[L[i].y][L[i].x] = A[L[i].y][L[i].x];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			output << res[i][j] << " ";
		}
		output << endl;
	}
	for (int i = 1; i <= n; i++) {
		delete[] res[i];
	}
	delete[] res;
	output.close();
	return;
}

/*Xóa Con Trỏ*/
void XoaConTro() {

	for (int i = 1; i <= n; i++) {
		delete[] A[i];
	}
	delete[] A;
	delete[] D;
	delete[] L;
	return;
}

/*Thuật Toán PRIM*/
void PRIM() {
	int k, top, min, l, t, u, dem = 0;
	int *s = new int[n];				//mảng chứa các đỉnh của cây khung nhỏ nhất.
	u = 1;
	top = 1;
	s[top] = u;							// thêm đỉnh u bất kỳ vào mảng s[]
	D[u] = FALSE;
	while (dem < n - 1) {
		min = MAX;
		//tìm cạnh có độ dài nhỏ nhất với các đỉnh trong mảng s[].
		for (int i = 1; i <= top; i++) {
			t = s[i];
			for (int j = 1; j <= n; j++) {
				if (D[j] && min > A[t][j]) {
					min = A[t][j];
					k = t;
					l = j;
				}
			}
		}
		dem++;
		Sum += min;
		//thêm vào danh sách cạnh của cây khung.
		L[dem].x = k;
		L[dem].y = l;
		D[l] = FALSE;
		top++;
		s[top] = l;
	}
}

/*Chương trình chính*/
int main() {
	NhapFile();
	PRIM();
	XuatFile();
	XoaConTro();
	system("pause");
	return 0;
}