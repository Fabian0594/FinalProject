#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

void login() {
    struct termios old_attr, new_attr;
    char ch;
    int i = 0;
    char username[50];
    char password[50];
    FILE *file;

    printf ("Aplicativo - Graficadora - UTP\n\n");

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // remove newline character

    /* Guardar los atributos originales */
    tcgetattr(STDIN_FILENO, &old_attr);
    new_attr = old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);

    /* Establecer los nuevos atributos */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);

    printf("Password: ");
    while ((ch = getchar()) != '\n' && i < 50) {
        password[i++] = ch;
        printf("*");
    }
    password[i] = '\0';

    /* Restaurar los atributos originales */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);

    file = fopen("seguridad.gra", "w");
    if (file == NULL) {
        printf("\nError al abrir el archivo.\n");
        return;
    }

    fprintf(file, "Nombre de usuario: %s\nContraseña: %s\n", username, password);
    fclose(file);

    printf("\nLos datos se han guardado correctamente en el archivo 'seguridad.gra'.\n");
}

int main() {
    login();
    
    return 0;
}
