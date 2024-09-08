#include <stdio.h>
#include <stdlib.h>

void sort_requests(int requests[], int n)
{
    // Sort the request array using bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void C_LOOK(int requests[], int n, int head, int is_top_bottom)
{
    int total_head_movement = 0;
    int sorted_requests[n];
    
    // Copy and sort the requests
    for (int i = 0; i < n; i++)
        sorted_requests[i] = requests[i];
    sort_requests(sorted_requests, n);

    // Display the initial head position
    printf("\nInitial Head Position: %d\n", head);
    if (is_top_bottom)
        printf("Disk Head Movement Sequence (Top-Bottom C-LOOK Approach):\n");
    else
        printf("Disk Head Movement Sequence (Bottom-Top C-LOOK Approach):\n");

    // Find the position of the head in the sorted array
    int start_index = 0;
    for (int i = 0; i < n; i++)
    {
        if (sorted_requests[i] >= head)
        {
            start_index = i;
            break;
        }
    }

    // Depending on the direction, handle head movement
    if (is_top_bottom)
    {
        // Move Upwards (Top-Down)
        for (int i = start_index; i < n; i++)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }

        // Jump to the lowest unserviced request
        if (start_index > 0)
        {
            printf("%d -> %d (Jump)\n", head, sorted_requests[0]);
            total_head_movement += abs(head - sorted_requests[0]);
            head = sorted_requests[0];

            // Continue moving Upwards from the lowest request
            for (int i = 0; i < start_index; i++)
            {
                printf("%d -> %d\n", head, sorted_requests[i]);
                total_head_movement += abs(sorted_requests[i] - head);
                head = sorted_requests[i];
            }
        }
    }
    else
    {
        // Move Downwards (Bottom-Up)
        for (int i = start_index - 1; i >= 0; i--)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }

        // Jump to the highest unserviced request
        if (start_index < n)
        {
            printf("%d -> %d (Jump)\n", head, sorted_requests[n - 1]);
            total_head_movement += abs(head - sorted_requests[n - 1]);
            head = sorted_requests[n - 1];

            // Continue moving Downwards from the highest request
            for (int i = n - 2; i >= start_index; i--)
            {
                printf("%d -> %d\n", head, sorted_requests[i]);
                total_head_movement += abs(sorted_requests[i] - head);
                head = sorted_requests[i];
            }
        }
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks (%s C-LOOK): %d\n",
           is_top_bottom ? "Top-Bottom" : "Bottom-Top", total_head_movement);
}

int main()
{
    // Self-initialized values for disk requests and head position
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64}; // Disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);       // Number of disk requests
    int head = 50;

    // Run C-LOOK Disk Scheduling Algorithm (Top-Bottom approach)
    C_LOOK(requests, n, head, 1);  // 1 for Top-Bottom

    // Run C-LOOK Disk Scheduling Algorithm (Bottom-Top approach)
    C_LOOK(requests, n, head, 0);  // 0 for Bottom-Top

    return 0;
}
