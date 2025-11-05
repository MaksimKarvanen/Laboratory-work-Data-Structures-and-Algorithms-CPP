import matplotlib.pyplot as plt

# Ваши данные
sizes = [1000, 2000, 5000, 8000, 10000, 50000, 100000]
selection_times = [3.125, 11.597, 49.737, 89.136, 124.796, 2684.31, 10721]
bubble_times = [7.484, 22.685, 86.425, 191.587, 297.24, 7187.04, 29585.3]
insertion_times = [1.281, 8.394, 36.91, 72.201, 98.943, 2002.06, 8041.38]
quick_times = [0.135, 0.352, 0.942, 2.086, 2.677, 9.412, 15.39]
recursive_merge_times = [0.625, 2.524, 5.999, 7.368, 10.178, 33.80, 54.86]
shell_times = [0.236, 0.541, 1.611, 3.513, 4.883, 17.93, 30.968]
radix_lsd_times = [0.515, 0.854, 1.692, 2.017, 3.529, 9.371, 13.76]
lex_times = [1.925, 5.695, 12.292, 17.13, 19.103, 81.37, 196.63]
heap_times = [0.387, 0.667, 2.093, 2.55, 4.111, 15.9, 27.21]

plt.figure()
plt.plot(sizes, selection_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Selection Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, bubble_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Bubble Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, insertion_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Iteration Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, quick_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Quick Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, recursive_merge_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Merge Sort (recursion)')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, shell_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Shell Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, radix_lsd_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Radix Sort (LSD)')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, lex_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Lexicographic Sort')
plt.grid(True)
plt.show()

plt.figure()
plt.plot(sizes, heap_times, 'ro-')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')
plt.title('Heap Sort')
plt.grid(True)
plt.show()