// FCFS - first come first served

#include<stdio.h>
#include<time.h>

int t = 0; // program execution time in sec;

struct Process{
	int PID,AT,BT,CT,TAT,WT,RT;
};


void delay(int sec,int pid){
	int ms = sec*1000;
	if(pid!=-1){
		printf("Process with PID: ");
		printf("%d ",pid);
		printf("is running\n");
	}else{
		printf("CPU is idle\n");
	}
	
	clock_t start_time = clock();
	while(clock()<start_time+ms);
	t = t+sec;
}




int main(){
	int index=0;
	int no_of_process = 4;
	struct Process p[no_of_process];
	for(int i=0;i<4;i++){
		printf("Enter process arrival time: ");
		scanf("%d",&p[i].AT);
		printf("Enter process burst time: ");
		scanf("%d",&p[i].BT);
		p[i].PID = i;
		p[i].CT = 0;
		p[i].RT = 0;
		p[i].TAT = 0;
		p[i].WT = 0;
	}
	

	
	while(index<no_of_process){
		if(p[index].AT-t>0){
			delay(p[index].AT-t,-1);
			continue;
		}
		delay(p[index].BT,p[index].PID);	
		p[index].CT = t;
		
		p[index].TAT = p[index].CT-p[index].AT;
		p[index].WT = p[index].TAT-p[index].BT;
		p[index].RT = p[index].TAT-p[index].BT;
		index++;

	}
	printf("PID  AT   BT   CT   TAT   WT   RT\n");
	for(int i=0;i<4;i++){
		printf("%d    %d    %d    %d    %d    %d    %d\n",p[i].PID,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT,p[i].RT);
	}
	
}
