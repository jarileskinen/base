function u64
get_time_of_day_us() {
    timespec time_record;
    clock_gettime(CLOCK_REALTIME, &time_record);
    u64 microseconds = 1000000L * time_record.tv_sec + time_record.tv_nsec / 1000;
    return microseconds;
}

function u64
get_time_us() {
    timespec time_record;
    clock_gettime(CLOCK_MONOTONIC, &time_record);
    u64 microseconds = 1000000L * time_record.tv_sec + time_record.tv_nsec / 1000;
    return microseconds;
}