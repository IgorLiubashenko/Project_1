#include <stdio.h>
#include <math.h>

int main() {
    double y;
    printf("введіть y зі значенням більшим за -5: ");
    scanf("%lf", &y);

    
    if (y + 5 <= 0) {
        printf("Помилка");
    } else {
    
        double R = sqrt( pow(2 + y, 2) + pow(sin(y + 5), 2)) + log( y + 5 ) - pow(y, 3);
    

    
                printf("R = %lf\n", R);
            }
         return 0;
    }


