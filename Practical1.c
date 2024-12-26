#include <stdio.h>
#include <conio.h>

int main()
{
    char str[100];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL)
    {
        printf("Invalid String\n");
        return 0;
    }

    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
        len--;
    }

    for (int i = 0; i < strlen(str) - 2; i++)
    {
        if (str[i] != 'a')
        {
            printf("Invalid String");
            return 0;
        }
    }

    if (str[strlen(str) - 2] == 'b' && str[strlen(str) - 1] == 'b')
    {
        printf("Valid String");
    }
    else
    {
        printf("Invalid String");
    }
    return 0;
}
