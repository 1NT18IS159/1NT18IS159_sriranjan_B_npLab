#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include<math.h>

char msg[50], poly_div[50], code[50];
int msg_len, poly_len;

void XOR(int i) {
  if (code[i] == poly_div[i])
    code[i] = '0';
  else
    code[i] = '1';
}

void CRC() {
  int i, j;

  for (i = 0; i < poly_len; i++) {
    code[i] = msg[i];
  }
    
  do { 
    if (code[0] == '1') {
      for (j = 1; j < poly_len; j++) {
        XOR(j);
      }
    }

    for (j = 0; j < poly_len - 1; j++)
      code[j] = code[j + 1];

    code[j] = msg[i++];
  } while (i <= msg_len + poly_len - 1);
}

int main(void) {
  int i;
  printf("Enter the message: ");
  scanf("%s", msg);
    
  printf("Enter the polynomial : ");
  scanf("%s", poly_div);
    
  
  msg_len = strlen(msg);
  poly_len = strlen(poly_div);
    
  
  for(i = msg_len; i < msg_len + poly_len - 1; i++)
    msg[i] = '0';
  
  CRC();

  // int appended_bits = 0;
  int code_len = strlen(code);
  // for(i = code_len - 1; i >= 0; i--) {
  //   //appended_bits += (int)(code[i] - '0') * (int)(pow(10, i-code_len));
  //   //printf("%c\n", code[i]);
  // }
  int flag = 0;
  for(i=0;i<code_len;i++) {
    if(code[i] == '0')
      continue;
    else if (code[i] == '1') {
      flag = 1;
      printf("Error in the msg!\n");
      break;
    }
    // printf("%c", code[i]);
    // printf("\n");
  }
  if (!flag)
    printf("The msg is error free!\n");
}