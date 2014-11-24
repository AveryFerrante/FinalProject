#ifndef STEMMER2_H
#define STEMMER2_H
#include <cstring>  /* for memmove */

#define TRUE 1
#define FALSE 0

class Stemmer2
{
private:
    static char * b;       /* buffer for word to be stemmed */
    static int k,k0,j;     /* j is a general offset into the string */
public:
    Stemmer2();
    static int cons(int i);
    static int m();
    static int vowelinstem();
    static int doublec(int j);
    static int cvc(int i);
    static int ends(char * s);
    static void setto(char * s);
    static void r(char * s);
    static void step1ab();
    static void step1c();
    static void step2();
    static void step3();
    static void step4();
    static void step5();
    int stem(char * p, int i, int j);
};

#endif // STEMMER2_H
