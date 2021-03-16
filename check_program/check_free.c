/*
** EPITECH PROJECT, 2020
** check free
** File description:
** same alloc and free
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char **my_str_to_word_tab(char *str, char separators);

static void free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

static int my_strcmp(char const *s1, char const *s2)
{
    int t = 0;

    for (; s1[t] == s2[t]; t++)
        if (s1[t] == '\0')
            return (0);
    return (s1[t] - s2[t]);
}

static int check_both(char *line)
{
    char **array = my_str_to_word_tab(line, ' ');

    printf(" %s free for %s alloc\n", array[6], array[4]);
    if (my_strcmp(array[4], array[6]) != 0) {
        free_tab(array);
        return (1);
    }
    free_tab(array);
    return (0);
}

static char *find_free(char *buffer)
{
    char *line = NULL;
    char **tab = my_str_to_word_tab(buffer, '\n');

    for (int i = 0; tab[i]; i++) {
        for (int j = 0; tab[i][j]; j++) {
            if (tab[i][j] == 'a' && tab[i][j+1] == 'l'
                && tab[i][j+2] == 'l' && tab[i][j+3] == 'o'
                && tab[i][j-1] == ' ') {
                line = strdup(tab[i]);
                free_tab(tab);
                return (line);
            }
        }
    }
    free_tab(tab);
    return (0);
}

static int size_file(int fd, char const *filename)
{
    int size = 0;
    struct stat st;

    stat(filename, &st);
    if (S_ISDIR(st.st_mode))
        return (-1);
    size = st.st_size;
    return (size);
}

int main(int const ac, char const **av)
{
    int fd = open(av[1], O_RDONLY);
    int size = size_file(fd, av[1]);
    char *buffer = malloc(sizeof(char) * size + 1);
    char *line = NULL;
    int value = 0;

    if (fd == -1 || size <= 0 || ac != 2) {
        free(buffer);
        close(fd);
        return (84);
    }
    read(fd, buffer, size);
    buffer[size] = 0;
    line = find_free(buffer);
    close(fd);
    free(buffer);
    value = check_both(line);
    free(line);
    return (value);
}
