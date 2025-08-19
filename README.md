# get_next_line
<br>
<p align="center">
    <img src=https://upload.wikimedia.org/wikipedia/commons/1/19/C_Logo.png alt="Logo C" width="125">
</p>

### Skills

- File descriptor handling (`open`, `read`, `close`)
- Static variables for persistent state
- Dynamic memory allocation (`malloc`, `free`)
- Buffer management and incremental reading
- String manipulation and concatenation
- Edge case handling (EOF, multiple FDs, buffer sizes)

<br>

## About

`get_next_line` is a function that reads a file descriptor line by line.

Its prototype is:
```c
char    *get_next_line(int fd);
```
Each call returns the next line of the file, including the trailing newline character (`\n`) if one is found. When the end of the file is reached, the function returns `NULL`.

The project focuses on **buffered file reading**:
- Data is read in chunks of size `BUFFER_SIZE`.
- A static variable is used to store any leftover text between calls.
- Memory is dynamically managed to concatenate chunks until a complete line is formed.

The function works with any valid file descriptor, including standard input (`stdin`).  

In the bonus part, it also supports **simultaneous reading from multiple file descriptors**.

<br>

## Usage

### Mandatory Part

**1. Clone the repository**
```bash
git clone git@github.com:maudiffr/get_next_line.git
cd get_next_line
```

**2. Write a custom test file to test functions**
```c
// main.c

#include <fcntl.h>      // open
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    // ------ Case 1: Read from file if argument given ------
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            return (1);
        }
        printf("=== Reading from file: %s ===\n", argv[1]);
    }
    // ------ Case 2: Read from standard input ------
    else if (argc == 1)
    {
        fd = 0; // stdin
        printf("=== Reading from standard input (Ctrl+D to stop) ===\n");
    }
    else
    {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    if (fd != 0)
        close(fd);

    return (0);
}
```

**3. Compile the project with the** `BUFFER_SIZE` **of your choice (>0)**

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

**4. Create a test file manually (example** `test1.txt`**):**
```bash
echo -e "Hello\nWorld\n42" > test1.txt
```

**5. Run the program**

- With a file:
```bash
./gnl_test test1.txt
```

- With standard input:
```bash
./gnl_test
# type your input, then press Ctrl+D
```
<br>

---

### Bonus Part (Multiple File Descriptors)

**1. Write a custom test file to test functions**
```c
// main_bonus.c

#include <fcntl.h>      // open
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include "get_next_line_bonus.h"

int main(void)
{
    int     fd1, fd2;
    char    *line1;
    char    *line2;

    // Open two test files
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("open");
        return (1);
    }

    printf("=== Reading alternately from test1.txt and test2.txt ===\n");

    while (1)
    {
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);

        if (!line1 && !line2)
            break;

        if (line1)
        {
            printf("test1: %s", line1);
            free(line1);
        }
        if (line2)
        {
            printf("test2: %s", line2);
            free(line2);
        }
    }

    close(fd1);
    close(fd2);

    return (0);
}
```

**2. Compile the bonus version**

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_test_bonus
```

**3. You can create a second test file (example `test2.txt`):**
```bash
echo -e "This\nis a\ntest" > test2.txt
```

**4. Run the bonus program**

```bash
./gnl_test_bonus
```
No command-line arguments are needed; filenames are defined in `main_bonus.c`.