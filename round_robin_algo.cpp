// Round Robin - RR

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

	int TQ = 2; //TQ - Time Quantum

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
	int r=1;
	struct Process * readyQueue[50];
	readyQueue[0] = &p[0];
	if(p[0].AT>0){
		t = p[0].AT;
	}

	while(processChecker(p,no_of_process)){

		struct Process *deqP = readyQueue[0];
		r--;
		for(int i=0;i<r;i++){
			readyQueue[i] = readyQueue[i+1];
		}
		if(deqP->CFT==-1){
			deqP->CFT = t;
		}
		if(deqP->NBT>TQ){
			delay(TQ,deqP->PID);
			deqP->NBT = deqP->NBT-TQ;
		}else{
			delay(deqP->NBT,deqP->PID);
			deqP->NBT=0;
		}
		int flag;
		
		for(int i=0;i<no_of_process;i++){
			flag=-1;
			for(int j=0;j<r;j++){
				if(readyQueue[j]->PID==p[i].PID){
					flag = 1;
					break;
				}
			}
			if(flag==-1){
				if(p[i].NBT>0 && p[i].PID!=deqP->PID && p[i].AT<=t){
				readyQueue[r] = &p[i];
				r++;
				}
			}
			
		}
		
		if(deqP->NBT>0){
			printf("PID %d is in context switching stage\n",deqP->PID);
			readyQueue[r] = deqP;
			r++;
			
		}else{
			deqP->CT = t;
			deqP->TAT = deqP->CT-deqP->AT;
			deqP->WT = deqP->TAT-deqP->BT;
			deqP->RT = deqP->CFT-deqP->AT;
//			index++;
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

