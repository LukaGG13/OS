#/!bin/bash

FILES=(
    "data/mala.bin"
    "data/srednja.bin"
    "data/velika.bin"
)


N=2
buffer_sizes=(1 512 1024)

mesure_cp() {
    local file="$1"
    local log_file="${file%.*}_result.log"
    > "$log_file"
    echo "Running cp for $log_file" >> "$log_file"
    echo "Running cp for $log_file"
    for i in $(seq 1 $N); do
        echo "Run $i of $N" >> "$log_file"
        real_time=$( (time -p cp "$file" "$file.copy") 2>&1 | grep real | awk '{print $2}')
        echo $real_time >> "$log_file"
    done
}

mesure_fc() {
    local file="$1"
    local log_file="${file%.*}_result.log"
    echo -e "\n\nRunning cfiles for $log_file" >> "$log_file"
    echo "Running fc for $log_file"
    for i in $(seq 1 $N); do
        echo "Run $i of $N" >> "$log_file"
        #for j in 1 512 1024; do
        real_time=$( (time -p /cflies/main "$file" "$file.copy" "1") 2>&1 | grep real | awk '{print $2}')
        echo -n "$real_time" >> "$log_file"
        echo "Full time output: $real_time"
        #real_time=$(echo "1" | time -p cfiles/main "$file" "$file.copy" 2>&1 | grep real | awk '{print $2}')
        #real_time=$( (time -p cfiles/main "$file" "$file.copy" "512") 2>&1 | grep real | awk '{print $2}')
        #echo -n "$real_time" >> "$log_file"
        #real_time=$( (time -p cfiles/main "$file" "$file.copy" "1024") 2>&1 | grep real | awk '{print $2}')
        #echo -n "$real_time" >> "$log_file"
        #done
        echo "" >> "$log_file"
    done
}

for file in "${FILES[@]}" ; do
    mesure_cp "$file"
    mesure_fc "$file"
done
echo "End"
