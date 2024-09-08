#include <stdio.h>
#include <stdlib.h>

void SCAN(int requests[], int n, int head, int disk_size, int direction) {
    int total_head_movement = 0, i, j, sorted_requests[n + 2];

    // Copy requests and add boundary points
    for (i = 0; i < n; i++) sorted_requests[i] = requests[i];
    sorted_requests[n] = 0;
    sorted_requests[n + 1] = disk_size - 1;

    // Sort the requests
    for (i = 0; i < n + 2; i++)
        for (j = i + 1; j < n + 2; j++)
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }

    // Display initial head position
    printf("\nInitial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence:\n");

    // Find the head position in the sorted array
    int start_index = 0;
    for (i = 0; i < n + 2; i++)
        if (sorted_requests[i] >= head) {
            start_index = i;
            break;
        }

    // SCAN movement: Top-Bottom or Bottom-Top based on direction
    if (direction == 1) { // Top-Bottom
        for (i = start_index; i < n + 2; i++) {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
        for (i = start_index - 1; i >= 0; i--) {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    } else { // Bottom-Top
        for (i = start_index - 1; i >= 0; i--) {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
        for (i = start_index; i < n + 2; i++) {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    }

    // Display total head movement
    printf("Total Distance Covered in Tracks: %d\n", total_head_movement);
}

int main() {
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50, disk_size = 200;

    // Run SCAN Disk Scheduling (Top-Bottom and Bottom-Top)
    SCAN(requests, n, head, disk_size, 1); // Top-Bottom
    SCAN(requests, n, head, disk_size, 0); // Bottom-Top

    return 0;
}
  