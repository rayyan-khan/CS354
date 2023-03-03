void sndA(void), sndB(void);

void sndA(void) {
    while(1) {
        kputc('A');
    }
}

void sndB(void) {
    while(1) {
        kputc('B');
    }
}