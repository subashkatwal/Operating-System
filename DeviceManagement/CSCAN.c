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

void C_SCAN(int requests[], int n, int head, int disk_size, int is_top_bottom)
{
    int total_head_movement = 0;
    int sorted_requests[n + 2]; // Include 2 more for the boundary points (0 and disk_size - 1)

    // Copy the requests and add the boundary points (0 and disk_size - 1)
    for (int i = 0; i < n; i++)
        sorted_requests[i] = requests[i];
    sorted_requests[n] = 0;                 // Add the lowest track (0)
    sorted_requests[n + 1] = disk_size - 1; // Add the highest track (disk_size - 1)

    // Sort the request array along with boundary points
    sort_requests(sorted_requests, n + 2);

    // Display the initial head position
    printf("\nInitial Head Position: %d\n", head);
    printf("Disk Head Movement Sequence (%s C-SCAN Approach):\n", is_top_bottom ? "Top-Bottom" : "Bottom-Top");

    // Find the position of the head in the sorted array
    int start_index = 0;
    for (int i = 0; i < n + 2; i++)
    {
        if (sorted_requests[i] >= head)
        {
            start_index = i;
            break;
        }
    }

    if (is_top_bottom)
    {
        // Move Upwards (Top-Down)
        for (int i = start_index; i < n + 2; i++)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }

        // Jump from the highest track to the lowest track (Circular behavior)
        if (head != 0)
        {
            printf("%d -> 0 (Jump)\n", head);
            total_head_movement += abs(head - 0);
            head = 0;
        }

        // Move Upwards again from the lowest track
        for (int i = 0; i < start_index; i++)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
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

        // Jump from the lowest track to the highest track (Circular behavior)
        if (head != disk_size - 1)
        {
            printf("%d -> %d (Jump)\n", head, disk_size - 1);
            total_head_movement += abs(head - (disk_size - 1));
            head = disk_size - 1;
        }

        // Move Downwards again from the highest track
        for (int i = n + 1; i >= start_index; i--)
        {
            printf("%d -> %d\n", head, sorted_requests[i]);
            total_head_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
        }
    }

    // Display the total head movement
    printf("Total Distance Covered in Tracks (%s C-SCAN): %d\n", 
           is_top_bottom ? "Top-Bottom" : "Bottom-Top", total_head_movement);
}

int main()
{
    // Self-initialized values for disk requests and head position
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64}; // Disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);       // Number of disk requests
    int head = 50; // Initial position of the disk head
    int disk_size = 200; // Size of the disk (number of tracks)

    // Run C-SCAN Disk Scheduling Algorithm (Top-Bottom approach)
    C_SCAN(requests, n, head, disk_size, 1); // 1 for Top-Bottom

    // Run C-SCAN Disk Scheduling Algorithm (Bottom-Top approach)
    C_SCAN(requests, n, head, disk_size, 0); // 0 for Bottom-Top

    return 0;
}
