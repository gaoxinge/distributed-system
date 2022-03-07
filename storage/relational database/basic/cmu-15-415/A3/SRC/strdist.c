double str2dbl(char *str) {
    double value = 0;
    double denom = 1.0;

    while (*str) {
        value += (*str) / denom;
        str++;
        denom *= 128;
    }

    return value;
}

double strdist(char *str1, char *str2) {
    return str2dbl(str1) - str2dbl(str2);
}

//#define UNIT_TEST_STRDIST
#ifdef UNIT_TEST_STRDIST
int main(int argc, char *argv[]) {
    char *str1 = argv[1];
    char *str2 = argv[2];

    double val1 = str2dbl(str1);
    double val2 = str2dbl(str2);

    printf("%lf %lf\n", val1, val2);
    printf("%lf\n", strdist(str1, str2));
}
#endif
