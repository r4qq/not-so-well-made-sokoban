#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
    #include <conio.h>
    #include <iostream>

    inline void clear()
    {
        system("cls");
    }
    
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <iostream>

    inline int _getch() 
    {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    inline void clear()
    {
        system("clear");
    }
#endif

#endif 
