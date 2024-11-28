#include <lib/stdlib.h>
#include <lib/string.h>


char num_a[20];
char* itoa(long long num){

		if(num == 0){
			num_a[0] = '0';
			num_a[1] = '\0';
			return num_a;
		}

	    int digits = 0;
	    int temp = num;
	    while(temp > 0){
	        digits++;
	        temp/=10;
	    }

	    for(int i=0;i<digits;i++){
	        num_a[digits-i-1] = '0' + num%10;
	        num/=10;
	    }
		num_a[digits] = '\0';
	    return num_a;
	
}

int stoi(char* str){
	int n = strlen(str);
	int val = 0;
	for(int i=0;i<n;i++){
		val *= 10;
		val += str[i] - '0';
	}

	return val;
}
