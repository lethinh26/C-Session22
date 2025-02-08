#include <stdio.h>
#include <string.h>

struct accounts {
	char username[20];
	char password[20];
};

void menu();
void login(struct accounts *acc, int current);
void reg(struct accounts *acc, int *current);
void workBinaryFile(struct accounts *acc, char *mode, int *current);

int main() {
	int current = 0;
	struct accounts acc[100];
	workBinaryFile(acc, "rb", &current);
	while (1) {
		menu();
		int choose;
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choose);
		switch (choose) {
			case 1:
				login(acc, current);
				break;
			case 2:
				reg(acc, &current);
				break;
			case 3:
				return 0;
			default:
				printf("Lua chon ko hop le\n");
				break;
		}
	}
}

void menu() {
	printf("============MENU============\n");
	printf("1. Dang nhap\n");
	printf("2. Dang ki\n");
	printf("3. Thoat\n");
	printf("============================\n");
}

void login(struct accounts *acc, int current) {
	char username[20];
	char password[20];
	printf("Nhap ten dang nhap: ");
	fflush(stdin);
	fgets(username, 20, stdin);
	username[strcspn(username, "\n")] = '\0';
	printf("Nhap mat khau: ");
	fgets(password, 20, stdin);
	password[strcspn(password, "\n")] = '\0';
	int checkuser = 1, checkpass = 1;

	for (int i = 0; i < current; i++) {
		if (strcmp(acc[i].username, username) == 0) {
			checkuser = 0;
			if (strcmp(acc[i].password, password) == 0) {
				checkpass = 0;
				break;
			}
		}
	}
	if (checkuser) {
		printf("Sai ten dang nhap\n");
	}else if (checkpass) {
		printf("Sai mat khau\n");
	}else {
		printf("Dang nhap thanh cong\n");
	}
}

void reg(struct accounts *acc, int *current) {
	char username[20];
	printf("Nhap ten dang ki: ");
	fflush(stdin);
	fgets(username, 20, stdin);
	username[strcspn(username, "\n")] = '\0';
	for (int i = 0; i < *current; i++) {
		if (strcmp(username, acc[i].username) == 0) {
			printf("Ten dang ki da ton tai\n");
			return;
		}
	}
	strcpy(acc[*current].username, username);
	printf("Nhap mat khau: ");
	fgets(acc[*current].password, 20, stdin);
	acc[*current].password[strcspn(acc[*current].password, "\n")] = '\0';
	(*current)++;
	workBinaryFile(acc, "ab", current);
	printf("Dang ki thanh cong\n");
}

void workBinaryFile(struct accounts *acc, char *mode, int *current) {
	FILE *fptr;
	fptr = fopen("../accounts.bin", mode);
	if (fptr == NULL) {
		printf("Loi mo file\n");
		return;
	}
	if (strcmp(mode, "ab") == 0) {
		fwrite(acc, sizeof(struct accounts), *current, fptr);
	}else {
		*current = fread(acc, sizeof(struct accounts), 100, fptr);
		printf("%d", *current);
	}
	fclose(fptr);
}