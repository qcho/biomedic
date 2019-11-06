#include "../apps.h"

void ex_serial(void) {
    char line[80];
    for(;;) {
        puts("Testing serial communication!");
        fgets(line,80,stdin);
        printf("Received line: %s\n", line);
    }
}
