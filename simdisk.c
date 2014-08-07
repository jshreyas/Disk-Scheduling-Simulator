#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

int number_cyl,first_number,limit,input[10],c=0; //c = total travel 

void help(){
	printf("simdisk [−h] [-n number-of-cylinders] [−d disk-shed-policy] [−i input_file]\n");
	printf("\t-h: help\n");
	printf("\t-n: number of cylinders\n");
	printf("\t-d: disk-shed-policy\n");
	printf("\t-i: input_file\n");
}

void FCFS(){
        int i;
        for(i=0; i<limit-1; i++){
                c=abs(input[i+1]-input[i])+c;
        }
        printf("the sequence of the requests is\n");
        for(i=1; i<limit; i++){
                printf("%d\t",input[i]);
        }
        printf("total travel is %d\n",c);
}

void SSTF(){
        int i,j,temp;
        for(i=0; i<limit; i++){
                for(j=i;j<(limit-1);j++){
                        if(input[i]>input[j+1]){
                                temp=input[i];
                                input[i]=input[j+1];
                                input[j+1]=temp;
                        }
                }
        }
        for(i=0; i<limit-1; i++){
                c=abs(input[i+1]-input[i])+c;
        }
        printf("the sequence of the requests is\n");
        for(i=1; i<limit; i++){
                printf("%d\t",input[i]);
        }
        printf("total travel is %d\n",c);
}

void LOOK(){
        int i,j,temp,index;
        for(i=0; i<limit; i++){
                for(j=i;j<(limit-1);j++){
                        if(input[i]>input[j+1]){
                                temp=input[i];
                                input[i]=input[j+1];
                                input[j+1]=temp;
                        }
                }
        }
        for(i=0; i<limit; i++){
                if(input[i]==first_number){
                        index=i;
                }
        }
        c=input[index];
        for(i=0; i<limit-1; i++){
                if(input[i]>=first_number){
                        c=abs(input[i+1]-input[i])+c;
                }
        }
        if(index!=1){
                c=abs(input[limit-1]-input[index-1])+c;
        }
        for(i=index-1;i>1;i--){
                c=abs(input[i]-input[i-1])+c;
        }
        printf("the sequence of the requests is\n");
        for(i=1; i<limit; i++){
                printf("%d\t",input[i]);
        }
        printf("total travel is %d\n",c);
}

void CSCAN(){
        int i,j,temp,index;
        for(i=0; i<limit; i++){
                for(j=i;j<(limit-1);j++){
                        if(input[i]>input[j+1]){
                                temp=input[i];
                                input[i]=input[j+1];
                                input[j+1]=temp;
                        }
                }
        }
        for(i=0; i<limit; i++){
                if(input[i]==first_number){
                        index=i;
                }
        }
        c=input[index];
        for(i=0; i<limit; i++){
                if(input[i]>=first_number){
                        c=abs(input[i+1]-input[i])+c;
                }
        }
        for(i=0;i<(index-1);i++){
                c=abs(input[i+1]-input[i])+c;
        }
        printf("the sequence of the requests is\n");
        for(i=1; i<limit; i++){
                printf("%d\t",input[i]);
        }
        printf("total travel is %d\n",c);
}

int main(int argc, char *argv[]){

	int i,s,k,sched_policy;
	char ch,file_name[10],number_string[10];
	bool file_flag=0;
	FILE *fp;

	//default initial data
	number_cyl=200;
	sched_policy=0;

	while ((ch = getopt(argc, argv, "hn:d:i:")) != -1) {
	        switch(ch) {
        	case 'n':{
        		number_cyl=atoi(optarg);    
		        printf("Total number of cylinders = %d\n",number_cyl);
			if ((number_cyl < 10) || (number_cyl > 9999)){
                		fprintf(stderr, "Invalid -n option of %d\n", atoi(optarg));
				help();
           			exit(1);
			}
			break;
		}
        	case 'd':{
			if (strcasecmp(optarg, "fcfs") == 0) {
                		sched_policy = 0;
               		}   
			else if (strcasecmp(optarg, "sstf") == 0) {
                		sched_policy = 1;
			}
			else if (strcasecmp(optarg, "look") == 0) {
        	        	sched_policy = 2;
               		}
			else if (strcasecmp(optarg, "cscan") == 0) {
        	        	sched_policy = 3;
               		}
			else {
	                	fprintf(stderr, "Invalid -d option of %s\n", optarg);
                    		help();
                    		exit(1);
                	}
			break;
		}
		case 'i':{
			k=1;
			input[0]=0;	
			strcpy(file_name,optarg);
			file_flag=1;
			fp = fopen(file_name,"r");
			if(!fp){
                                printf("Invalid -i option of %s\n", optarg);
                                exit(1);
                        }
			while(fp && (fgets(number_string,10,fp) != NULL)){
				number_string[strlen(number_string)-1]='\0';
				input[k]=atoi(number_string);
				k++;
			}
			fclose(fp);
			input[k]=number_cyl;
			limit=k;
			first_number=input[1];
			break;
		}
		case 'h':{
       		//default:
        		help();
			exit(1);
		}
		}
	}
	if(!file_flag){
                printf("Enter the I/O request sequence\n");  
		s=1;
		input[0]=0;	
		while(1){
                        scanf("%d",&(input[s]));
                        if(input[s]==-1){
				break;
			}
			s++;
		}
		limit=s;
		input[s]=(number_cyl-1);
		first_number=input[1];
        }

	if(sched_policy==0){
		FCFS();
	}
	if(sched_policy==1){
       		SSTF();
	}
	if(sched_policy==3){
       		CSCAN();
        }
	if(sched_policy==2){
       		LOOK();
	}        
	return 0;
}
