#include <iostream>
#include <vector>
#include <string>

struct Book {

    std::string title;
    std::string author;
    std::string genre;
    std::string description;
    bool reserved = false;
};

std::vector<Book> library;

std::vector<Book> reservedBooks;

void searchBooks(const std::string& query ) {
    setlocale(LC_ALL, "Russian");
    std::cout << "Результаты поиска для \"" << query << "\":\n";
    for (const auto& book : library) {
        if (book.title.find(query) != std::string::npos ||
            book.author.find(query) != std::string::npos ||
            book.genre.find(query) != std::string::npos) {
            std::cout << "Название: " << book.title << "\n"
                << "Автор: " << book.author << "\n"
                << "Жанр: " << book.genre << "\n"
                << "Описание: " << book.description << "\n\n";
        }
    }
}

void addBook() {
    setlocale(LC_ALL, "Russian");
    Book newBook;
    std::cout << "Введите название книги: ";
    std::getline(std::cin, newBook.title);
    std::cout << "Введите автора: ";
    std::getline(std::cin, newBook.author);
    std::cout << "Введите жанр: ";
    std::getline(std::cin, newBook.genre);
    std::cout << "Введите описание: ";
    std::getline(std::cin, newBook.description);
    library.push_back(newBook);
    std::cout << "Книга успешно добавлена в каталог.\n";
}

void reserveBook(const Book& book) {
    setlocale(LC_ALL, "Russian");
    reservedBooks.push_back(book);
    std::cout << "Книга \"" << book.title << "\" успешно зарезервирована.\n";
}

void viewReservedBooks() {
    setlocale(LC_ALL, "Russian");
    if (reservedBooks.empty()) {
        std::cout << "У вас нет зарезервированных книг.\n";
        return;
    }
    std::cout << "Ваши зарезервированные книги:\n";
    for (const auto& book : reservedBooks) {
        std::cout << "Название: " << book.title << "\n"
            << "Автор: " << book.author << "\n"
            << "Жанр: " << book.genre << "\n\n";
    }
}

void cancelReservation(const Book& book) {
    setlocale(LC_ALL, "Russian");
    for (auto it = reservedBooks.begin(); it != reservedBooks.end(); ++it) {
        if (it->title == book.title && it->author == book.author && it->genre == book.genre && it->description == book.description && it->reserved == book.reserved) {
            reservedBooks.erase(it);
            std::cout << "Резервация книги \"" << book.title << "\" успешно отменена.\n";
            return;
        }
    }
    std::cout << "Книга \"" << book.title << "\" не найдена в списке зарезервированных.\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    library.push_back({ "War and peace", "Tolstoy", "Roman", "Эпическое произведение о Отечественной войне 1812 года." });
    library.push_back({ "Prestuplenie and nakazanie", "Dostoevskii", "Роман", "Психологический роман о преступлении и его последствиях." });
    library.push_back({ "Garry Potter", "Rawling", "Fantasy", "Первая книга о приключениях юного волшебника Гарри Поттера." });

    int choice;
    std::string query;
    Book selectedBook;

    do {
        std::cout << "\nБиблиотечный каталог\n"
            << "1. Поиск книг\n"
            << "2. Добавить книгу\n"
            << "3. Зарезервировать книгу\n"
            << "4. Просмотр зарезервированных книг\n"
            << "5. Отменить резервацию\n"
            << "6. Выход\n"
            << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "Введите название, автора или жанр для поиска: ";
            std::getline(std::cin, query);
            searchBooks(query);
            break;
        case 2:
            addBook();
            break;
        case 3:
            std::cout << "Введите название книги для резервирования: ";
            std::getline(std::cin, query);
            for (const auto& book : library) {
                if (book.title == query) {
                    selectedBook = book;
                    reserveBook(selectedBook);
                    break;
                }
            }
            break;
        case 4:
            viewReservedBooks();
            break;
        case 5:
            std::cout << "Введите название книги для отмены резервации: ";
            std::getline(std::cin, query);
            for (const auto& book : reservedBooks) {
                if (book.title == query) {
                    selectedBook = book;
                    cancelReservation(selectedBook);
                    break;
                }
            }
            break;
        case 6:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}