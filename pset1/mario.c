//#include <cs50.h>
#include <stdio.h>

void pyramid(int);  //makes pyramid using given number of size
void spaces(int);   //prints given number of spaces
void hashes(int);   //prints given number of hashes

int main(void)
{
	int height;	//get_int("Height: ");       //take height value from user
  	do
    {
        //height = get_int("Height: ");  
        printf("Height: ");
        scanf("%d",&height);
        if (height >= 1 && height <= 8)     //checks height before execution
        {
            pyramid(height);
            return 1;
        }
    }
    while (1);  
}

void pyramid(int h)
{
    int i;
	for (i = 1; i <= h ; i++)
    {
        spaces(h - i);      //prints spaces before hashes
        hashes(i);          //prints hashes
        spaces(2);          //prints two space
        hashes(i);          //again prints hashes
        printf("\n");
    }
}

void spaces(int s)
{
	int i;
    for (i = 0; i < s ; i++)
    {
        printf(" ");
    }
}

void hashes(int h)
{
	int i;
    for (i = 0; i < h ; i++)   
    {
        printf("#");
    }
}
