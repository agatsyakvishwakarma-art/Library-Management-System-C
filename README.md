# 📚 Library Management System (C)

A lightweight, file-based **Library Management System** written in C.
This project lets you **add, display, search, edit, and delete** book records using binary file handling.
Designed as a simple, menu-driven program ideal for learning file operations and structured data storage.

---

## 🚀 Features

* Add new books
* Display all books
* Search a book by ID
* Edit book details
* Delete book records
* Deleted entries are stored separately (`delete.dat`)
* Clean console UI
* Persistent storage using binary files (`books.dat`, `temp.dat`)

---

## 🗂️ File Structure

```
.
├── main.c            // Source code
├── books.dat         // Main book database
├── temp.dat          // Used for edit/delete operations
```

---

## 🛠️ How It Works

Books are stored as binary records using:

```c
struct book {
    int ID;
    char Name[50];
    char Author[50];
    int Quantity;
};
```

All operations use `fread()` and `fwrite()` to handle these structures directly in binary form.

---

## 📌 Menu UI

```
|============================= MENU ==============================|
 1. Add New Book
 2. Display Books
 3. Search Book
 4. Edit Book
 5. Delete Book
 6. Save & Exit
|=================================================================|
```

---

## ✔️ Why This Project Is Useful

* Excellent introduction to **file handling in C**
* Shows real-world CRUD operations
* Beginner-friendly
* Perfect for college submissions and learning structured programming

---

## 💡 Future Improvements

* Sorting books by ID or Name
* Duplicate ID detection
* Search by Name or Author
* Admin login system
* GUI version (C++/Python)
* Database upgrade (MySQL)

---

## 👤 Author

**Agatsya Vishwakarma**
LDCE – Computer Engineering (1st Semester)
