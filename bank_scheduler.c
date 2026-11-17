
#include <stdio.h>

struct Process {
    int id, at, bt, ct, wt, tat;
};

int main() {
    struct Process p[20], temp;
    int n, i, j, time;
    float fcfsWT = 0, sjfWT = 0;
    float fcfsTAT = 0, sjfTAT = 0;
    int done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time and Burst Time: ");
        scanf("%d %d %d", &p[i].id, &p[i].at, &p[i].bt);
    }

    // FCFS Scheduling
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    time = 0;

    printf("\nFCFS Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        time = p[i].ct;

        fcfsWT += p[i].wt;
        fcfsTAT += p[i].tat;

        printf("%d\t%d\t%d\t%d\t%d\n",
        p[i].id, p[i].at, p[i].bt,
        p[i].wt, p[i].tat);
    }

    // SJF Scheduling
    time = 0;

    printf("\nSJF Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        int min = -1;

        for(j = 0; j < n; j++) {
            if(done[j] == 0 && p[j].at <= time) {
                if(min == -1 || p[j].bt < p[min].bt)
                    min = j;
            }
        }

        if(min == -1) {
            time++;
            i--;
            continue;
        }

        p[min].ct = time + p[min].bt;
        p[min].tat = p[min].ct - p[min].at;
        p[min].wt = p[min].tat - p[min].bt;

        time = p[min].ct;
        done[min] = 1;

        sjfWT += p[min].wt;
        sjfTAT += p[min].tat;

        printf("%d\t%d\t%d\t%d\t%d\n",
        p[min].id, p[min].at, p[min].bt,
        p[min].wt, p[min].tat);
    }

    printf("\nFCFS Average WT = %.2f", fcfsWT/n);
    printf("\nFCFS Average TAT = %.2f", fcfsTAT/n);

    printf("\nSJF Average WT = %.2f", sjfWT/n);
    printf("\nSJF Average TAT = %.2f\n", sjfTAT/n);

    if(sjfWT < fcfsWT)
        printf("\nSJF gives better performance.");
    else if(fcfsWT < sjfWT)
        printf("\nFCFS gives better performance.");
    else
        printf("\nBoth algorithms have equal performance.");

    return 0;
}
