 #include "ipc.h"
int main(int argc,char *argv[])
{
	int rate;
	if(argv[1] != NULL) rate = atoi(argv[1]);
	else rate = 3; 

	buff_key = 101;
	buff_num = 3; 
	cget_key = 103; 
	cget_num = 1; 
	shm_flg = IPC_CREAT | 0644; 

	buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);

	cget_ptr = (int *)set_shm(cget_key,cget_num,shm_flg);

	prod_key = 201; 
	cmtx_key = 203; 
	c_PG_key = 301;
	c_TP_key = 302;
	c_TG_key = 303;
	sem_flg = IPC_CREAT | 0644; 

	sem_val = 1;

	prod_sem = set_sem(prod_key,sem_val,sem_flg);

	sem_val = 0;

	c_PG_sem = set_sem(c_PG_key,sem_val,sem_flg);
	c_TP_sem = set_sem(c_TP_key,sem_val,sem_flg);
	c_TG_sem = set_sem(c_TG_key,sem_val,sem_flg);

	sem_val = 1;

	cmtx_sem = set_sem(cmtx_key,sem_val,sem_flg);
	int pid1, pid2;
	pid1 = fork();
	if(pid1 == 0) {
	    while(1){
	        down(c_PG_sem);
	        down(cmtx_sem);

	        sleep(rate);
	        printf("%dsmoker has tobacco T, receive paper %c and glue %c, smoking……\n",
	            getpid(),buff_ptr[*cget_ptr + 1],buff_ptr[*cget_ptr + 2]);

	        up(cmtx_sem);
	        up(prod_sem);
	    }
	} else {
	    pid2 = fork();
	    if(pid2 == 0) {
	        while(1){
	            down(c_TP_sem);
	            down(cmtx_sem);

	            sleep(rate);
	            printf("%d smoker has glue G,receive paper %c and tobacco %c, smoking……\n",
	                getpid(),buff_ptr[*cget_ptr + 1],buff_ptr[*cget_ptr]);

	            up(cmtx_sem);
	            up(prod_sem);
	        }
	    } else {
	        while(1){
	            down(c_TG_sem);
	            down(cmtx_sem);
	            sleep(rate);
	            printf("%d smoker has paper P, receive glue %c and tobacco %c, smoking…\n",
	                getpid(),buff_ptr[*cget_ptr + 2],buff_ptr[*cget_ptr]);
	            up(cmtx_sem);
	            up(prod_sem);
	        }
	        }
	}
	return EXIT_SUCCESS;
}
 
