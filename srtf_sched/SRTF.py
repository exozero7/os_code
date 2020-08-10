#!/usr/bin/python3

# # SRTF (Shortest Remaining Time First) CPU Scheduling Algorithm
# @exozero7
# 04.01.2020

'''
data.txt file format

1st row: Process indexes
2nd row: Arrival times
3rd row: Execution times
'''

# Reading files and saving them to the 2D-list
with open("data.txt", "r") as f:
    data = [[int(x) for x in line.split()] for line in f]
print(data)

f.close()

# Concurrent 2D-list
conc = [[], [], []]

# Time Execution Left list, as copy of 3rd column of data
texecleft = data[2].copy()

# Wait time list (initialized 0)
wait_time = [0]*len(data[0])

# Elapsed time
etime = 0

print("From\tProcess\tTo")
exe = True

# Useful information about the process

current_process_index, current_process_id, current_process_burst_time = -1, -1, -1

# The execution will continue until all processes have finished their individual execution time
while exe:
    
    # Empties the concurrent list to create the new one with processes
    conc.clear()

    for _ in range(3):
        conc.append([]) # Krijon conc[[], [], []]
    
    # Check every process
    for i in data[0]:
        index = data[0].index(i) # Get the index of that process
        
        # Check if the arrival time of this process is less than the elapsed time and the process isn't executed completely 
        if data[1][index] <= etime and texecleft[index] > 0:
            # If the condition is true, then add the process into the concurrent list
            conc[0].append(data[0][index])
            conc[1].append(data[1][index])
            conc[2].append(data[2][index])

    # Next step the process with the least time execution left is found.
    # In order to do that we need to set an initial maximum value.

    current_process_execution_time_left = max(data[2]) + 1

    # Find next process to use
    # Check every process in the concurrent list

    for j in conc[0]:
        # Save the index of that process
        index = data[0].index(j)

        # Check if the time execution left of the process is smaller than the current process selected
        if texecleft[index] < current_process_execution_time_left:
            # If the condition is true, then get every information about the process
            current_process_index = index
            current_process_id = data[0][index]
            current_process_burst_time = data[1][index]
            current_process_execution_time_left = texecleft[index]
        
        # If the time execution time left of the process is equal as the current process selected than between them, 
        # the one with the smallest arrival time would be choosed (FCFS)
        elif texecleft[index] == current_process_execution_time_left:
            if data[1][index] < current_process_burst_time:
                # Get the information again
                current_process_index = index
                current_process_id = data[0][index]
                current_process_burst_time = data[1][index]
                current_process_execution_time_left = texecleft[index]
    
    # Execution time of the selected process is decremented
    texecleft[current_process_index] += -1

    # Print information for the actual step
    print("({})\t{}\t({})".format(etime, current_process_id, etime+1))

    # For every other process (not selected) the wait time is incremented
    
    # Notice: The wait time value doesn't consider the arrival time. The real waiting time is the difference of the
    # wait time value of this list and the arrival time. This changed is made below. 
    
    for p in range(len(data[0])):
        if p == current_process_index or texecleft[p] == 0:
            continue
        wait_time[p] += 1

    # Check if all processes have finished
    if sum(texecleft) == 0:
        exe = False

    # Elapsed time is incremented
    etime += 1

# Prints wait time
print("\n-  WAITING TIME  -")
print("=================")
print("Process\tWaiting time")
for _ in range(len(data[0])):
    # real wait time
    print(data[0][_], "\t", wait_time[_] - data[1][_])
print("\nAverage waiting time: ", (sum(wait_time) - sum(data[1])) / len(wait_time))

# Prints
print("\n-  TURN-AROUND TIME  -")
print("======================")
print("Process\tTurn-Around time")
for _ in range(len(data[0])):
    # turn around time = waiting time + execution time
    print(data[0][_], "\t", wait_time[_] - data[1][_] + data[2][_])    
print("\nAverage turn-around time: ", (sum(wait_time) - sum(data[1]) + sum(data[2])) / len(wait_time))