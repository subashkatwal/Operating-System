#include <stdio.h>
#include <stdlib.h>

void LOOK(int requests[], int n, int head, int direction) {
    int total_head_movement = 0, i, j, sorted_requests[n];

    // Copy and sort the requests
    for (i = 0; i < n; i++) sorted_requests[i] = requests[i];
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
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
    for (i = 0; i < n; i++)
        if (sorted_requests[i] >= head) {
            start_index = i;
            break;
        }

    // LOOK movement: Top-Bottom or Bottom-Top based on direction
    if (direction == 1) { // Top-Bottom
        for (i = start_index; i < n; i++) {
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
        for (i = start_index; i < n; i++) {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    }

    // Display total head movement
    printf("Total Distance Covered in Tracks: %d\n", total_head_movement);
}

int main() {
    // Updated example: new disk requests and head position
    int requests[] = {40, 150, 20, 70, 90, 10, 200, 170}; // New disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);       // Number of disk requests
    int head = 100;                                       // New initial head position

    // Run LOOK Disk Scheduling (Top-Bottom and Bottom-Top)
    LOOK(requests, n, head, 1); // Top-Bottom
    LOOK(requests, n, head, 0); // Bottom-Top

    return 0;
}
