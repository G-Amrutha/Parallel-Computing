
#include <stdlib.h>
#define header_lines 4;
/* "Hard coding" image header values into sizing and values to be written out.
    Change this to match the values in your image */
/* Note: Image Type P2 will be written directly in cout */
#define image_columns 110
#define image_rows 142
#define  MaxGrayComponentValue 255;
#define carriage_return '\n'

/* Here's the image array you will read into */
int image_in[image_rows+ 1][image_columns+ 1];
/* Here's the image you will write to */
int image_out[image_rows + 1][image_columns+ 1];

/*here's your iterators to scan through the image*/
int i, j;

/* End of Global variables Shared Memory*/

void read_image_header()
 {
/* this procedure reads the four header lines and throw them away*/
    char buffer[header_lines+1][80]; /* buffer for storing input line */
    char c;
    int m;
    for (m = 1; m <= header_lines; ++m)
    do
    {
      cin >> c;  /* input next character */
    } while (c != carriage_return);
 }

void read_image_values()
  {/* read image into array */
    for(i = 1; i <= image_rows; i++)
        for( j = 1; j <= image_columns; j++)
         cin >> image_in[i][j];
   }


int smooth_pixel(int p, int q){
    
    int k;
    int l;
    int m;
    int sum;
    int count= 0;
    
    for( k = p-1; k <= p+1; k++){
        
        forall l = q-1 to q+1 do{
            
            sum = sum + image_in[k][l];
            count++;
            
        }
    }
    
    int avg = sum / count;
    
    return avg;
}


void write_image_to_file()
 {
    int output_row_width = 10;
    int OUTPUT_ROW_COUNTER = 1;
    cout << "P2" << ENDL;
    cout << image_columns << " " << image_rows << ENDL;
    cout << MaxGrayComponentValue << ENDL;
    /*this loop write to the file in a manner acceptable to cstar 10 values per Row */
    for(i = 1; i <= image_rows; i++)
    {
      for ( j = 1; j <= image_columns; j++)
      {
        if (OUTPUT_ROW_COUNTER == output_row_width)
        {
          cout << ENDL;
          OUTPUT_ROW_COUNTER = 1;
        }
        cout << image_out[i][j] << " ";
        OUTPUT_ROW_COUNTER = OUTPUT_ROW_COUNTER + 1;
      }
    }
  }
main()
{

read_image_header();

read_image_values();

  /*  Your work - create the logic to process the image array_in
     Outer for loop is row counter.*/

    for(i = 1; i <= image_rows; i++){
        
        forall j = 1 to image_columns do{
            
            if(i == 1 || i == image_rows || j == 1 || j == image_columns){
                
                image_out[i][j] = image_in[i][j];
            }
            
            else{
                
                image_out[i][j] = smooth_pixel(i,j);
            }
        }
    }
write_image_to_file();

}
