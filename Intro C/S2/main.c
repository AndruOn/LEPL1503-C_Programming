#include <stdio.h>
#include <math.h>
#include <stdbool.h>


char* strcatavecCrochets(char* dest, const char* src) {
    int i;
    for (i = 0; dest[i] != '\0'; ++i) {}
    for (int j = 0; src[j] != '\0'; ++j) {
        dest[i+j] = src[j];
    }
    return dest;
}
char* strcatPointeur(char* dest, const char* src) {
    char* memoire;
    memoire = dest;
    while (*dest != '\0'){
        dest++;
    }
    while (*src != '\0'){
        *dest = *src;
        dest++; src++;
    }
    *dest = '\0';
    return memoire;
}
size_t strlen(const char* s) {
    int i = 0;
    while (*s++){i++;}
    return i;
}

void teststrlenetstrcat(){
    printf("Hello, World!\n");
    char* src;
    char vroum[] = "a vroom";
    src = &vroum;
    char* dest;
    char caca[] = "cac";
    dest = &caca;
    printf("src= %s\n", src);
    printf("dest= %s\n", dest);
    printf("\n");
    //printf("dest after strcat= %s\n", strcat(dest, src));
    printf("dest after strcatpointeur= %s\n", strcatPointeur(dest, src));
    printf("len= %lu",strlen(dest));
}



int strcasecmp(const char *s1, const char *s2) {
    int i;
    char s1minuscule;
    char s2minuscule;
    for (i = 0; i < strlen(s1); i++){
        if (s2[i] == '\0'){
            printf("s2 est un préfix de s1\n");
            return 1;
        }

        if ('A' <= s1[i] && s1[i] <= 'Z') {
            s1minuscule = s1[i] - ('A' - 'a');
        } else { s1minuscule = s1[i]; }
        if ('A' <= s2[i] && s2[i] <= 'Z') {
            s2minuscule = s2[i] - ('A' - 'a');
        } else { s2minuscule = s2[i]; }

        if (s1minuscule < s2minuscule) {
            printf("s1min= %c / s2min= %c\n", s1minuscule, s2minuscule);
            printf("s1minuscule + petit / i=%d\n",i);
            return -1;}
        else if (s1minuscule > s2minuscule) {
            printf("s1min= %c / s2min= %c\n", s1minuscule, s2minuscule);
            printf("s2minuscule + petit / i=%d\n",i);
            return 1;}
    }
    if (s2[i] != '\0'){
        printf("s1 est un préfix de s2\n");
        return -1;}
    return 0;
}

void testprintcomp(char a[] ,char b[]){
    char* s1 = a;
    char* s2 = b;
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);
    printf("strcasecomp(s1,s2) = %d\n", strcasecmp(s1, s2));
    printf("\n");
}
void testStrCaseComp(){
    testprintcomp("aaa", "baa");
    testprintcomp("aaad", "aabd");
    testprintcomp("Aa","ba");
    testprintcomp("AAAAA", "aa");
    testprintcomp("ab", "abzjjs");
    testprintcomp("abxxbc", "ab");
    testprintcomp("Aad", "aad");
}



int pal(char *str) {
    if (*str=='\0') {
        return -1;
    }
    unsigned long len = strlen(str);
    int i = 0;
    int j = len-1;
    while (i < j){
        while (str[i] == ' ') {
            i++;
        }
        while (str[j] == ' ') {
            j--;
        }
        if (str[i] != str[j]) {
            return 0;
        }
        i++; j--;
    }

    return 1;
}

void testPalprint(char* s){
    printf("str = %s   \npal(str) = %d\n",s,pal(s));
}
void testPal(){
    //"racecar", "a man a plan a canal panama" or "kayak".
    testPalprint("racecar");
    testPalprint("a    man a plan a canal panama");
    testPalprint("assa");
    testPalprint("sad");
    testPalprint("");
    testPalprint("       a  ");
    testPalprint("   ");
}



int mainPrint1sur2(char* args) {
    int i = 0;
    printf(*args);
    while (args != '\0') {
        if (i % 2 == 0) {
            printf(" %s",*args);
        }
        args++;
        i++;
    }
    printf("\n");
}



void swap(int *i, int *j) {
    int memoire;
    memoire = *j;
    *j = *i;
    *i = memoire;
}

void  testSwap(){
    int i = 1;
    int j = 2;
    printf("int i = %d , int j = %d\n", i, j);
    swap(&i, &j);
    printf("Swap\nint i = %d , int j = %d\n\n", i, j);
}


struct fract_t {
    int num;
    int denum;
};
void swapFract(struct fract_t *a, struct fract_t *b){
    int memoire = b->num;
    b->num = a->num;
    a->num = memoire;
    memoire = b->denum;
    b->denum = a->denum;
    a->denum = memoire;
}

void swapFractPrint(a_num, a_denum, b_num, b_denum){
    struct fract_t a; struct fract_t b;
    a.num = a_num; a.denum = a_denum;
    b.num = b_num; b.denum = b_denum;
    printf("fract_a = %d/%d    fract_b = %d/%d\n", a.num, a.denum, b.num, b.denum);
    swapFract(&a, &b);
    printf("SwapFraction\n");
    printf("fract_a = %d/%d    fract_b = %d/%d\n", a.num, a.denum, b.num, b.denum);
}
void testSwapFract(){
    swapFractPrint(1,2,3,4);
}



uint8_t get_3_leftmost_bits(uint8_t x){
    return x >> 29;
}
uint8_t get_4_eightmost_bits(uint8_t x){
    return x << 28 >> 28;
}


void int2bin(unsigned int num, char *str) {
    int i;
    str[32] = '\0';
    for (i = 32 - 1; i >= 0; i--) {
        if ((num & (unsigned int) 1) == 1) {
            str[i] = '1';
        } else {
            str[i] = '0';
        }
        num = num >> 1;
    }
    printf("%s",str);
}

/*
 * @pre 0<= pos < 64
 */
uint64_t set_bit(uint64_t x, int pos, bool value) {
    if (value == 1) {
        return x | ( (uint64_t) 1 << pos );
    } else {
        return x & ( (~(uint64_t) 1) - 1 );
    }
}

uint8_t nbits(uint32_t n) {
    uint8_t bits_count;
    for (int i = 0; i < 32; i++) {
        if (((n << i) >> 31) == 1) {
            bits_count++;
        }
    }
    return bits_count;
}

void printbits(uint8_t n) {
    uint8_t pos_n;
    for (int i = 0; i < 8; i++) {
        pos_n = (n << i) >> 7;
        printf("pos_n= %d\n",pos_n);
        if (pos_n == 1) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    printf("\n");
}

void test_nbits(){
    printf("test_nbits:\n");
    printf("%d\n", nbits(0b00001111));
    printf("%d\n", nbits(0b00110101));
    printf("%d\n", nbits(0b00000001));
}

int32_t cycle_bits(uint32_t x, uint8_t n) {
    uint32_t premiere_moitie = x << n;
    uint32_t deuxieme_moitie = x >> (32-n);
    return premiere_moitie | deuxieme_moitie;
}



int main() {
    //test_nbits();
    printbits(0b11001011);
    printf("Hello world");
    return 0;
}