# File Mapping Project

This project demonstrates how to create and manipulate a large file (2 GB) using memory mapping in C on Windows. The project is divided into several parts:

1. **Creating and initializing a large file with fixed-length records.**
2. **Reading records from the large file using memory mapping.**

## Project Structure

file_mapping_project/ <br>
|-- CMakeLists.txt <br>
|-- screenshots/ <br>
| |-- created_file.jpg <br>
| |-- reading_file_1.jpg <br>
| |-- reading_file_2.jpg <br>
|-- src/ <br>
| |-- print_error.c <br>
| |-- print_error.h <br>
| |-- create_file.c <br>
| |-- create_file.h <br>
| |-- read_file.c <br>
| |-- read_file.h <br>
| |-- main.c <br>
|-- README.md <br>

### Files Description

- **src/print_error.c** and **src/print_error.h**: Contains a utility function `print_last_error` for printing detailed error messages.
- **src/create_file.c** and **src/create_file.h**: Functions for creating and initializing a large file with fixed-length records.
- **src/read_file.c** and **src/read_file.h**: Functions for reading records from the file using memory mapping.
- **src/main.c**: Main function that orchestrates the creation and reading of the file.
- **CMakeLists.txt**: CMake configuration file for building the project.


## Created File
![screen of created file](screenshots/created_file.jpg)

## Reading file 1 screenshot
![screen of reading file](screenshots/reading_file_1.jpg)

## Reading file 2 screenshot
![screen of reading file](screenshots/reading_file_2.jpg)
