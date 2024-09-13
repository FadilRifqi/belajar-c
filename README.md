### Learning C

#### Project Structure

- **main.c**: The main source file containing the implementation of the data visualization application.
- **nob.c**: A build script written in C that uses the nob library to compile the project.
- **nob.h**: The header file for the nob library, which provides various utilities for building and running commands.

#### Dependencies

- **raylib**: A simple and easy-to-use library to enjoy videogames programming.
- **nob**: A custom build system inspired by nobuild.

#### How to Build

To build the project, run the following command:

first compile the nob.c into build/nob

```sh
cc -o build/nob nob.c
```

then compile the main.c

```sh
build/nob
```

This will compile the main.c file and link it with the necessary libraries (raylib and libm).

#### How to Run

After building the project, you can run the executable:

```sh
build/main
```

#### Features

- **Cluster Generation**: Generates random clusters of points.
- **Interactive Updates**: Press `R` to regenerate clusters and `SPACE` to update the cluster means.
- **Visualization**: Displays the clusters and their means on the screen.

#### Key Functions

- `generate_cluster()`: Generates a cluster of points around a center.
- `reset_cluster()`: Resets the clusters based on the current means.
- `update_means()`: Updates the means of the clusters based on the current points.
- `project_sample_to_screen()`: Projects a sample point to screen coordinates.

#### Credit

This project utilizes the `nob` library. For more information, please visit the [nobuild repository](https://github.com/tsoding/nobuild) by tsoding.
