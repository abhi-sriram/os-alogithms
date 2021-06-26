// SJF - shortest job first
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

	for(int i=0;i<no_of_process;i++){
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
		printf("time %d\n",t);
		int currentProcess = -1; //  dummy variable to get the process index

		if(p[index].AT>t){
			delay(p[index].AT-t,-1);
			continue;
		}
		
		for(int i=0;i<no_of_process;i++){
			if(p[i].CT==0){ // checking if process completed or not
				if(p[i].AT<=t){ // checking if arrival time of process is less than t (running time of program)
					if(currentProcess!=-1){ // if current process is not -1, then already some process is selected, then we need to check thier burst time.
						if(p[i].BT<p[currentProcess].BT){
							currentProcess = i;
						}
						if(p[i].BT==p[currentProcess].BT){
							if(p[i].AT<p[currentProcess].AT){
								currentProcess = i;
							}
						}
					}else{
						currentProcess = i;
					}
					
				}
			}
		}
		delay(p[currentProcess].BT,p[currentProcess].PID);
		p[currentProcess].CT = t;
		p[currentProcess].TAT = p[currentProcess].CT-p[currentProcess].AT;
		p[currentProcess].WT = p[currentProcess].TAT-p[currentProcess].BT;
		index++;
	}
	
	printf("PID  AT   BT   CT   TAT   WT   RT\n");
	for(int i=0;i<no_of_process;i++){
		printf("%d    %d    %d    %d    %d    %d    %d\n",p[i].PID,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT,p[i].RT);
	}
	
	float avgTAT,avgWT;
	int tat,wt;
	for(int i=0;i<no_of_process;i++){
		tat += p[i].TAT;
		wt += p[i].WT;
	}
	avgTAT = (tat/no_of_process);
	avgWT = (wt/no_of_process);
	
	printf("Average TAT: %.2f\n",avgTAT);
	printf("Average WT : %.2f\n",avgWT);
	
	
}
