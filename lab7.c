#include <stdio.h>

enum Cars {
    PASSENGER_CAR,
    TRUCK,
    BUS,
    RACE_CAR,
    WORKING_CAR
};

struct Square {
    int x0, y0, x1, y1, x2, y2, x3, y3;
};

int get_area(struct Square self_sq) {
    return (self_sq.x0 - self_sq.x1) * (self_sq.x0 - self_sq.x1) +
           (self_sq.y0 - self_sq.y1) * (self_sq.y0 - self_sq.y1);
}
union printer {
    struct state_bits {
        unsigned char ready:1;
        unsigned char toner:1;
        unsigned char drum:1;
        unsigned char paper:1;
    } bits;
    unsigned char state;
};

int main7() {
    enum Cars a = BUS;
    printf("%d \n", a);
    struct Square sq = {0, 0, 0, 3, 3, 0, 3, 3};
    printf("%d \n", get_area(sq));
    union printer my_printer;
    scanf("%hx", &my_printer.state);
    printf("%d - size of bits \n", sizeof(my_printer.bits));
    if (my_printer.bits.ready) {
        printf("Printer is ready\n");
    } else {
        printf("Printer is not ready\n");
    }
    if (my_printer.bits.toner) {
        printf("Printer has enough toner\n");
    } else {
        printf("Printer has not enough toner\n");
    }
    if (my_printer.bits.drum) {
        printf("Printer`s drum is OK\n");
    } else {
        printf("Printer`s drum is not OK\n");
    }
    if (my_printer.bits.paper) {
        printf("Printer has enough paper\n");
    } else {
        printf("Printer has not enough paper\n");
    }
    return 0;
}