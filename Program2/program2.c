#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void receiver(int*, int);

void main() {
	int data[100], frame[100], frameLen=0, num, i, j=0;
	int count, zerosAdded = 0, zero;
	printf("Enter length: \n");
	scanf("%d", &num);
	printf("Enter data\n");
	for(i = 0; i < num; i++)
		scanf("%d", &data[i]);
		
	// create the initial frame header (first 8 indices)
	frame[j++]=0;
	frame[j++]=1;
	frame[j++]=1;
	frame[j++]=1;
	frame[j++]=1;
	frame[j++]=1;
	frame[j++]=1;
	frame[j++]=0;
	
	//populate the input data into frame buffer
	for(i = 0; i < num; i++) {
		if(data[i] == 0) {
			frame[j] = data[i];
			j++;
			count = 0;
			zero = 1;
		} else {
			if((count == 5) && (zero == 1)) {
				frame[j] = 0;
				j++;
				zerosAdded++;
				frame[j] = data[i];
				j++;
				count = 0;
			}
			else {
				frame[j] = data[i];
				j++;
				count++; 
			}
		}
	}
	// set the end of frame bit from last j'th position
	frame[j++] = 0;
	frame[j++] = 1;
	frame[j++] = 1;
	frame[j++] = 1;
	frame[j++] = 1;
	frame[j++] = 1;
	frame[j++] = 1;
	frame[j++] = 0;
	
	//calculate total frame lenth
	// num of input bits + total lenth of sof and eof headers + number of zero padding
	frameLen = num + 16 + zerosAdded;
	printf("Length of frame which was sent = %d \n",frameLen);
	printf("Error Corrected Frame: "); 
	for(i = 0; i < frameLen; i++)
		printf("%d",frame[i]);
	printf("\n");
	receiver(frame,frameLen);
}

void receiver(int *frame, int len) {
	int i, j, counter, l;
	int recv[100];
	l = len - 8;
	j = 0;
	for(i = 8; i < l; i++) {
		if(frame[i] == 0) {
			if(counter == 5) {
				i++;
				recv[j] = frame[i];
				j++;
				counter = 0;
			} else {
				recv[j] = frame[i];
				j++;
				counter = 0;
			}
		}
		else {
			recv[j] = frame[i];
			j++;
			counter++;
		}
	}
	printf("Received Frame is: ");
	for(i = 0; i < j; i++)
		printf("%d", recv[i]);
	printf("\n");
}
