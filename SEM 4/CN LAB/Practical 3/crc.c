#include<stdio.h>  
#include<math.h>  
#include<string.h>  


int Decimal_to_Binary(int decimal)  
{  
    // binary value  
    long int binary = 0;  
    // counter  
    int count = 0;  
    // remainder variable  
    int rem=0;   
    while (decimal != 0) {  

        rem = decimal % 2;  
        
        long int tmp = pow(10, count);  
         
        binary += rem * tmp;  
        
        decimal /= 2;  
        
        count++;  
    }  
    return binary;  
}  
   
long int Binary_to_Decimal(char binary[]){  
    long int decimal = 0;  
    
    for (int i=0; i<strlen(binary); i++){  
        if (binary[i]=='1')  
            decimal += 1 << (strlen(binary) - i - 1);  
    }  
    return decimal;  
}  
   
void CRC(char data[], char gen_poly[]){  
    
    int length_gen = strlen(gen_poly);  

    long int generator_dec = Binary_to_Decimal(gen_poly);  
    
    long int dataDecimal = Binary_to_Decimal(data);  

    long int dividend = dataDecimal << (length_gen-1);   

    int shift_bits = (int) ceill(log2l(dividend+1)) - length_gen;   

    long int check_value;  
    // loop to find the check_value or CRC  
    while ((dividend >= generator_dec) || (shift_bits >= 0)){  

        // perform XOR with the generator polynomial  
        check_value = (dividend >> shift_bits) ^ generator_dec;    
        
        dividend = (dividend & ((1 << shift_bits) - 1)) | (check_value << shift_bits);  
        // compute the number of bits to shift again  
        shift_bits = (int) ceill(log2l(dividend + 1)) - length_gen;  
    }  
    // append the check value with the data  
    long int final_data = (dataDecimal << (length_gen - 1)) | dividend;  

    
    // print the results
    printf("Check value or CRC: %d\n",Decimal_to_Binary(dividend));  
    printf("Data to be sent:  %d",Decimal_to_Binary(final_data));  
}  
   
int main(){  
    // Get the data  
    char dataword[20];  
    printf("Enter the data to be transmitted: ");  
    scanf("%s", dataword);  

    // Get the generator polynomial  
    char generator[20];  
    printf("\nEnter the generator polynomial: ");      
    scanf("%s",generator);  
    // Calong intng the CRC function  
    CRC(dataword, generator);  
    return 0;  
}
