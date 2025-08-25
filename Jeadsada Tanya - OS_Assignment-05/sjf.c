#include <stdio.h>

// กำหนดจำนวนโปรเซสสูงสุด
#define MAX_PROCESS 10

// --- ต้นแบบฟังก์ชัน (Function Prototypes) ---
// ประกาศเพื่อให้ main รู้จักฟังก์ชันเหล่านี้ก่อน
void input(int* total_process, int burst_time[], int arrival_time[], int temp[]);
void calculateAndDisplay(int total_process, int burst_time[], int arrival_time[], int temp[]);


// --- ฟังก์ชันหลัก (Main Function) ---
int main() {
    int total_process;
    int burst_time[MAX_PROCESS], arrival_time[MAX_PROCESS], temp[MAX_PROCESS];
    
    // 1. เรียกฟังก์ชันเพื่อรับข้อมูลจากผู้ใช้
    input(&total_process, burst_time, arrival_time, temp);
    
    // 2. เรียกฟังก์ชันเพื่อคำนวณและแสดงผล
    calculateAndDisplay(total_process, burst_time, arrival_time, temp);
    
    return 0;
}


// --- ฟังก์ชันรับข้อมูล (Input Function) ---
void input(int* total_process, int burst_time[], int arrival_time[], int temp[]) {
    int i;
    printf("\nEnter the Total Number of Processes:\t");
    scanf("%d", total_process);
    
    printf("\nEnter Details of %d Processes\n", *total_process);
    for(i = 0; i < *total_process; i++) {
        printf("\nEnter Arrival Time:\t");
        scanf("%d", &arrival_time[i]);
        printf("Enter Burst Time:\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i]; // เก็บค่า Burst Time เริ่มต้นไว้
    }
}


// --- ฟังก์ชันคำนวณและแสดงผล (Calculation and Display Function) ---
void calculateAndDisplay(int total_process, int burst_time[], int arrival_time[], int temp[]) {
    int i, smallest, count = 0, curr_time;
    double total_wait_time = 0, total_turnaround_time = 0, end;
    
    // กำหนดค่า burst_time ของโปรเซสตัวหลอกให้มีค่าเยอะๆ เพื่อให้การเปรียบเทียบครั้งแรกทำงานถูกต้อง
    burst_time[MAX_PROCESS-1] = 9999;
    
    // วนลูปไปเรื่อยๆ ตามเวลา จนกว่าทุกโปรเซสจะทำงานเสร็จ (count == total_process)
    for(curr_time = 0; count != total_process; curr_time++) {
        smallest = MAX_PROCESS - 1;
        for(i = 0; i < total_process; i++) {
            // เงื่อนไข: หาโปรเซสที่ (1)มาถึงแล้ว (2)เวลาทำงานสั้นที่สุด และ (3)ยังทำงานไม่เสร็จ
            if(arrival_time[i] <= curr_time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0) {
                smallest = i;
            }
        }
        
        // ลดเวลาทำงานของโปรเซสที่สั้นที่สุดลง 1 หน่วย
        burst_time[smallest]--;
        
        // ถ้าโปรเซสทำงานเสร็จ (burst_time เป็น 0)
        if(burst_time[smallest] == 0) {
            count++;
            end = curr_time + 1; // เวลาที่ทำงานเสร็จ
            
            // คำนวณ Waiting Time และ Turnaround Time
            double turnaround_for_process = end - arrival_time[smallest];
            double waiting_for_process = turnaround_for_process - temp[smallest];
            
            // บวกค่าสะสมเพื่อหาค่าเฉลี่ย
            total_wait_time += waiting_for_process;
            total_turnaround_time += turnaround_for_process;
        }
    }
    
    // แสดงผลลัพธ์ค่าเฉลี่ย
    printf("\n\nAverage Waiting Time = %.2f\n", total_wait_time / total_process);
    printf("Average Turnaround Time = %.2f\n", total_turnaround_time / total_process);
}