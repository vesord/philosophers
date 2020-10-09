cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

add_executable(philosophers_1
        philo_one/philo_one.c
        philo_one/philo_one.h
        philo_one/utils.c
        philo_one/set_arg.c
        philo_one/main_thread.c
        philo_one/initialization.c
        philo_one/phil_function.c
        philo_one/philo_thread.c
        philo_one/utils2.c)

add_executable(philosophers_2
        philo_two/philo_two.h
        philo_two/philo_two.c
        philo_two/utils.c
        philo_two/set_arg.c
        philo_two/main_thread.c
        philo_two/initialization.c
        philo_two/phil_function.c
        philo_two/philo_thread.c
        philo_two/utils2.c)

add_executable(philosophers_3
        philo_three/philo_three.h
        philo_three/philo_three.c
        philo_three/utils.c
        philo_three/set_arg.c
        philo_three/main_thread.c
        philo_three/initialization.c
        philo_three/phil_function.c
        philo_three/philo_thread.c
        philo_three/utils2.c)
