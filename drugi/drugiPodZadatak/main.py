
#bal counters
anomalies = 0
checks = 0

# Function to process the file
def process_file(filename):
    global anomalies, checks

        # Open the file for reading
     with open(filename, 'r') as file:
     lines = file.readlines()

                            # Loop through lines in pairs (two lines at a time)
     for i in range(0, len(lines) - 1, 2):
        checks += 1  # Increment the check counter

                                                                # Strip any surrounding whitespace
        first_line = lines[i].strip().split()
        second_line = lines[i+1].strip().split()

                                                                                                    # Check if the first word of the first line is "Dijete" and the second word of the second line is "Roditelj"
        if len(first_line) >= 1 and first_line[0] != "Dijete":
                                                                                                                                anomalies += 1  # Increment anomalies if first word is not "Dijete"
                                                                                                                            if len(second_line) >= 2 and second_line[1] != "Roditelj":
                                                                                                                                anomalies += 1  # Increment anomalies if second word is not "Roditelj"

                                                                                                                                                                        # Print results
                                                                                                                        print(f"Total checks: {checks}")
                                                                                                                        print(f"Anomalies found: {anomalies}")

# Call the function with your file
process_file('file.txt')

