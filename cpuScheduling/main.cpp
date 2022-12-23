/*
----------------------------------------------------------------------------
Simulate CPU scheduling algorithms by generating a set of statistics
and printing their values to stdout. (In this project it is first come/serve

Ex input format:
P                               //processes available
p N                             //execution elements and instruction lines
<pid> <burst> <priority>
<pid> <burst> <priority>
...

Outputs to format:
<voluntary context switch>
<non-voluntary context switch>
<CPU Utilization>
<Δ Throughput>
<Δ turnaround time>
<Δ waiting time>
<Δ response time>
----------------------------------------------------------------------------
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Q {
    int data[3];
};

void calcStats(struct Q * queue, int P, int p, int N)
{
    int vcSwitch = 1;    //total v switches
    int nvcSwitch = 0;   //total nv switches
    double thrupt = 0;
    double trnrnd = 0;
    double wtng = 0;
    double rspns = 0;

//finding voluntary and nonvoluntary context switches
    for (int i = 1; i < N; i++) {
        if ((queue[i-1]).data[0] != (queue[i]).data[0]) {
            for (int j = i-1; j >=0; j--) {
                if ((queue[j]).data[0] == (queue[i]).data[0]) {     //checks for nonVoluntar>
                    for (int q = i-1; q >= 0; q--) {
                        wtng += (queue[q]).data[1];
                    }

                    nvcSwitch++;
                    break;
                }
            }
        }

        for (int h = i-1; h >=0; h--) {

            if ((queue[h]).data[0] == (queue[i]).data[0]) {       //checks for voluntary s>
                break;
            }
            if (h == 0) {
                vcSwitch++;
            }
        }
    }

//finding Throughput, turnaround time,response
    for (int x = 0; x < N; x++) {
        thrupt += (queue[x]).data[1];
        trnrnd += (queue[x]).data[1];

        if(x > 0) {
            if ((queue[x]).data[0] != (queue[x-1]).data[0]) {
                for (int m = x-1; m >=0; m--) {
                    trnrnd += (queue[m]).data[1];
                    rspns += (queue[m]).data[1];
                }
            }
        }
    }

    wtng = wtng + rspns;
    wtng = wtng/vcSwitch;
    thrupt = p/thrupt;
    trnrnd = trnrnd/vcSwitch;
    rspns = rspns/vcSwitch;

//outputs for the Simulation and Statistics
    printf("%d\n", vcSwitch);
    printf("%d\n", nvcSwitch);
    printf("100.00\n");
    printf("%.2f\n", thrupt);
    printf("%.2f\n", trnrnd);
    printf("%.2f\n", wtng);
    printf("%.2f\n", rspns);
}


int main(int argc, char *argv[])
{

    int x, y, z;    //Processes, execution elements available to the system

//uses read in case user chooses to input as file through the arg
    if (argc > 1) {


    }

//uses scanf in case user chooses to cat the input
    else {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &z);

        struct  Q  q[z];

        for (int t = 0; t < z; t++) {
            scanf("%d", &(q[t]).data[0]);
            scanf("%d", &(q[t]).data[1]);
            scanf("%d", &(q[t]).data[2]);

        }

        calcStats(q, x, y, z);
    }
    return 0;
}
