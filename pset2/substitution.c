#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h> 

bool check_key(char key[]);
void encipher(char key[], char plaintext[]);

int main(void)
{
	char key[] = "VCHPRZGJNTLSKFBDQWAXEUYMOI" , plaintext[] = "hello, world";

	//check key
	if (!check_key(key))
	{
		return 1;
	}

	//encipher key
	encipher(key, plaintext);
}

bool check_key(char key[])
{
	int len = strlen(key);
	//if key is short	
	if(len != 26)
	{
		printf("Key must contain 26 characters.\n");
		return false;
	}

	for (int i = 0; i < len; i++)
	{
		//if key contains non alphabetical characters
		if (!isalpha(key[i]))
		{
			printf("Key must only contain alphabetic characters.\n");
			return false;
		}

		//check for upto second last character for repeatation
		if (i != (len-1))
		{
			for (int j = i + 1; j < len; j++)
			{
				//if two character matches
				if(toupper(key[i]) == toupper(key[j]))
				{
					printf("Key must not contain repeated characters.\n");
					return false;
				}	

			}
		}

	}

	//key is valid
	return true;
}

void encipher(char key[], char plaintext[])
{
	int pt_len = strlen(plaintext);
	char ciphertext[pt_len+1];

	for (int i = 0; i < pt_len; ++i)
	{
		//if character isn't an alphabet
		if(!isalpha(plaintext[i]))
		{
			//copy at is it
			ciphertext[i] = plaintext[i];	
		}

		else
		{
			// if character is uppercase
			if(isupper(plaintext[i]))
			{
				ciphertext[i] = toupper(key[(plaintext[i] - 'A')]);
			}
			
			//else character is lowercase
			else
			{
				ciphertext[i] = tolower(key[(plaintext[i] - 'a')]);
			}
		}

	}
	ciphertext[pt_len] = '\0';

	printf("plaintext: %s\nciphertext: %s\n", plaintext,ciphertext);
}