#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;

const int BOOK_LIMIT = 1000;
const char FILENAME[] = "bookList.txt";


struct Book {
	char Name[100];
	char Author[50];
  int Year;
  float Rating;
};

int bookCount;
Book books[BOOK_LIMIT];



void showMenu()
{
    cout << "\n=== Трекер книг===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}
void saveBookToFile(const char* filename, Book b)
{
  ofstream out(filename,ios::app);
  if(out)
  {
    out << b.Name << endl <<  b.Author << '\n' << b.Year << '\n' << b.Rating << '\n' << "////" << endl;
    books[bookCount++] = b;
  }
  else
  {
    cout << "Произошла ошибка при записи в файл" << endl;
    return;
  }
  out.close();
}
void loadBooksFromFile()
{
  char yearStr[20], ratingStr[20];
  ifstream in(FILENAME);
  while(true)
  {
  if(!in.getline(books[bookCount].Name, sizeof books[bookCount].Name))
    break;
  if(!in.getline(books[bookCount].Author, sizeof books[bookCount].Author))
    break;
  if(!in.getline(yearStr, sizeof yearStr))
    break;
  if(!in.getline(ratingStr, sizeof ratingStr))
    break;
  }
  bookCount ++;


}
void addBook()
{
  Book b;

  cout << "Введите название книги: " << endl;
  std::cin >> std::ws;   
  cin.getline(b.Name, sizeof b.Name);
  
  cout << "Введите автора: " << endl; 
  cin.getline(b.Author, sizeof b.Author);
  
  cout << "Введите год прочтения: " << endl;
  while (!(cin >> b.Year)) {
    cin.clear();
    cin.ignore(100, '\n');
    cout << "Ошибка, введите целое неотрицательное число: " << endl;
  }

  cout << "Введите оценку (0-10): " << endl;
  while (!(cin >> b.Rating)) {
    cin.clear();
    cin.ignore(100, '\n');
    cout << "Ошибка, введите число от 0.0 до 10.0: " << endl;
  }

  saveBookToFile(FILENAME, b);
}

void showStats()
{
  float avg = 0;
  float ma = 0;

  for(Book b : books) {
    avg+=b.Rating;
    ma = max(ma,b.Rating);
  }
  cout << "Количество прочитанных книг: " << bookCount << endl;
  cout << "Средняя оценка: " << avg/bookCount << endl;
  cout << "Наивысшая оценка: " << ma << endl;


}




void showAllBooks()
{
  if(bookCount>0)
  {
      for(int i = 0; i < bookCount ; i++)
      {
          cout << "Книга: " << books[i].Name << endl;
          cout << "Автор: " << books[i].Author << endl;
          cout << "=====" << endl;
      }
  }
  else {
      cout << "Вы еще не добавили ни одной книги"  << endl;
  }
}
int main() {
  loadBooksFromFile();
  int choice;

  do{
    showMenu();
    cin >> choice;
    switch(choice)
    {
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
        break;
      default:
        cout << "Неправильный ввод";
        break;
    }
  } while(choice !=4);
}
