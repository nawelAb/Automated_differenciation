#!/bin/bash
#@ class            = clallmds
#@ job_name         = RUN_01
#@ total_tasks      = 1
#@ node             = 1
#@ wall_clock_limit = 00:10:00
#@ output           = $(job_name).$(jobid).log
#@ error            = $(job_name).$(jobid).err
#@ job_type         = mpich
#@ queue
#
export OMP_NUM_THREAD=16
module load gnu-env/5.4.0
./build/main
