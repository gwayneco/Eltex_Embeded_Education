#! /bin/bash
. for_logs.conf

process_pid=$(pgrep $process_name | head -1)
journalctl _PID=$process_pid --since $start_time --until $end_time
