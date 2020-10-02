cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philosophers
        philo_one/philo_one.c philo_one/philo_one.h philo_one/utils.c philo_one/set_arg.c philo_one/main_thread.c)
