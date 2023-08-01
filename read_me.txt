Checker si valeur plus grand qu'un int(2147483647) et traité comme un argument invalide ou pas

----------------------------------------

WARNING: ThreadSanitizer: data race (pid=18894)
  Read of size 4 at 0x7ffefff1e340 by thread T5 (mutexes: write M7):
    #0 ft_print core/philo_utils.c:23 (philo+0x28ef)
    #1 philo_think core/philo_life.c:21 (philo+0x1ce6)
    #2 philo_sleep core/philo_life.c:62 (philo+0x1fbe)
    #3 philo_life core/philo_life.c:83 (philo+0x20c7)
    #4 routine core/philo_exec.c:33 (philo+0x1620)

  Previous write of size 4 at 0x7ffefff1e340 by thread T1 (mutexes: write M6):
    #0 death_time_check core/time_manager.c:56 (philo+0x331d)
    #1 philo_eat core/philo_life.c:29 (philo+0x1d50)
    #2 philo_life core/philo_life.c:79 (philo+0x2068)
    #3 routine core/philo_exec.c:33 (philo+0x1620)

  Location is stack of main thread.

  Location is global '<null>' at 0x000000000000 ([stack]+0x00000001f340)

  Mutex M7 (0x7ffefff1e3c8) created at:
    #0 pthread_mutex_init ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1227 (libtsan.so.0+0x4bee1)
    #1 init_mutex core/philo_init.c:55 (philo+0x2510)
    #2 init_philo core/philo_init.c:67 (philo+0x257c)
    #3 main core/main.c:21 (philo+0x1459)

  Mutex M6 (0x7ffefff1e378) created at:
    #0 pthread_mutex_init ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1227 (libtsan.so.0+0x4bee1)
    #1 init_mutex core/philo_init.c:53 (philo+0x24ee)
    #2 init_philo core/philo_init.c:67 (philo+0x257c)
    #3 main core/main.c:21 (philo+0x1459)

  Thread T5 (tid=18900, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:969 (libtsan.so.0+0x605b8)
    #1 philosopher core/philo_exec.c:47 (philo+0x16fe)
    #2 main core/main.c:23 (philo+0x1474)

  Thread T1 (tid=18896, finished) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:969 (libtsan.so.0+0x605b8)
    #1 philosopher core/philo_exec.c:47 (philo+0x16fe)
    #2 main core/main.c:23 (philo+0x1474)