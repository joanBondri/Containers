
# ft_containers - Reimplementation of C++ Standard Library Containers

![GitHub last commit](https://img.shields.io/github/last-commit/joanBondri/Containers)

## Overview

ft_containers is a project created as part of the "ft_containers" curriculum at École 42, designed to provide an in-depth understanding of C++ and its Standard Library. In this project, we have reimplemented core C++ Standard Library containers, including `vector`, `stack`, and `map`, within our custom namespace `ft`. The goal is to deepen our knowledge of C++ and its underlying data structures while ensuring compatibility with the standard library containers.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Prerequisites

Before you begin, ensure you have the following requirements:

- A Unix-based operating system (Linux or macOS).
- A C++ compiler that supports C++98 (e.g., GCC or Clang).
- [GNU Make](https://www.gnu.org/software/make/) for building the project.

### Installation

1. Clone this repository to your local machine.

```shell
git clone https://github.com/joanBondri/Containers.git
cd Containers
```

2. Build the project using the provided Makefile.

```shell
make
```

## Usage

The `ft_containers` project provides custom implementations of several C++ Standard Library containers, accessible within the `ft` namespace. To use these containers in your C++ programs, include the appropriate header files and use the `ft::` namespace qualifier.

Here's an example of how to use the `ft::vector` container:

```cpp
#include <iostream>
#include "includes/vector.hpp"

int main() {
    ft::vector<int> myVector;

    myVector.push_back(42);
    myVector.push_back(73);

    for (const auto& value : myVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Supported Containers

- `ft::vector` - A custom implementation of the C++ Standard Library `std::vector`.
- `ft::stack` - A custom implementation of the C++ Standard Library `std::stack`.
- `ft::map` - A custom implementation of the C++ Standard Library `std::map`.

## Testing

The `containers_test` directory contains scripts for testing your custom containers against their C++ Standard Library counterparts.

- `do.sh` - Compares the behavior and output of your containers with the standard library containers using a set of test cases.
- `one` - Displays the output of your containers' test cases side by side with the standard library containers for comparison.

To run the tests, execute the following command:

```shell
./includes/containers_test/do.sh
```

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve this project. Please make sure to follow the code of conduct.

