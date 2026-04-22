# Contributing and Debugging

Make sure to respect the epitech coding style!

And only include what's needed.

## Build in debug mode

To build in debug mode, simply use the `debug` rule present in the Makefile, i.e. `make debug`.

## LSP and Formatting

If you want proper LSP support in your editor, you must use **clangd**. To use clangd, you first need to generate a compile commands database.

To do so, you can simply use the `bear` command line tool.
After installing it, run `bear -- make re -j` to generate the database.

In VSCode, you would first install the [official clang extension](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) (incompatible with the official C/C++ extension, that you first need to disable if already installed).

After installing it, generate the database as mentioned previously. Then, press CTRL+SHIFT+P and run `clangd: Restart Language Server`.

For **formatting**, before submitting your code, make sur to run `git-clang-format-20` (installable with the package `clang-format-20` in the project's root directory. That will automatically format all the files that you've edited. Then make sure that the code respects the epitech coding style.

If there is some problem with the formatting, you can use the comments `// clang-format off` and `// clang-format on` to surround the concerned code.

Additionally, separate project, lib and system headers in different groups. First system, then lib, then project. 

## Clang-tidy

If you're using the clangd LSP, clang-tidy will automatically reports the problems it finds. Pay attention to them.

You can install it using the `clang-tidy-20` package, and run it using `run-clang-tidy-20 -quiet`.

## Faster Compilation

To improve the compilation time, you can use a different compiler than `epiclang`, which is slow due to the fact that it checks the coding style.

To do so, you can run make using the additional CC argument. For example:

```sh
make CC=clang-20
```

will use clang-20 instead of epiclang.

Moreover, you can use parallel compilation using the -j flag. For example:

```sh
make -j4
```

will use 4 threads instead of a single one. To use all available threads, simply run

```sh
make -j$(nproc)
```

For fastest compilation, combine these two parameters:

```sh
make -j$(nproc) CC=clang-20
```
