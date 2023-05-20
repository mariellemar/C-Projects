#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define LED_PIN "/sys/class/gpio/gpio7"

int main() {
    int fd;
    
    // Abre o arquivo de exportação do GPIO
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Erro ao exportar o pino GPIO");
        return 1;
    }
    
    // Escreve o número do pino desejado
    write(fd, "7", 1);
    close(fd);
    
    // Define o pino como saída
    fd = open(LED_PIN "/direction", O_WRONLY);
    if (fd == -1) {
        perror("Erro ao configurar o pino como saída");
        return 1;
    }
    
    write(fd, "out", 3);
    close(fd);

    while (1) {
        // Acende o LED
        fd = open(LED_PIN "/value", O_WRONLY);
        if (fd == -1) {
            perror("Erro ao abrir o pino do LED");
            return 1;
        }
        
        write(fd, "1", 1);
        close(fd);
        
        // Espera 1 segundo
        sleep(1);
        
        // Apaga o LED
        fd = open(LED_PIN "/value", O_WRONLY);
        if (fd == -1) {
            perror("Erro ao abrir o pino do LED");
            return 1;
        }
        
        write(fd, "0", 1);
        close(fd);
        sleep(1);
    }
    
    return 0;
}
