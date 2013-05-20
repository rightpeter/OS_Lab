 #include "ipc.h"

int main(int argc,char *argv[])

{

int rate;


if(argv[1] != NULL) rate = atoi(argv[1]);

else rate = 3; 

buff_key = 101;

buff_num = 3;

pput_key = 102;

pput_num = 1; 

shm_flg = IPC_CREAT | 0644;

buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);

pput_ptr = (int *)set_shm(pput_key,pput_num,shm_flg);

prod_key = 201;

pmtx_key = 202;

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

pmtx_sem = set_sem(pmtx_key,sem_val,sem_flg);

int pid;

int i;

pid = fork();

if(pid == 0) {

    while(1){

        int r = rand() % 3;

        if(r == 0) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr + 1] = 'P';

            buff_ptr[*pput_ptr + 2] = 'G';

            sleep(rate);

            printf("%d provide：paper %c, glue %c\n",getpid(),buff_ptr[*pput_ptr + 1] ,buff_ptr[*pput_ptr + 2]);

            up(pmtx_sem);

            up(c_PG_sem);

        } else if(r == 1) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr] = 'T';

            buff_ptr[*pput_ptr + 2] = 'G';

            sleep(rate);

            printf("%d provide：tobacco %c, glue %c\n",getpid(),buff_ptr[*pput_ptr] ,buff_ptr[*pput_ptr + 2]);

            up(pmtx_sem);

            up(c_TG_sem);

        } else if(r == 2) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr + 1] = 'P';

            buff_ptr[*pput_ptr] = 'T';

            sleep(rate);

            printf("%d provide： tobacco %c, paper %c\n",getpid(),buff_ptr[*pput_ptr] ,buff_ptr[*pput_ptr + 1]);

            up(pmtx_sem);

            up(c_TP_sem);

        }

    }

} else {

    while(1){

        int r = rand() % 3;

        if(r == 0) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr + 1] = 'P';

            buff_ptr[*pput_ptr + 2] = 'G';

            sleep(rate);

            printf("%d provide： paper %c, glue %c\n",getpid(),buff_ptr[*pput_ptr + 1] ,buff_ptr[*pput_ptr + 2]);

            up(pmtx_sem);

            up(c_PG_sem);

        } else if(r == 1) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr] = 'T';

            buff_ptr[*pput_ptr + 2] = 'G';

            sleep(rate);

            printf("%d provide：tobacco %c, glue %c\n",getpid(),buff_ptr[*pput_ptr] ,buff_ptr[*pput_ptr + 2]);

            up(pmtx_sem);

            up(c_TG_sem);

        } else if(r == 2) {

             down(prod_sem);

            down(pmtx_sem);

            buff_ptr[*pput_ptr + 1] = 'P';

            buff_ptr[*pput_ptr] = 'T';

            sleep(rate);

            printf("%d provide: tobacco %c, paper %c\n",getpid(),buff_ptr[*pput_ptr] ,buff_ptr[*pput_ptr + 1]);

            up(pmtx_sem);

            up(c_TP_sem);

        }

    }

}

return EXIT_SUCCESS;

}
