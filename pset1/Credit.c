#include<stdio.h>
//#include<cs50.h>
#include<math.h>

int checksum(long long);
void cardtype(long long);
int countdegit(long long);
int sumofdegits(long long, int, int);

int main(void) {
  long long number = 378282246310005; // get_long_long("Number: ");
    if (checksum(number))
      cardtype(number);
	else 
		printf("INVALID\n");

}

int checksum(long long n) {
	int length = countdegit(n);
	int sum = sumofdegits(n, length, 1) + sumofdegits(n, length, 0);
  if (!(sum % 10))
    return 1;	
	return 0;
}

void cardtype(long long n) {
  int length = countdegit(n);
  int checkdigit;		//stores digits for checking further

  if (length == 15) //AMEX
  {
    checkdigit = (long long) floor(n / pow(10, length - 2));
    if (checkdigit == 34 || checkdigit == 37) {
      printf("AMEX\n");
      return;
    }

  }

  if (length == 16) //MASTERCARD
  {
    checkdigit = (long long) floor(n / pow(10, length - 2));
    if (checkdigit >= 51 && checkdigit <= 55) {
      printf("MASTERCARD\n");
      return;
    }
  }

  if (length == 13 || length == 16) //VISA
  {
    checkdigit = (long long) floor(n / pow(10, length - 1));
		if (checkdigit == 4) {
      printf("VISA\n");
      return;
    }
  }

  printf("INVALID\n");
}

int countdegit(long long n) {
  int len;
  for (len = 0; n != 0; n /= 10, len++) {};
  return len;
}

int sumofdegits(long long n, int len, int startfrom) {
	int temp, sum = 0, i;
	for (i = startfrom; i <= len; i += 2) {
    
		if (i == 0 && startfrom == 1)
			temp = (long long) n % 10;
		
		else
			temp = (long long)(n / pow(10, i)) % 10;
		
	    if (startfrom == 1)
	    {
			temp *= 2;
			if (temp > 9)	//if temp is two digit
				sum += 1;	
			temp %= 10;					
		}  
		sum += temp;
  }
  return sum;
}
