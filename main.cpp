#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>

using namespace std;
struct element { // 1 phan tu gom co 3 thuoc tinh: toa do x,y va gia tri phan tu
	int x, y, value;
};
element list[10]; // mang co toi da 10 phan tu
int soLuong; // so luong phan tu

// ham nhap mang
void nhapMang() {
	//Nhap mang tren man hinh console
	do {
		cout << "Nhap so luong phan tu: ";
		cin >> soLuong;
	} while (!(soLuong > 0 && soLuong <= 10));

	for (int i = 0;i < soLuong;i++) {
		cout << "Nhap phan tu thu " << i + 1 << ": ";
		cin >> list[i].value;
	}
}

// ham in ki tu len man hinh do hoa
void renderText(string text, int x, int y) {
	glRasterPos2f(x, y); // dat van ban len man hinh tai toa do x,y
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); // in tung ki tu
	}
}


void init()
{
	//to mau nen den
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//thiet lap phep chieu
	glMatrixMode(GL_PROJECTION);
	//thiet lap ma tran don vi
	glLoadIdentity();
	gluOrtho2D(0, 1280, 1280, 0);

	//khoi tao toa do su dung de ve cot cua toi da 10 phan tu
	int x_pos = 100;
	for (int i = 0;i < 10;i++) {
		list[i].y = 700;
		list[i].x = x_pos;
		x_pos += 100;
	}
}

//ham ve 1 phan tu trong mang duoi dang 1 cot 
void drawElement(element phanTu, float red, float green, float blue) {
	glColor3f(red, green, blue); // ham thiet lap mau ve voi 3 tham so: red, green, blue
	glRecti(phanTu.x, phanTu.y, phanTu.x + 85, phanTu.y - phanTu.value * 5); // ham ve hinh chu nhat
	renderText(to_string(phanTu.value), phanTu.x + 35, phanTu.y + 100); // ham in chu len man hinh do hoa
}
// ham ve bieu dien cac phan tu trong mang la cac cot
void drawArray(int it, int skip) {
	glClear(GL_COLOR_BUFFER_BIT); //xoa buffer truoc do tren man hinh do hoa
	for (int i = 0;i < soLuong;i++) {
		if (i != skip) { // neu cot hien tai dang xet la cot bi lay ra thi khong ve
			if (i != it) { // phan tu dang xet hien tai ve cot mau do, con lai ve mau vang 
				drawElement(list[i], 1.0, 1.0, 0.0);
			}
			else {
				drawElement(list[i], 1.0, 0.0, 0.0);
			}
		}
		Sleep(75); // dung man hinh do hoa trong 75ms
	}
	glFlush(); // cap nhat man hinh do hoa
}

// Ham sap xep chen
void insertionSort()
{
	int i, key, j;
	for (i = 1; i < soLuong; i++)
	{
		drawArray(i, -1);
		// neu phan tu dang xet hien tai co gia tri lon hon phan tu truoc do(khong xay ra thao tac chen) thi truc tiep 
		// xet phan tu tiep theo  
		if (list[i].value >= list[i - 1].value) continue;
		drawArray(i, i); // ve lai mang sau khi lay phan tu thu i de so sanh voi nhung phan tu truoc do
		key = list[i].value;
		j = i - 1;

		// di chuyen phan tu cac phan tu lon phan tu thu i qua ben phai
		while (j >= 0 && list[j].value > key) {
			if (list[j].value > key) {
				// ve lai mang voi phan tu thu j+1 bi lay ra(khong ve),
				// phan tu thu j duoc chon de day qua phai(ve mau do)
				drawArray(j, j + 1); 
				list[j + 1].value = list[j].value;
				// ve lai mang sau khi day phan tu thu j qua vi tri j+1,
				// phan tu thu j+1 ve mau do,
				// phan tu thu j khong ve(do da day qua j+1)
				drawArray(j + 1, j);
			}
			j--;
		}

		list[j + 1].value = key;
		drawArray(j + 1, -1);
	}

	// ve lai danh sach sau khi hoan thanh sap xep thanh cac cot (ve mau xanh)
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < soLuong; i++) {
		drawElement(list[i], 0, 1, 0);

	}
	glFlush(); //cap nhat lai man hinh do hoa
}

void display()
{
	drawArray(-1, -1);
	insertionSort();
	Sleep(3000); // dung 3000 ms roi thoat chuong trinh
	exit(0);
}

int main(int argc, char* argv[]) {
	nhapMang();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //khoi tao che do ve single buffer va he mau RGB
	glutInitWindowSize(1280, 1280); //khoi tao man hinh do hoa co kich thuoc 1280x1280
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Insertion Sort"); //dat ten cua so la "Insertion Sort"
	init();
	glutDisplayFunc(display);
	glutMainLoop();



	return 0;
}
