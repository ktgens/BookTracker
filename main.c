#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOK_LIMIT 1000
#define FILENAME "bookList.txt"

typedef struct {
	char Name[101];
	char Author[61];
	int Year;
	float Rating;
} Book;



int bookCount = 0;

Book books[BOOK_LIMIT];



void showMenu() {
	printf("\n=== Трекер книг===\n");
	printf("1. Добавить книгу\n");
	printf("2. Показать все книги\n");
	printf("3. Показать статистику\n");
	printf("4. Выход\n");
	printf("Выберите пункт: ");
}



void saveBookToFile(Book b) {
	FILE* out = fopen(FILENAME, "a");

	if (out) {
		fprintf(out, "%s\n", b.Name);
		fprintf(out, "%s\n", b.Author);
		fprintf(out, "%d\n", b.Year);
		fprintf(out, "%f\n", b.Rating);
		fclose(out);
	}
	else {
		printf("Произошла ошибка при записи в файл\n");
		return;
	}
}



int readLine(FILE* f, char* buffer, int maxLen) {
	if (fgets(buffer, maxLen, f) == NULL)
		return 0;
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';
	return 1;
}



void loadBooksFromFile() {
	FILE* fin = fopen(FILENAME, "r");
	if (!fin)
		return;

	while (bookCount < BOOK_LIMIT) {
		Book b = { 0 };
		if (!readLine(fin, b.Name, sizeof(b.Name)))
			break;
		if (!readLine(fin, b.Author, sizeof(b.Author)))
			break;
		if (fscanf(fin, "%d", &b.Year) != 1)
			break;
		if (fscanf(fin, "%f", &b.Rating) != 1)
			break;
		int c;
		while ((c = fgetc(fin)) != '\n' && c != EOF);

		books[bookCount++] = b;
	}

	fclose(fin);
}



int readLineStdin(char* buffer, int maxLen) {

	if (fgets(buffer, maxLen, stdin) == NULL)
		return 0;

	size_t len = strlen(buffer);

	if (len > 0 && buffer[len - 1] == '\n') {
		buffer[len - 1] = '\0';
		return 1;
	}
	else {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return 0;
	}
}



void addBook() {

	if (bookCount >= BOOK_LIMIT) {
		printf("Ошибка количество книг максимально\n");
		return;
	}

	Book b = { 0 };

	printf("Введите название книги:\n");

	for (;;) {
		if (readLineStdin(b.Name, sizeof(b.Name)) && b.Name[0] != '\0')
			break;
		printf("Ошибка, попробуйте еще раз:\n");
	}

	printf("Введите автора:\n");

	while (1) {
		if (readLineStdin(b.Author, sizeof(b.Author)) && b.Author[0] != '\0')
			break;
		printf("Ошибка, попробуйте еще раз:\n");
	}

	printf("Введите год прочтения:\n");

	while (scanf("%d", &b.Year) != 1 || b.Year < 0) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		printf("Ошибка, введите целое неотрицательное число:\n");
	}

	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	printf("Введите оценку (0-10):\n");

	while (scanf("%f", &b.Rating) != 1 || b.Rating < 0.0 || b.Rating > 10.0) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		printf("Ошибка, введите число от 0.0 до 10.0:\n");
	}
	while ((c = getchar()) != '\n' && c != EOF);
	books[bookCount++] = b;
	saveBookToFile(b);
}



void showStats() {
	float avg = 0;
	float ma = 0;
	Book fav = { 0 };

	for (int i = 0; i < bookCount; i++) {
		avg += books[i].Rating;
		if (books[i].Rating > ma) {
			fav = books[i];
			ma = books[i].Rating;
		}
	}

	printf("============================\n");
	printf("Количество прочитанных книг: %d\n", bookCount);
	printf("Средняя оценка: %f\n", avg / bookCount);
	printf("Наивысшая оценка: %f у книги \"%s\"\n", ma, fav.Name);
	printf("============================\n");
}



void showAllBooks() {
	printf("\n=====\n");

	if (bookCount > 0) {
		for (int i = 0; i < bookCount; i++) {
			printf("Книга: %s\n", books[i].Name);
			printf("Автор: %s\n", books[i].Author);
			printf("Год: %d\n", books[i].Year);
			printf("Оценка: %f\n", books[i].Rating);
			printf("=====\n");
		}
	}
	else {
		printf("Вы еще не добавили ни одной книги\n");
	}
}



int main() {
	loadBooksFromFile();

	while (1) {
		showMenu();

		int choice;

		if (scanf("%d", &choice) != 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Введите номер пункта 1-4.\n");
			continue;
		}

		int c;

		while ((c = getchar()) != '\n' && c != EOF);

		switch (choice) {
		case 1:
			addBook();
			break;
		case 2:
			showAllBooks();
			break;
		case 3:
			showStats();
			break;
		case 4:
			return 0;
		default:
			printf("Нет такого пункта.\n");
			break;
		}
	}
}
