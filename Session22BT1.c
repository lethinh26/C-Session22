#include <stdio.h>
#include <string.h>

struct Students {
	char id[6];
	char name[20];
	int age;
};

void menu();
void workBinaryFile(struct Students *students, int *current, int choose);
void printStudent(struct Students *students, int current);
void addStudent(struct Students *students, int *current);
void editStudent(struct Students *students, int current);
void removeStudent(struct Students *students, int *current);
void findStudent(struct Students *students, int current);
void sortStudent(struct Students *students, int current);

int main() {
	int current = 0;
	struct Students students[100];
	workBinaryFile(students, &current, 0);
	while (1) {
		menu();
		int choose;
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choose);
		switch (choose) {
			case 1:
				printStudent(students, current);
				break;
			case 2:
				addStudent(students, &current);
				break;
			case 3:
				editStudent(students, current);
				break;
			case 4:
				removeStudent(students, &current);
				break;
			case 5:
				findStudent(students, current);
				break;
			case 6:
				sortStudent(students, current);
				break;
			case 7:
				return 0;
			default:
				printf("Lua chon cua ban ko hop le\n");
				break;
		}

	}
	return 0;
}

void menu() {
	printf("=============MENU=============\n");
	printf("1. In danh sach sinh vien\n");
	printf("2. Them sinh vien\n");
	printf("3. Sua thong tin sinh vien\n");
	printf("4. Xoa sinh vien\n");
	printf("5. Tim kiem sinh vien\n");
	printf("6. Sap xep danh sach sinh vien \n");
	printf("7. Thoat\n");
}

void workBinaryFile(struct Students *students, int *current, int choose) {
	FILE *fptr;
	if (choose == 0) {
		fptr = fopen("../student.bin", "rb");
		if (fptr == NULL) {
			printf("Loi mo file\n");
			return;
		}
		*current = fread(students, sizeof(struct Students), 100, fptr);
	}else if (choose == 1) {
		fptr = fopen("../student.bin", "wb");
		if (fptr == NULL) {
			printf("Loi mo file\n");
			return;
		}
		fwrite(students, sizeof(struct Students), *current, fptr);
	}
	fclose(fptr);
}

void printStudent(struct Students *students, int current) {
	printf("-------------Student--------------\n");
	printf("|%-6s|%-20s|%-4s|\n", "MSSV", "Ten", "Tuoi");
	printf("+------+--------------------+----+\n");
	for (int i = 0; i < current; i++) {
		printf("|%-6s|%-20s|%-4d|\n", students[i].id, students[i].name, students[i].age);
		if (i != current - 1) {
			printf("+------+--------------------+----+\n");
		}
	}
	printf("----------------------------------\n");
}

void addStudent(struct Students *students, int *current) {
	printf("Nhap ma sinh vien can them: ");
	fflush(stdin);
	fgets(students[*current].id, 6, stdin);
	students[*current].id[strcspn(students[*current].id, "\n")] = '\0';
	printf("Nhap ten sinh vien: ");
	fgets(students[*current].name, 20, stdin);
	students[*current].name[strcspn(students[*current].name, "\n")] = '\0';
	printf("Nhap tuoi sinh vien: ");
	fflush(stdin);
	scanf("%d", &students[*current].age);


	FILE *fptr = fopen("../student.bin", "ab");
	if (fptr == NULL) {
		printf("Loi mo file");
		return;
	}
	fwrite(&students[*current], sizeof(struct Students), 1, fptr);
	fclose(fptr);
	(*current)++;
	printf("Nhap thanh cong\n");
}

void editStudent(struct Students *students, int current) {
	char id[6];
	printf("Nhap ma sinh vien can sua: ");
	fflush(stdin);
	fgets(id, 6, stdin);
	id[strcspn(id, "\n")] = '\0';
	int check = 1;
	for (int i = 0; i < current; i++) {
		if (strcmp(students[i].id, id) == 0) {
			printf("Nhap ten sinh vien moi: ");
			fgets(students[i].name, 20, stdin);
			students[i].name[strcspn(students[i].name, "\n")] = '\0';
			printf("Nhap tuoi sinh vien moi: ");
			fflush(stdin);
			scanf("%d", &students[i].age);
			workBinaryFile(students, &current, 1);
			check = 0;
		}
	}
	if (check) {
		printf("Ko tim thay sinh vien\n");
	}else {
		printf("Sua thanh thanh cong\n");
	}
}

void removeStudent(struct Students *students, int *current) {
	char id[6];
	fflush(stdin);
	printf("Nhap ma sinh vien can xoa: ");
	fgets(id, 6, stdin);
	id[strcspn(id, "\n")] = '\0';
	int check = 1;
	for (int i = 0; i < *current; i++) {
		if (strcmp(students[i].id, id) == 0) {
			for (int j = i; j < *current-1; j++) {
				students[j] = students[j+1];
			}
			(*current)--;
			workBinaryFile(students, current, 1);
			check = 0;
			break;
		}
	}
	if (check) {
		printf("Ko tim thay sinh vien\n");
	}else {
		printf("Xoa thanh cong\n");
	}
}
void findStudent(struct Students *students, int current) {
	char id[6];
	printf("Nhap ma sinh vien ban muon tim kiem: ");
	fflush(stdin);
	fgets(id, 6, stdin);
	id[strcspn(id, "\n")] = '\0';
	int check = 1;
	for (int i = 0; i < current; i++) {
		if (strcmp(students[i].id, id) == 0) {
			printf("MSSV: %s\n", students[i].id);
			printf("Ten SV: %s\n", students[i].name);
			printf("Tuoi: %d\n", students[i].age);
			check = 0;
		}
	}
	if (check) {
		printf("Ko tim thay sinh vien\n");
	}
}

void sortStudent(struct Students *students, int current) {
	for (int i = 0; i < current-1; i++) {
		for (int j = 0; j < current-i-1; j++) {
			if (strcmp(students[j].id, students[j+1].id) > 0) {
				struct Students temp = students[j];
				students[j] = students[j+1];
				students[j+1] = temp;
			}
		}
	}
	workBinaryFile(students, &current, 1);
	printf("Sap xep thanh cong\n");
}
