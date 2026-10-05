#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1) return 0;
    if (n < 1) return 0;
    if (n > 100) n = 100;

    struct UserAccount accounts[100];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &accounts[i].account_id, &accounts[i].plan_type, &accounts[i].monthly_fee, &accounts[i].remaining_days, &accounts[i].active_devices);
    }

    long long mrr_before = 0;
    for (int i = 0; i < n; i++) {
        if (accounts[i].plan_type > 0) {
            mrr_before += accounts[i].monthly_fee;
        }
    }

    for (int i = 0; i < n; i++) {
        if (accounts[i].remaining_days <= 0) {
            accounts[i].plan_type = 0;
            accounts[i].monthly_fee = 0;
        } else {
            if (accounts[i].plan_type == 0) {
                accounts[i].monthly_fee = 0;
            } else if (accounts[i].plan_type == 1) {
                accounts[i].monthly_fee = 120000;
                if (accounts[i].active_devices > 2) {
                    accounts[i].active_devices = 2;
                }
            } else if (accounts[i].plan_type == 2) {
                accounts[i].monthly_fee = 300000;
                if (accounts[i].active_devices > 5) {
                    accounts[i].active_devices = 5;
                }
            } else {
                accounts[i].plan_type = 0;
                accounts[i].monthly_fee = 0;
            }
        }

        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        if (accounts[i].plan_type == 0) {
            accounts[i].monthly_fee = 0;
            if (accounts[i].active_devices > 1) {
                accounts[i].active_devices = 1;
            }
        }
    }

    struct UserAccount paid_arr[100];
    struct UserAccount free_arr[100];
    int paid_count = 0;
    int free_count = 0;

    for (int i = 0; i < n; i++) {
        if (accounts[i].plan_type > 0) {
            paid_arr[paid_count] = accounts[i];
            paid_count++;
        } else {
            free_arr[free_count] = accounts[i];
            free_count++;
        }
    }

    for (int i = 0; i < paid_count - 1; i++) {
        for (int j = 0; j < paid_count - i - 1; j++) {
            if (paid_arr[j].monthly_fee < paid_arr[j + 1].monthly_fee) {
                struct UserAccount temp = paid_arr[j];
                paid_arr[j] = paid_arr[j + 1];
                paid_arr[j + 1] = temp;
            }
        }
    }

    int idx = 0;
    for (int i = 0; i < paid_count; i++) {
        accounts[idx] = paid_arr[i];
        idx++;
    }
    for (int i = 0; i < free_count; i++) {
        accounts[idx] = free_arr[i];
        idx++;
    }

    long long mrr_after = 0;
    for (int i = 0; i < n; i++) {
        if (accounts[i].plan_type > 0) {
            mrr_after += accounts[i].monthly_fee;
        }
    }

    printf("BAO CAO KIEM TOAN VA TAI CAU TRUC CLOUDSYNC STUDIO\n");
    printf("MRR Truoc khi kiem toan: %lld VND\n", mrr_before);
    printf("MRR Sau khi kiem toan: %lld VND\n", mrr_after);
    printf("Chenh lech doanh thu MRR: %lld VND\n", mrr_after - mrr_before);
    printf("DANH SACH TAI KHOAN SAU KHI CHUAN HOA VA SAP XEP:\n");
    printf("ID | Plan | Monthly Fee | Remaining Days | Active Devices\n");
    for (int i = 0; i < n; i++) {
        printf("%d | %d | %d | %d | %d\n", accounts[i].account_id, accounts[i].plan_type, accounts[i].monthly_fee, accounts[i].remaining_days, accounts[i].active_devices);
    }

    return 0;
}
