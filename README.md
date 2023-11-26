## Preconditions

All tasks should be performed from `src` directory.

## Components

### `main`

* Reads arrays to sort from a source file.
* Sorts arrays using different implementations of *merge sort* algorithm.
* Benchmarks the execution of each method.
* Saves the results to the target file.

### `samplegen`

* Generates random arrays to be sorted.
* Saves them to the target file.

## Compiling

### `main`

```shell
make
```

### `samplegen`

```shell
make samplegen
```

### Cleanup

```shell
make clean
```

## Running

### `main`

```shell
./main
```

### `samplegen`

* **arg1:** number of arrays to generate
* **arg2:** length of each array
* **arg3:** output file name

```shell
./samplegen 100 100 output.txt
```

Output file format is as follows:

```
<number_of_arrays_to_generate> <length_of_each_array>
arr1_element1 arr1_element2 arr1_element3 ...
arr2
arr3
...
```