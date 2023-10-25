#include "fcgi_stdio.h"
#include <stdio.h>

int main() {
    while(FCGI_Accept() >= 0){
        printf("Content-type: text/html\r\nStatus: 200 OK\r\n\r\n");
        printf("<html>\n<head><title>My Page</title>");
        printf("<style>.large-text { font-size: 24px; }</style>");
        printf("</head>\n<body>\n");
        printf("<p class='large-text'>Hello World!</p>\n");  // Класс large-text применяет стиль с увеличенным размером шрифта
        printf("</body>\n</html>\n");
    }
    return 0;
}