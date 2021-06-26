// SRJF - shortest remaining job first (or) SJF with preemptive
#include<stdio.h>
#include<time.h>
int t = 0; // program execution time in sec;

struct Process{
	int PID,AT,BT,NBT,CT,TAT,WT,RT,CFT; 
	// NBT - New Best Time
	// CFT - CPU First Time
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

bool processChecker(struct Process *p,int len){
	for(int i=0;i<len;i++){
		if(p[i].NBT>0){
			return true;
		}
	}
	return false;
}

int main(){
	int index=0;
	int no_of_process = 4;
	struct Process p[no_of_process];
	int bt;
	


	for(int i=0;i<no_of_process;i++){
		printf("Enter process arrival time: ");
		scanf("%d",&p[i].AT);
		printf("Enter process burst time: ");
		scanf("%d",&bt);
		p[i].BT = bt;
		p[i].NBT = bt;
		p[i].CFT = -1;
		p[i].PID = i+1;
		p[i].CT = 0;
		p[i].RT = 0;
		p[i].TAT = 0;
		p[i].WT = 0;
	}
	
	while(processChecker(p,no_of_process)){
		
		if(p[index].AT>0){
			delay(p[index].AT,-1);
			continue;
		}
		int currentProcess = -1; 
		for(int i=0;i<no_of_process;i++){
			if(p[i].NBT!=0){ // checking if process completed or not
				if(p[i].AT<=t){ // checking if arrival time of process is less than t (running time of program)
					if(currentProcess!=-1){ // if current process is not -1, then already some process is selected, then we need to check thier burst time.
						if(p[i].NBT<p[currentProcess].NBT){
							currentProcess = i;
						}
						if(p[i].NBT==p[currentProcess].NBT){
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
	
		if(p[currentProcess].CFT==-1){
			p[currentProcess].CFT = t;
		}
		delay(1,p[currentProcess].PID);
		if(p[currentProcess].NBT==1){
			p[currentProcess].NBT = 0;
			p[currentProcess].CT = t;
			p[currentProcess].TAT = p[currentProcess].CT-p[currentProcess].AT;
			p[currentProcess].WT = p[currentProcess].TAT-p[currentProcess].BT;
			p[currentProcess].RT = p[currentProcess].CFT-p[currentProcess].AT;
			
		}else{
			p[currentProcess].NBT = p[currentProcess].NBT-1;
		}

		
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
