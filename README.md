# C++ Database Engine

This project is a lightweight C++ database engine inspired by SQL. It mimics basic SQL-like commands, allowing users to create, insert into, query, and delete tables using a simplified syntax. This was developed as a hands-on way to better understand database systems and query parsing by researching SQL syntax and translating it into C++ logic.

## 💻 Requirements
- C++ (C++17 or later recommended)
- SFML

## ✨ Features
The engine supports basic operations using a SQL-style syntax:

### 📄 Create a Table
```sql
CREATE TABLE tableName (col1, col2, col3)
```
- Creates a new table with the specified column names.

### ➕ Insert Into a Table
```sql
INSERT INTO tableName (col1, col2, col3) VALUES (val1, val2, val3)
```
- Inserts a new row of values into the specified table.

### 🔍 Select Columns
```sql
SELECT col1, col2 FROM tableName WHERE (col1)
```
- Returns selected columns from the table based on a condition. <br />

To select a single column:
```sql
SELECT col1 FROM tableName WHERE (col1)
```

### 🗑 Delete a Table
```sql
DELETE TABLE tableName
```
- Removes the entire table from the database.

## 📚 Background
This project was developed after researching SQL syntax and concepts. It provided a foundational understanding of how database queries are structured and processed, and how similar logic can be implemented in C++. Parsing input, managing structured data, and designing a command interface were key challenges tackled in this project.

## 💡 What I Learned
- How to parse SQL-like commands and tokenize input.
- How databases manage table creation, row insertion, and querying.
- Using data structures like maps, stacks, and vectors effectively.
- Designing modular, reusable, and visually interactive C++ components.
- Building a GUI application with SFML from scratch.

