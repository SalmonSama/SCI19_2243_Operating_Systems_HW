#include <stdio.h>

// ฟังก์ชันสำหรับรับข้อมูลจำนวนโปรเซสและ Burst Time
void input(int* total_process, float burst_time[]) {
    int count;

    // ถามจำนวนโปรเซสทั้งหมด
    printf("Enter The Number of Processes To Execute:\t");
    // (1) รับค่าจำนวนโปรเซสจากผู้ใช้
    scanf("%d", total_process);

    // ถาม Burst Time ของแต่ละโปรเซส
    printf("\nEnter The Burst Time of Processes:\n\n");
    for (count = 0; count < *total_process; count++) {
        printf("Process [%d]: ", count + 1);
        scanf("%f", &burst_time[count]);
    }
}

// ฟังก์ชันสำหรับคำนวณ Waiting Time ของแต่ละโปรเซส
void calculateWaitingTime(int total_process, float burst_time[], float waiting_time[]) {
    int count, j;

    // Waiting time ของโปรเซสแรกสุดคือ 0
    waiting_time[0] = 0;

    // คำนวณ waiting time
    // (2) วนลูปสำหรับทุกโปรเซส (เริ่มจากตัวที่สอง)
    for (count = 1; count < total_process; count++) {
        // (3) กำหนดค่าเริ่มต้น waiting time ของโปรเซสปัจจุบันเป็น 0
        waiting_time[count] = 0;
        // (4) วนลูปเพื่อรวม Burst Time ของโปรเซสก่อนหน้าทั้งหมด
        for (j = 0; j < count; j++) {
            // (5) คำนวณ Waiting Time ของโปรเซสปัจจุบัน
            waiting_time[count] += burst_time[j];
        }
    }
}

// ฟังก์ชันสำหรับคำนวณ Turnaround Time ของแต่ละโปรเซส
void calculateTurnaroundTime(int total_process, float burst_time[], float waiting_time[], float turnaround_time[]) {
    int count;
    for (count = 0; count < total_process; count++) {
        turnaround_time[count] = burst_time[count] + waiting_time[count];
    }
}

// ฟังก์ชันสำหรับแสดงผลลัพธ์
void displayResults(int total_process, float burst_time[], float waiting_time[], float turnaround_time[]) {
    int count;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float avg_waiting_time, avg_turnaround_time;

    printf("\n\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (count = 0; count < total_process; count++) {
        total_waiting_time += waiting_time[count];
        total_turnaround_time += turnaround_time[count];
        printf("P[%d]\t\t%.2f\t\t%.2f\t\t%.2f\n", count + 1, burst_time[count], waiting_time[count], turnaround_time[count]);
    }

    avg_waiting_time = total_waiting_time / total_process;
    avg_turnaround_time = total_turnaround_time / total_process;

    printf("\n\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int total_process;
    // สมมติว่ารองรับโปรเซสสูงสุด 20 ตัว
    float burst_time[20], waiting_time[20], turnaround_time[20];

    // เรียกฟังก์ชันเพื่อรับข้อมูล
    input(&total_process, burst_time);

    // เรียกฟังก์ชันเพื่อคำนวณ Waiting Time
    calculateWaitingTime(total_process, burst_time, waiting_time);

    // เรียกฟังก์ชันเพื่อคำนวณ Turnaround Time
    calculateTurnaroundTime(total_process, burst_time, waiting_time, turnaround_time);

    // เรียกฟังก์ชันเพื่อแสดงผล
    displayResults(total_process, burst_time, waiting_time, turnaround_time);

    return 0;
}