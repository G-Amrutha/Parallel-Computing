#include <stdlib.h>
#define MaxGrayComponentValue 255
#define image_columns 125
#define image_rows 177
#define carriage_return '\n'
#define header_lines 4

int image_in[image_rows + 1][image_columns + 1];
int i;
int j;
int hist[MaxGrayComponentValue + 2];
spinlock L[MaxGrayComponentValue+1];

void read_image_values() {
    for (i = 1; i <= image_rows; i++) {
        for (j = 1; j <= image_columns; j++) {
            cin >> image_in[i][j];
        }
    }
}

void read_image_header() {
    char buffer[header_lines+1][80];
    char c;
    int m;
    for (m = 1; m <= header_lines; ++m) {
        do {
            cin >> c;
        }
        while (c != carriage_return);
    }
}

int main() {
    read_image_header();
    read_image_values();
    for (i = 0; i <= MaxGrayComponentValue; i++)
        hist[i] = 0;
    forall i = 1 to image_rows do {
        int j, intensity;
        for (j = 1; j <= image_columns; j++) {
            intensity = image_in[i][j];
            Lock(L[intensity]);
            hist[intensity] = hist[intensity] + 1;
            Unlock(L[intensity]);
        }
    }
    forall i = 0 to MaxGrayComponentValue do{
        cout <<hist[i]<<endl;
    }
}
